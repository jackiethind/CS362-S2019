#include "assert.h"
#include "dominion_helpers.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>

#define TESTCARD "adventurer"

/*
 * Card Test for Adventurer Card
 * Reveal cards from your deck until you reveal 2 treasure cards, put those cards in your hand and discard the other cards
 * +
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
    int seed = 1000;
    int discarded = 1;
    int numPlayers = 2;
    int newCards = 0;
    int thisPlayer = 0;
    int otherPlayer = 1;
    int numToTreasure = 0;

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, great_hall, smithy};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    printf("TEST 1: Drawing correct number of cards for treasure \n");

    testG.deck[thisPlayer][0] = mine;
    testG.deck[thisPlayer][1] = silver;
    testG.deck[thisPlayer][2] = mine;
    testG.deck[thisPlayer][3] = mine;
    testG.deck[thisPlayer][4] = mine;
    testG.deck[thisPlayer][5] = silver;

    testG.deckCount[thisPlayer] = 6;

    G.deck[thisPlayer][0] = mine;
    G.deck[thisPlayer][1] = silver;
    G.deck[thisPlayer][2] = mine;
    G.deck[thisPlayer][3] = mine;
    G.deck[thisPlayer][4] = mine;
    G.deck[thisPlayer][5] = silver;

    G.deckCount[thisPlayer] = 6;

    testG.hand[thisPlayer][0] = adventurer;
    testG.hand[thisPlayer][1] = adventurer;

    testG.handCount[thisPlayer] = 2;

    G.hand[thisPlayer][0] = adventurer;
    G.hand[thisPlayer][1] = adventurer;

    G.handCount[thisPlayer] = 2;

    memcpy(&testG, &G, sizeof(struct gameState));
    adventurerCard(&testG, whoseTurn(&testG));

    numToTreasure = 5;
    newCards = 2;
    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - numToTreasure);

    customAssert(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    customAssert(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - numToTreasure);

    printf("TEST 2: Drawing minimum number of cards for treasure \n");

    testG.deck[thisPlayer][0] = silver;
    testG.deck[thisPlayer][1] = silver;

    testG.deckCount[thisPlayer] = 2;

    G.deck[thisPlayer][0] = silver;
    G.deck[thisPlayer][1] = silver;

    G.deckCount[thisPlayer] = 2;

    testG.hand[thisPlayer][0] = adventurer;

    testG.handCount[thisPlayer] = 1;

    G.hand[thisPlayer][0] = adventurer;

    G.handCount[thisPlayer] = 1;

    memcpy(&testG, &G, sizeof(struct gameState));
    adventurerCard(&testG, whoseTurn(&testG));
    numToTreasure = 2;

    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - numToTreasure);

    customAssert(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    customAssert(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - numToTreasure);

    printf("TEST 3: Not enough treasures in deck \n");

    testG.deck[thisPlayer][0] = silver;
    testG.deckCount[thisPlayer] = 1;

    G.deck[thisPlayer][0] = silver;
    G.deckCount[thisPlayer] = 1;

    testG.hand[thisPlayer][0] = adventurer;

    testG.handCount[thisPlayer] = 1;

    G.hand[thisPlayer][0] = adventurer;

    G.handCount[thisPlayer] = 1;

    memcpy(&testG, &G, sizeof(struct gameState));
    adventurerCard(&testG, whoseTurn(&testG));

    numToTreasure = 1;
    newCards = 1;
    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - numToTreasure);

    customAssert(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    customAssert(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - numToTreasure);


    printf("TEST 4: Other Players Unchanged \n");

    testG.deck[thisPlayer][0] = silver;
    testG.deck[thisPlayer][1] = silver;

    testG.deckCount[thisPlayer] = 2;

    G.deck[thisPlayer][0] = silver;
    G.deck[thisPlayer][1] = silver;

    G.deckCount[thisPlayer] = 2;

    testG.hand[thisPlayer][0] = adventurer;

    testG.handCount[thisPlayer] = 1;

    G.hand[thisPlayer][0] = adventurer;

    G.handCount[thisPlayer] = 1;

    memcpy(&testG, &G, sizeof(struct gameState));
    adventurerCard(&testG, whoseTurn(&testG));


    memcpy(&testG, &G, sizeof(struct gameState));

    villageCard(&testG, whoseTurn(&testG), 3);

    printf("other player hand count = %d, expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
    printf("other player deck count = %d, expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
    printf("other player discard count = %d, expected = %d\n", testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);

    customAssert(testG.handCount[otherPlayer], G.handCount[otherPlayer]);
    customAssert(testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
    customAssert(testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);

    printf("TEST 5: Kingdom and Victory Cards unchanged \n");

    memcpy(&testG, &G, sizeof(struct gameState));
    adventurerCard(&testG, whoseTurn(&testG));

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