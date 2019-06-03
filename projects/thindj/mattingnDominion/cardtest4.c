#include "assert.h"
#include "dominion_helpers.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>

#define TESTCARD "smithy"


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

int main(){

    struct gameState G, testG;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int handPos = 0;
    int returnValue = 0;
    int k[10] = {smithy, adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, great_hall};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    printf("TEST 1: handpos is out of bounds [NEGATIVE TEST]\n");
    handPos = -1;

    memcpy(&testG, &G, sizeof(struct gameState));
    returnValue = playSmithy(&testG, 3);
    ;

    printf("return result = %d, expected = %d\n", returnValue, -1);
    customAssert(returnValue, -1);

    printf("TEST 2: card at handPos is not smithy [NEGATIVE TEST] \n");
    testG.hand[thisPlayer][0] = G.hand[thisPlayer][0] = gardens;
    testG.hand[thisPlayer][1] = G.hand[thisPlayer][1] = smithy;

    testG.handCount[thisPlayer] = G.handCount[thisPlayer] = 2;

    handPos = 0;

    printf("result = %d, expected = %d\n", testG.hand[thisPlayer][handPos], smithy);
    customAssert(testG.hand[thisPlayer][handPos], smithy);

    memcpy(&testG, &G, sizeof(struct gameState));
    returnValue = playSmithy(&testG, 3);

    printf("return result = %d, expected = %d\n", returnValue, -1);
    customAssert(returnValue, -1);


    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

    return 0;
}