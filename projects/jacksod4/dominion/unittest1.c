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
    int seed = 1000;
    int numPlayer = 2;
    int r;
	int p, handCount, newHandCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
    int handPos = 0;
	int playedCardCount = 0;

    printf ("TESTING discardCard():\n");

	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game


    for (p = 0; p < numPlayer; p++) 
    {
		for (newHandCount = 2; newHandCount <= maxHandCount; newHandCount++) //should be 2
        {
			for (handPos = 0; handPos <= newHandCount; handPos++)
            {
				#if (NOISY_TEST == 1)
                printf("Test player %d max hand count %d handPos %d.\n", p, newHandCount ,handPos);
				#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = newHandCount;                 // set the number of cards on hand
					

				handCount =  G.handCount[p];
				playedCardCount = G.playedCardCount;
				//discard card by trashing
				discardCard(handPos,p,&G, 1);				
				#if (NOISY_TEST == 1)
				printf("G.handCount = %d, expected = %d\n", G.handCount[p], handCount - 1);
				printf("G.playedCardCount = %d, expected = %d\n", G.playedCardCount, playedCardCount);	
				#endif
                assertTrue(G.handCount[p] == handCount - 1); // check if the number of cards is correct
				assertTrue(G.playedCardCount == playedCardCount); // check if the number of played cards is correctt
				
				handCount =  G.handCount[p];
				playedCardCount = G.playedCardCount;
				
				//discard and do not trash
				discardCard(handPos,p,&G, 0);
				
				#if (NOISY_TEST == 1)
                printf("G.handCount = %d, expected = %d\n", G.handCount[p], handCount - 1);
				printf("G.playedCardCount = %d, expected = %d\n", G.playedCardCount, playedCardCount + 1);
				#endif
                assertTrue(G.handCount[p] == handCount - 1); // check if the number of cards is correctt
				assertTrue(G.playedCardCount == playedCardCount + 1); // check if the number of played cards is correctt
            }
        }
    }

    printf("All tests passed!\n");

    return 0;
}
