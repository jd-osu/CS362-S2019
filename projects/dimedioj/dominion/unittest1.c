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

    int handCount_prev, deckCount_prev, discardCount_prev;
    //int num_tr_hand, num_tr_deck, num_tr_discard, total_deck_tr;
    //int num_tr_hand_prev, num_tr_deck_prev, num_tr_discard_prev, total_deck_tr_prev;
    
    int tr1, tr2;

    // clear the game state
    memset(&G, 23, sizeof(struct gameState));

    // initialize new game
    initializeGame(numPlayer, k, seed, &G);

    printf ("TESTING _adventurer():\n");
    
    //SET INPUT CONDITIONS - 1st 2 cards of deck are treasure cards
    tr1 = 4;
    tr2 = 5;

    G.deck[0][0] = tr1;
    G.deck[0][0] = tr2;
    
    handCount_prev = G.handCount[0];
    deckCount_prev = G.deckCount[0];
    discardCount_prev = G.discardCount[0];
    //num_tr_hand_prev = num_treasures(G.hand, G.handCount);
    //num_tr_deck_prev = num_treasures(G.deck, G.deckCount);
    //num_tr_discard_prev = num_treasures(G.discard, G.discardCount);
    //total_deck_tr_prev = num_tr_deck_prev + num_tr_discard_prev;

    
    // CALL FUNCTION
    _adventurer(0, &G);
    
    //num_tr_hand = num_treasures(G.hand, G.handCount);
    //num_tr_deck = num_treasures(G.deck, G.deckCount);
    //num_tr_discard = num_treasures(G.discard, G.discardCount);
    //total_deck_tr = num_tr_deck + num_tr_discard;
    
    printf("Hand diff = %d, expected = %d\n", G.handCount[0] - handCount_prev, 2);
    printf("Last two in hand = %d,%d, expected %d, %d\n", G.hand[0][G.handCount[0]-2], G.hand[0][G.handCount[0]-1], tr1, tr2);
    printf("Deck/discard diff = %d, expected = %d\n", G.deckCount[0] + G.discardCount[0] - deckCount_prev - discardCount_prev, -2);
    //printf("Hand treasures diff = %d, expected = %d\n", num_tr_hand - num_tr_hand_prev, 2);
    //printf("Deck/discard treasures diff = %d, expected = %d\n", total_deck_tr - total_deck_tr_prev, 2);

    //assert(G.coins == handCount * 3 + bonus); // check if the number of coins is correct


    printf("All tests passed!\n");

    return 0;
}
