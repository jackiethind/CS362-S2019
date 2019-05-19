#include "assert.h"
#include "dominion_helpers.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define TESTCARD "village"

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

int customVillageTest(int choice1, int choice2, int choice3, struct gameState *G, int handPos, int* bonus) {
    struct gameState testG;
    memcpy(&testG, G, sizeof(struct gameState));
    int returnVal = cardEffect(adventurer, choice1, choice2, choice3, &testG, handPos, bonus);

    customAssert(returnVal, 0);

    printf("estate unchanged test\n");
    customAssert(testG.supplyCount[estate], G->supplyCount[estate]);
    printf("duchy unchanged test\n");
    customAssert(testG.supplyCount[duchy], G->supplyCount[duchy]);
    printf("province unchanged test\n");
    customAssert(testG.supplyCount[province], G->supplyCount[province]);
    printf("gardens unchanged test\n");
    customAssert(testG.supplyCount[gardens], G->supplyCount[gardens]);
    printf("curse unchanged test\n");
    customAssert(testG.supplyCount[curse], G->supplyCount[curse]);
    printf("smithy unchanged test\n");
    customAssert(testG.supplyCount[smithy], G->supplyCount[smithy]);
    printf("adventurer unchanged test\n");
    customAssert(testG.supplyCount[adventurer], G->supplyCount[adventurer]);
    printf("embargo unchanged test\n");
    customAssert(testG.supplyCount[embargo], G->supplyCount[embargo]);
    printf("village unchanged test\n");
    customAssert(testG.supplyCount[village], G->supplyCount[village]);
    printf("minion unchanged test\n");
    customAssert(testG.supplyCount[minion], G->supplyCount[minion]);
    printf("mine unchanged test\n");
    customAssert(testG.supplyCount[mine], G->supplyCount[mine]);
    printf("cutpurse unchanged test\n");
    customAssert(testG.supplyCount[cutpurse], G->supplyCount[cutpurse]);
    printf("sea hag unchanged test\n");
    customAssert(testG.supplyCount[sea_hag], G->supplyCount[sea_hag]);
    printf("tribute unchanged test\n");
    customAssert(testG.supplyCount[tribute], G->supplyCount[tribute]);
    printf("council room unchanged test\n");
    customAssert(testG.supplyCount[council_room], G->supplyCount[council_room]);

    for (int i = 0; i < G->numPlayers; i++) {
        if (i != G->whoseTurn) {
            printf("other player hand count = %d, expected = %d\n", testG.handCount[i], G->handCount[i]);
            printf("other player deck count = %d, expected = %d\n", testG.deckCount[i], G->deckCount[i]);
            printf("other player discard count = %d, expected = %d\n", testG.discardCount[i], G->discardCount[i]);

            customAssert(testG.deckCount[i], G->deckCount[i]);
            customAssert(testG.discardCount[i], G->discardCount[i]);
            customAssert(testG.handCount[i], G->handCount[i]);
        }
        else {
            int newActions = 2;
            printf("num of actions= %d, expected = %d\n", testG.numActions, G->numActions + newActions);
            customAssert(testG.numActions, G->numActions + newActions);

            int newCards = 1;
            int discarded = 1;
            int shuffledCards = 0;
            printf("Current player state change check\n");
            printf("hand count = %d, expected = %d\n", testG.handCount[i], G->handCount[i] + newCards - discarded);
            printf("deck count = %d, expected = %d\n", testG.deckCount[i], G->deckCount[i] - newCards + shuffledCards);

            customAssert(testG.handCount[i], G->handCount[i] + newCards - discarded);
            customAssert(testG.deckCount[i], G->deckCount[i] - newCards + shuffledCards);

        }
    }
}

int main() {
    time_t t;
    srand((unsigned) time(&t));
    SelectStream(2);
    PutSeed(3);

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, great_hall, smithy};
    struct gameState G;

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    printf("Random Tests\n");

    // begin by randomizing all parameters for the adventurer card function
    for (int i = 0; i < 800; i++) {

        int numPlayers = rand() % 3 + 2;
        initializeGame(numPlayers, k, rand(), &G);
        // for every player, randomize their deckCount, discardCount, handCount
        for (int j = 0; j < numPlayers; j++) {

            do {
                G.deckCount[j] = (int) floor(Random() * (MAX_DECK));
                G.discardCount[j] = (int) floor(Random() * (MAX_DECK));
                G.handCount[j] = (int) floor(Random() * (MAX_HAND));
            }
                // the game has 500 cards to make it so they less than 500
            while (G.deckCount[j] + G.discardCount[j] + G.handCount[j] >= 500);
        }
        G.whoseTurn = rand() % numPlayers;
        int choice1 = rand();
        int choice2 = rand();
        int choice3 = rand();
        int bonus = rand();
        int handPos;
        if (G.handCount[G.whoseTurn] == 0 ) {
            handPos = 0;
        }
        else {
            handPos = rand() % G.handCount[G.whoseTurn];
        }
        customVillageTest(choice1, choice2, choice3, &G, handPos, bonus);
    }
    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
    return 0;
}