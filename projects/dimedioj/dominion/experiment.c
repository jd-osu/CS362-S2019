/* -----------------------------------------------------------------------
 * Author: Jason DiMedio
 * CS362, Spring 2019
 * NOTE: The following code was adapted from testUpdateCoins.c provided as a
 * template to be used in Assignment 3 for CS362.
 *
 * testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
 *      gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

/*
int num_treasures(int cards[], int n)
{
  int count = 0;
  int i;
  for (i=0; i<n; i++)
  {
    if (cards[i] == copper || cards[i] == silver || cards[i] == gold)
      count++;
  }
  
  return count;
}
*/

int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int p, r, handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    
    printf ("TESTING _adventurer():\n");

    // clear the game state
    memset(&G, 23, sizeof(struct gameState));

    // initialize new game
    initializeGame(numPlayer, k, seed, &G);

    for (p=0; p<numPlayer; p++)
    {
      printf("player=%d\n", p);
      
      printf("handCount=%d\n", G.handCount[p]);
      for (i=0; i<50; i++)
      {
        printf("%d : %d\n", i, G.hand[p][i]);
      }
      
      printf("deckCount=%d\n", G.deckCount[p]);
      for (i=0; i<50; i++)
      {
        printf("%d : %d\n", i, G.deck[p][i]);
      }
      
      printf("discardCount=%d\n", G.discardCount[p]);
      for (i=0; i<50; i++)
      {
        printf("%d : %d\n", i, G.discard[p][i]);
      }
      
      printf("\n");
    }

    printf("All done!\n");

    return 0;
}
