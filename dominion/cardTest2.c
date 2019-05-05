#include "assert.h"
#include "dominion_helpers.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>

#define TESTCARD "embargo"
/*
 * Card Test for Embargo Card
 * + 2 coins
 * + 1 Embargo token
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

int main() {
    struct gameState G, testG;
    int eTokens = 0;
    int xtraCoins = 0;
    int numPlayers = 2;
    int thisPlayer = 0;
    int choice1 = 0;
    int seed = 1000;

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, great_hall, smithy};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    printf("TEST 1: +2 coins \n");
    memcpy(&testG, &G, sizeof(struct gameState));
    embargoCard(&testG, thisPlayer, 0, choice1);

    xtraCoins = 2;

    printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
    customAssert(testG.coins, G.coins + xtraCoins);


    printf("TEST 2: +1 embargo token \n");
    eTokens = 1;
    printf("tokens = %d, expected = %d\n", testG.embargoTokens[choice1], G.embargoTokens[choice1] + eTokens);
    customAssert(testG.embargoTokens[choice1], G.embargoTokens[choice1] + eTokens);

    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

    return 0;
}