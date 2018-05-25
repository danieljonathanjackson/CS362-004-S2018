#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
// cd CS362/CS362-004-S2018/projects/jacksod4/dominion/
#define NOISY_TEST 1

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
    int seed = 1000;
    int numPlayer = 5;
    int r,i;
	int p, handCount, newHandCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 6;
    int handPos = 0;
	int playedCardCount = 0;
	int count = 0;
    int curPlayer = 0;
	printf ("TESTING discardCard():\n");

	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game


    while(count < 100){
		
		//randomly select  2-4 players
		numPlayer = (rand() % 3 ) + 2;	
		
		//select player to remove card , 0-(numPlayer -1 )
		p = (rand() % numPlayer );		
		
		#if (NOISY_TEST == 1)
		printf("iteration %i , num players = %i , newHandCount = %i , handPos = %i \n",count,p,newHandCount,handPos);
		#endif
		memset(&G, 23, sizeof(struct gameState));   // clear the game state
		r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
				
		// loop through each players, set number of cards on hand between 2-10
		for (i=0;i<numPlayer;i++){
			newHandCount = (rand() % 9) + 2;
			G.handCount[i] = newHandCount;                	
		}
		
		handCount =  G.handCount[p];
		
		//randomly select hand pos, between 0 - 1 less than maxHandCount
		handPos = (rand() % newHandCount );
		printf("iteration %i , num players = %i , newHandCount = %i , handPos = %i \n",count,numPlayer,newHandCount,handPos);
		
		playedCardCount = G.playedCardCount;
		//discard card by trashing
		discardCard(handPos,p,&G, 1);				
		#if (NOISY_TEST == 1)
		printf("G.playedCardCount = %d, expected = %d\n", G.playedCardCount, playedCardCount);	
		#endif
		assertTrue(G.handCount[p] == handCount - 1); // check if the number of cards is correct
		assertTrue(G.playedCardCount == playedCardCount); // check if the number of played cards is correctt
		
		handCount =  G.handCount[p];
		playedCardCount = G.playedCardCount;
		
		//discard and do not trash
		handPos = (rand() % newHandCount );
		printf("discarding by trashing \n");
		printf("iteration %i , num players = %i , newHandCount = %i , handPos = %i , handCount =%i \n",count,numPlayer,newHandCount,handPos, handCount);
		
		discardCard(handPos,p,&G, 0);
		#if (NOISY_TEST == 1)
		printf("G.handCount = %d, expected = %d\n", G.handCount[p], handCount - 1);
		printf("G.playedCardCount = %d, expected = %d\n", G.playedCardCount, playedCardCount + 1);
		#endif
		assertTrue(G.handCount[p] == handCount - 1); // check if the number of cards is correctt
		assertTrue(G.playedCardCount == playedCardCount + 1); // check if the number of played cards is correctt
		printf("All tests completed!\n");
		count++;
	}
    return 0;
}
