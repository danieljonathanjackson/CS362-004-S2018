#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs 
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
    int numPlayer = 4;
    int p, r;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    printf ("TESTING whoseTurn():\n");
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

    for (p = 0; p < numPlayer; p++) 
    {
		#if (NOISY_TEST == 1)
		printf("Test player %d \n", p);
		#endif
		//memset(&G, 23, sizeof(struct gameState));   // clear the game state
		//r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	
		#if (NOISY_TEST == 1)
		printf("whose turn = %d, expected = %d\n", whoseTurn(&G), p);
		#endif
		assertTrue(whoseTurn(&G) == p);
		
		//switch turn
		endTurn(&G);
    }

    printf("All tests passed!\n");

    return 0;
}
