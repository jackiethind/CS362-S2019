#include "assert.h"
#include "dominion_helpers.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>

#define TESTCARD "councilRoom"

/*
 * Unit Test for Council Room Card
 * + 4 cards, + 1 Buy, each other player draws a card
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

    struct gameState G, testG;
    int newCards = 0;
    int newBuys = 0;
    int discarded = 1;
    int newCardsOtherPlayers = 0;
    int shuffledCards = 0;
    int numPlayers = 2;
    int thisPlayer = 0;
    int otherPlayer = 1;
    int seed = 1000;

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, council_room};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    printf("TEST 1: + 4 cards \n");
    memcpy(&testG, &G, sizeof(struct gameState));
    playCouncilRoom(&testG, 9);

    newCards = 4;

    printf("Current player state change check\n");
    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);

    customAssert(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    customAssert(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);

    printf("TEST 2: + 1 buy \n");

    newBuys = 1;

    printf("buys count = %d, expected = %d\n", testG.numBuys, G.numBuys + newBuys);
    customAssert(testG.numBuys, G.numBuys + newBuys);


    printf("TEST 3: + 1 card for each other player \n");
    newCardsOtherPlayers = 1;

    printf("Other player state change check\n");
    printf("other player hand count = %d, expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer] + newCardsOtherPlayers);
    printf("other player deck count = %d, expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer] - newCardsOtherPlayers + shuffledCards);
    printf("other player discard count = %d, expected = %d\n", testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);

    customAssert(testG.handCount[otherPlayer], G.handCount[otherPlayer] + newCardsOtherPlayers);
    customAssert(testG.deckCount[otherPlayer], G.deckCount[otherPlayer]- newCardsOtherPlayers + shuffledCards);
    customAssert(testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);

    printf("TEST 4: Kingdom and Victory Cards unchanged \n");

    memcpy(&testG, &G, sizeof(struct gameState));
    playCouncilRoom(&testG, 9);

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