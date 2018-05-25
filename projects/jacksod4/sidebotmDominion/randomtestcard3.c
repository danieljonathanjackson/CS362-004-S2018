#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output 1147
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
    int j;
    int seed = 1000;
    int numPlayer = 2;
    int p, r, handCount, deckCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int handPos = 0;
	int maxSupplyPos = 2;
    int toFlag = 0;
	int discardCount = 0;
	int newHandCount;
	int count = 0;
	printf ("TESTING gainCard():\n");

	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	
	while(count < 100){
		numPlayer = (rand() % 3 ) + 2;	
		p = (rand() % numPlayer );
		//randomly select max supply , 0-(maxSupplyPos -1 )
		
		printf("j=%i\n",j);
		//randomly select toFlag
		toFlag = (rand() % 3 );j = (rand() % (maxSupplyPos + 2) ) - 1;	
		
		#if (NOISY_TEST == 1)
		printf("Test player %d supplyPos %d toFlag %d.\n", p, j ,toFlag);
		#endif
		memset(&G, 23, sizeof(struct gameState));   // clear the game state
		r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
		newHandCount = (rand() % 9) + 2;
		G.handCount[p] = newHandCount;                 // set the number of cards on hand
						
		discardCount = G.discardCount[p];
		handCount =  G.handCount[p];
		deckCount =  G.deckCount[p];
					
		//gaincard
		gainCard(p, &G, toFlag, p);
		
		// toFlag = 0 : add to discard
		// toFlag = 1 : add to deck
		// toFlag = 2 : add to hand
		if (toFlag == 0){
			#if (NOISY_TEST == 1)
			printf("G.discardCount = %d, expected = %d\n", G.discardCount[p], discardCount + 1);
			#endif
			assertTrue(G.discardCount[p] == discardCount + 1); // check if the number of cards is correct
		}
		
		if (toFlag == 1){
			#if (NOISY_TEST == 1)
			printf("G.deckCount = %d, expected = %d\n", G.deckCount[p], deckCount + 1);
			#endif
			assertTrue(G.deckCount[p] == deckCount + 1); // check if the number of cards is correct
		}


		if (toFlag == 2){
			#if (NOISY_TEST == 1)
			printf("G.handCount = %d, expected = %d\n", G.handCount[p], handCount + 1);
			#endif
			assertTrue(G.handCount[p] == handCount + 1); // check if the number of cards is correct
		}	
		count++;
	}
    printf("All tests complete!\n");

    return 0;
}
