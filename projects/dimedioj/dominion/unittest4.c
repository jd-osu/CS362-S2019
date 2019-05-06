/* -----------------------------------------------------------------------
 * Author: Jason DiMedio
 * CS362, Spring 2019
 * NOTE: The following code was adapted from testUpdateCoins.c provided as a
 * template to be used in Assignment 3 for CS362.
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// bool type defined
typedef enum {false, true} bool;

const char PASS[] = "PASS";
const char FAIL[] = "FAIL";
const char FUNCTION[] = "_sea_hag()";

void display_state(struct gameState *state)
{
  int i, p;

  for (p = 0; p<state->numPlayers; p++)
  {
    printf("player: %d\n", p);
    
    printf("HAND: %d\n", state->handCount[0]);
    for (i=0; i<state->handCount[0]; i++)
      printf("%d : %d\n", i, state->hand[0][i]);
    printf("DECK: %d\n", state->deckCount[0]);
    for (i=0; i<state->deckCount[0]; i++)
      printf("%d : %d\n", i, state->deck[0][i]);
    printf("DISCARD: %d\n", state->discardCount[0]);
    for (i=0; i<state->discardCount[0]; i++)
      printf("%d : %d\n", i, state->discard[0][i]);
    printf("\n"); 
  }
  
  printf("PLAYED: %d\n", state->playedCardCount);
  for (i=0; i<state->playedCardCount; i++)
    printf("%d : %d\n", i, state->playedCards[i]);
  printf("\n");
  
  printf("SUPPLY:\n");
  for (i=0; i<=treasure_map; i++)
    printf("%d : %d\n", i, state->supplyCount[i]);
  printf("\n");
}



int _assert(bool condition, const char *test_name)
{
  printf("%s: ", FUNCTION);
  
  if (condition == true)
    printf("%s", PASS);
  else
    printf("%s", FAIL);
  
  printf(" when %s\n", test_name);
}

int main() {
    int i;
    int seed = 1000;
    int numPlayer;
    int p, r, handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    int handCount_prev[10], deckCount_prev[10], discardCount_prev[10], playedCount_prev, curse_qty_Prev;
    
    int p2_deck, p2_discard, hag_idx, curse_qty;
    
    int return_val;
    
    bool result;


    // ************************************************************************************
    //TEST1
    const char test1[] = "players=2, curse supply >0, deck>0";

    numPlayer = 2;

    // clear the game state
    memset(&G, 23, sizeof(struct gameState));

    // initialize new game
    initializeGame(numPlayer, k, seed, &G);

    hag_idx = 0;
    //curse_qty =
    p2_deck = 5;
    p2_discard = 5;
    G.hand[0][hag_idx] = sea_hag;

    for (p=1; p<G.numPlayers; p++)
    { 
      G.deckCount[p] = p2_deck;
      G.discardCount[p] = p2_discard;
    }

    for (p=0; p<G.numPlayers; p++)
    { 
      handCount_prev[p] = G.handCount[p];
      deckCount_prev[p] = G.deckCount[p];
      discardCount_prev[p] = G.discardCount[p];
    }
    playedCount_prev = G.playedCardCount;
    curse_qty_Prev = G.supplyCount[curse];

    display_state(&G);    
    
    return_val = _sea_hag(0, &G);
    
    display_state(&G);    
    
/*    result =  ( (return_val == 0) &&
                (G.handCount[0] - handCount_prev == -1) &&
                (G.playedCardCount - playedCount_prev == 1) &&
                (G.discardCount[0] - discardCount_prev == 0) &&
                (c2_result) &&
                (G.supplyCount[c2] - c2_qty_Prev == -1)
              );

    _assert(result, test1);
*/    
    
   
    return 0;
}
