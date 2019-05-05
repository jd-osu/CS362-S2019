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


int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int p, r, handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    
    int prev_hand_p1, prev_hand_p2;
    int first_tr, first_tr_idx, second_tr, second_tr_idx;
    
    int cards_revealed[MAX_PLAYERS][MAX_DECK];
    
    int maxHandCount = 5;
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    printf ("TESTING _adventurer():\n");

    // clear the game state
    memset(&G, 23, sizeof(struct gameState));

    // initialize new game
    initializeGame(numPlayer, k, seed, &G);

    G.
    
    
    
    printf("G.coins = %d, expected = %d\n", G.coins, handCount * 1 + bonus);






    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            for (bonus = 0; bonus <= maxBonus; bonus++)
            {
#if (NOISY_TEST == 1)
                printf("Test player %d with %d treasure card(s) and %d bonus.\n", p, handCount, bonus);
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand
                memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
                updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
                printf("G.coins = %d, expected = %d\n", G.coins, handCount * 1 + bonus);
#endif
                assert(G.coins == handCount * 1 + bonus); // check if the number of coins is correct

                memcpy(G.hand[p], silvers, sizeof(int) * handCount); // set all the cards to silver
                updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
                printf("G.coins = %d, expected = %d\n", G.coins, handCount * 2 + bonus);
#endif
                assert(G.coins == handCount * 2 + bonus); // check if the number of coins is correct

                memcpy(G.hand[p], golds, sizeof(int) * handCount); // set all the cards to gold
                updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
                printf("G.coins = %d, expected = %d\n", G.coins, handCount * 3 + bonus);
#endif
                assert(G.coins == handCount * 3 + bonus); // check if the number of coins is correct
            }
        }
    }

    printf("All tests passed!\n");

    return 0;
}
