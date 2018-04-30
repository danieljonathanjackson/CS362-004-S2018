#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "outpost"


int assertTrue(logicalStatement){
	if (logicalStatement == 1){
		printf("TEST SUCCESSFULLY COMPLETED\n");
		return 1;
	} else if (logicalStatement == 0){
		printf("TEST FAILED\n");
		return 0;		
	}

	return 0;
}


int main() {
    int newCards = 0;
    int discarded = 1;
	int newOutpost = 1;
    int i;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	int otherPlayer = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
		
	// might need to initialize
	int k_test[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	cardEffect(outpost, choice1, choice2, choice3, &testG, handpos, &bonus);

	// Current player should have 1 less card.
	printf("TEST 1: Current player should receive exact 1 cards, +1 cards\n");	
	newCards = 0;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);

	//deck count should remain constant
	printf("TEST 2: Current player deck should decrease by exact 1 card\n");	
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer]);

	// Outpost flag should increase by 1
	printf("TEST 4: Current player deck should decrease by exact 1 card\n");	
	printf("TEST2: Outpost flags increased by 1.\n");
	printf("player actions = %d, expected = %d\n", testG.outpostPlayed, G.outpostPlayed + newOutpost);
	assertTrue(testG.outpostPlayed == G.outpostPlayed + newOutpost);

	
	// No state change should occur for other players.
	printf("TEST 3: No state change should occur for other players.\n");	
	// other players card and deck count should not change
	printf("hand count = %d, expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
	assertTrue(testG.handCount[otherPlayer] == G.handCount[otherPlayer]);
	printf("deck count = %d, expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
	assertTrue(testG.deckCount[otherPlayer] == G.deckCount[otherPlayer]);

	printf("TEST 3: Current player discard count should not change (until after turn)\n");	
	printf("deck count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	assertTrue(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer]);		
	
		
	// No state change should occur to the victory card piles and kingdom card piles
	printf("TEST 4:No state change should occur to the victory card piles and kingdom card piles.\n");		
	//check  kingdom cards are not different
	printf("Checking Kingdom Cards\n");
	for (i = 0; i < 10; i++)
		{
			assertTrue(k[i] == k_test[i]);			
		}
	
	// victory cards
	printf("estate card count = %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate]);
	assertTrue(testG.supplyCount[estate] == G.supplyCount[estate]);
	
	printf("estate card count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
	assertTrue(testG.supplyCount[duchy] == G.supplyCount[duchy]);
	
	printf("province card count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);
	assertTrue(testG.supplyCount[province] == G.supplyCount[province]);
		
	//after end of turn discard count should increase by 1
	endTurn(&testG);
	endTurn(&G);
	printf("TEST 5: Current player discard count should increase by exactly 1 card after turn\n");	
	printf("deck count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] - discarded);
	assertTrue(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] - discarded);	

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}


