#include "assert.h"
#include "dominion_helpers.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>

#define TESTCARD "minion"
/*
 * Unit Test for Minion Card
 * + 1 action
 * Choice 1: +2 coins
 * Choice 2: discard hand, +4 cards, each player with at least 5 cards in their hand discards their hand and draws + 4 cards.
*/

int customAssert(int actual, int expected)
{
    if (actual == expected) {
        printf("TEST SUCCEEDED: actual: %d, expected: %d \n", actual, expected);

    }
    else {
        printf("TEST FAILED: actual: %d, expected: %d \n", actual, expected);
    }
    return 0;
}

int main () {

    struct gameState G, testG, testG2;
    int choice1 = 0, choice2 = 0;
    int discarded = 0;
    int otherDiscarded = 0;
    int newCards = 0;
    int shuffledCards = 0;
    int m;
    int xtraCoins = 0;
    int newActions = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int otherPlayer = 1;


    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, council_room};

    initializeGame(numPlayers, k, seed, &G);

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    printf("TEST 1: +1 actions \n");

    memcpy(&testG, &G, sizeof(struct gameState));
    choice1 = 1;
    minionCard(&testG, whoseTurn(&testG), 4, choice1, choice2);

    newActions = 1;

    printf("num of actions= %d, expected = %d\n", testG.numActions, G.numActions + newActions);
    customAssert(testG.numActions, G.numActions + newActions);

    printf("TEST 2: Choice 1, +2 coins \n");

    xtraCoins = 2;

    printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
    customAssert(testG.coins, G.coins + xtraCoins);

    printf("TEST 3: Choice 2, discard hand, +4 cards, each player with at least 5 cards in their hand discards their hand and draws + 4 cards \n");
    choice1 = 0;
    choice2 = 1;

    // create hand and check if it gets discarded

    G.hand[thisPlayer][0] = steward;
    G.hand[thisPlayer][1] = copper;
    G.hand[thisPlayer][2] = duchy;
    G.hand[thisPlayer][3] = estate;
    G.hand[thisPlayer][4] = feast;

    G.hand[otherPlayer][0] = steward;
    G.hand[otherPlayer][1] = copper;
    G.hand[otherPlayer][2] = duchy;
    G.hand[otherPlayer][3] = estate;
    G.hand[otherPlayer][4] = feast;

    memcpy(&testG2, &G, sizeof(struct gameState));


    printf("starting cards of player: ");
    for (m=0; m<testG2.handCount[thisPlayer]; m++) {
        printf("(%d)", testG2.hand[thisPlayer][m]);
        discarded++;

    }
    printf("; ");

    printf("starting cards of other player: ");
    for (m=0; m<testG2.handCount[otherPlayer]; m++) {
        printf("(%d)", testG2.hand[otherPlayer][m]);
        otherDiscarded++;

    }
    printf("; ");


    minionCard(&testG2, whoseTurn(&testG2), 4, choice1, choice2);

    // cycle to check if hand was discarded

    printf("ending cards of player: ");
    for (m=0; m<testG2.handCount[thisPlayer]; m++) {
        printf("(%d)", testG2.hand[thisPlayer][m]);
    }
    printf("; ");

    printf("ending cards of other player: ");
    for (m=0; m<testG2.handCount[otherPlayer]; m++) {
        printf("(%d)", testG2.hand[otherPlayer][m]);
        otherDiscarded++;

    }
    printf("; ");

    newCards = 4;
    printf("player hand count = %d, expected = %d\n", testG2.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    printf("player deck count = %d, expected = %d\n", testG2.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
    customAssert(testG2.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    customAssert(testG2.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);

    printf("other player hand count = %d, expected = %d\n", testG2.handCount[otherPlayer], G.handCount[otherPlayer] + newCards - otherDiscarded);
    printf("other player deck count = %d, expected = %d\n", testG2.deckCount[otherPlayer], G.deckCount[otherPlayer] - newCards + shuffledCards);
    customAssert(testG2.handCount[otherPlayer], G.handCount[otherPlayer] + newCards - otherDiscarded);
    customAssert(testG2.deckCount[otherPlayer], G.deckCount[otherPlayer] - newCards + shuffledCards);

    printf("TEST 4: Kingdom and Victory Cards unchanged \n");

    memcpy(&testG, &G, sizeof(struct gameState));
    minionCard(&testG, whoseTurn(&testG), 4, choice1, choice2);

    printf("estate unchanged test\n");
    customAssert(testG.supplyCount[estate], G.supplyCount[estate]);
    printf("duchy unchanged test\n");
    customAssert(testG.supplyCount[duchy], G.supplyCount[duchy]);
    printf("province unchanged test\n");
    customAssert(testG.supplyCount[province], G.supplyCount[province]);
    printf("gardens unchanged test\n");
    customAssert(testG.supplyCount[gardens], G.supplyCount[gardens]);
    printf("curse unchanged test\n");
    customAssert(testG.supplyCount[curse], G.supplyCount[curse]);
    printf("smithy unchanged test\n");
    customAssert(testG.supplyCount[smithy], G.supplyCount[smithy]);
    printf("adventurer unchanged test\n");
    customAssert(testG.supplyCount[adventurer], G.supplyCount[adventurer]);
    printf("embargo unchanged test\n");
    customAssert(testG.supplyCount[embargo], G.supplyCount[embargo]);
    printf("village unchanged test\n");
    customAssert(testG.supplyCount[village], G.supplyCount[village]);
    printf("minion unchanged test\n");
    customAssert(testG.supplyCount[minion], G.supplyCount[minion]);
    printf("mine unchanged test\n");
    customAssert(testG.supplyCount[mine], G.supplyCount[mine]);
    printf("cutpurse unchanged test\n");
    customAssert(testG.supplyCount[cutpurse], G.supplyCount[cutpurse]);
    printf("sea hag unchanged test\n");
    customAssert(testG.supplyCount[sea_hag], G.supplyCount[sea_hag]);
    printf("tribute unchanged test\n");
    customAssert(testG.supplyCount[tribute], G.supplyCount[tribute]);
    printf("council room unchanged test\n");
    customAssert(testG.supplyCount[council_room], G.supplyCount[council_room]);

    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
    return 0;

}