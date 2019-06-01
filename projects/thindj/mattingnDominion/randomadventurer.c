#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main()
{
	
	int i;
    
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    
    int thisPlayer = 0;

    //holds a pointer to the gameState variable, in this case we have G and testG
    struct gameState G, testG;

    //an array k of 10 kingdom cards avaliable for purchase
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	for ( i = 0; i < 5; i++)
	{ 
		int numPlayers = (rand() % 50);
		int seed = (rand () % 1000);

		initializeGame(numPlayers, k, seed, &G);

		printf("----------------- Random Testing Card: %s ----------------\n", TESTCARD);

		//copying the game state to the test case, testG
		memcpy(&testG, &G, sizeof(struct gameState));
		cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
    
    	thisPlayer = whoseTurn(&testG);

    	//Test 1: Testing to see if the player has the Adventurer card within their hand
    	if (G.hand[thisPlayer][testG.handCount[thisPlayer]] != 1)
        printf("TEST 1 PASSED: THE HAND COUNT IS CORRECT\n");
    	else
        printf("TEST 1 FAILED: THE HAND COUNT IS NOT CORRECT\n");

    
    	//Test 2: Test to see if the player played the Adventurer card
    	if(testG.playedCardCount+2 == G.playedCardCount)
        printf("TEST 2 PASSED: THE PLAYER PLAYED THE ADVENTURER CARD\n");
   		else
        printf("TEST 2 FAILED: THE PLAYER DID NOT PLAY THE ADVENTURER CARD\n");

    	//Test 4: Test to see if the Adventurer card is discarded from the hand

    	if (testG.discardCount[thisPlayer] == G.discardCount[thisPlayer])
        printf("TEST 4: PASSED. ADVENTURER CARD WAS DISCARDED\n");
    	else
        printf("TEST 4: FAILED. ADVENTURER CARD NOT DISCARDED\n");


     printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	}

	return 0;

} 