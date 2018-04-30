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
	printf ("TESTING gainCard():\n");

	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	

    for (p = 0; p < numPlayer; p++) 
    {
		for (j = -1; j <= maxSupplyPos; j++) //supplyPos
        {
			for (toFlag = 0; toFlag < 3; toFlag++)
            {
				#if (NOISY_TEST == 1)
                printf("Test player %d supplyPos %d toFlag %d.\n", p, j ,toFlag);
				#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
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


            }
        }
    }

    printf("All tests passed!\n");

    return 0;
}
