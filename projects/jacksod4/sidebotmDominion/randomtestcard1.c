#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int failures=0;

int assertTrue(logicalStatement){
	if (logicalStatement == 1){
		printf("TEST SUCCESSFULLY COMPLETED\n");
		return 1;
	} else if (logicalStatement == 0){
		printf("TEST FAILED\n");
		failures++;
		return 0;		
	}

	return 0;
}


/*Determines number of treasure cards*/
int numberTreasureCards(struct gameState *state, int player){
	int handCount,i,numberTreasure, cardDrawn;
	numberTreasure=0;
	// get hand count
	handCount = state->handCount[player];
	// loop through number of cards
	for (i=0;i<handCount;i++){
		cardDrawn = state->hand[player][i];		
		//printf("card in hand  = %d\n", cardDrawn);
		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold){
			numberTreasure++;
		}
	}
	
	return numberTreasure;
}

int main() {
    int newCards = 0;
    int discarded = 1; //discarded due to playing card
    int shuffledCards = 0;
	int xtraTreasureCards = 0;
    int handpos = 0; 
	int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1200;
    int numPlayers; // set during random testing
	int thisPlayer = 0;
	int otherPlayer ; // set during random testing
	int newHandCount;
	int r,i;
	int count = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	
	//memset(&G, 23, sizeof(struct gameState));   // clear the game state
	//r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	
	while(count < 100)
	{
		// generate random inputs for testing 
		
		printf("----------------- Iteration %i Testing %s ----------------\n",count, TESTCARD);
		// select 2-6 players
		numPlayers = (rand() % 5 ) + 2;	
		
		
		// initialize a game state and random inputs
		/* memset(&G, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayers, k, seed, &G); // initialize a new game */
        initializeGame(numPlayers, k, seed, &G);
		
		
		
		printf("after initiliaze game \n");
		// loop through each players, set number of cards on hand between 2-10
		for (i=0;i<numPlayers;i++){
			newHandCount = (rand() % 9) + 2;
			G.handCount[i] = newHandCount;                	
		}
		
		
		// initializeGame(numPlayers, k, seed, &G);
		
		
		
		
		printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));
		cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

		// ----------- TEST 1:  +2 cards --------------
		printf("TEST 1:  +2 cards\n");
		newCards = 2;
		printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
		printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
		assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
		assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);

		// ----------- TEST 2:  +2 treasure cards --------------
		xtraTreasureCards = 2;
		printf("TEST 2:  +2 cards treasure cards in hand\n");
		printf("treasure card count = %d, expected = %d\n", numberTreasureCards(&testG, thisPlayer), numberTreasureCards(&G, thisPlayer) + xtraTreasureCards);
		assertTrue(numberTreasureCards(&testG, thisPlayer) == numberTreasureCards(&G, thisPlayer) + xtraTreasureCards);
			
		// No state change should occur for other players.
		printf("TEST 4: No state change should occur for other players.\n");	
		// other players card and deck count should not change
		for (otherPlayer=0;otherPlayer < numPlayers; otherPlayer++){
			printf("hand count = %d, expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
			assertTrue(testG.handCount[otherPlayer] == G.handCount[otherPlayer]);
			printf("deck count = %d, expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
			assertTrue(testG.deckCount[otherPlayer] == G.deckCount[otherPlayer]);	
			printf("treasure card count = %d, expected = %d\n", numberTreasureCards(&testG, otherPlayer), numberTreasureCards(&G, otherPlayer));
			assertTrue(numberTreasureCards(&testG, thisPlayer) == numberTreasureCards(&G, thisPlayer) + xtraTreasureCards);	
		}
		//after end of turn discard count should increase by at least 1
		endTurn(&testG);
		endTurn(&G);
		printf("TEST 5: Current player discard count should increase by at least 1 card after turn\n");	
		printf("discard count = %d, expected > %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
		assertTrue(testG.discardCount[thisPlayer] > G.discardCount[thisPlayer]);	

		printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
		count++;

	}
	printf("total number of failures %= ", failures);
	return 0;
}


