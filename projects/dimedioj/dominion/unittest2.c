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
const char FUNCTION[] = "_mine()";

void display_state(struct gameState *state)
{
  int i;
  
  printf("HAND: %d\n", state->handCount[0]);
  for (i=0; i<state->handCount[0]; i++)
    printf("%d : %d\n", i, state->hand[0][i]);
  printf("\n");
  
  printf("DECK: %d\n", state->deckCount[0]);
  for (i=0; i<state->deckCount[0]; i++)
    printf("%d : %d\n", i, state->deck[0][i]);
  printf("\n");
  
  printf("DISCARD: %d\n", state->discardCount[0]);
  for (i=0; i<state->discardCount[0]; i++)
    printf("%d : %d\n", i, state->discard[0][i]);
  printf("\n");
  
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
    int numPlayer = 2;
    int p, r, handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    int handCount_prev, deckCount_prev, discardCount_prev, playedCount_prev, c2_qty_Prev;
    
    int c1, c2, c1_idx, c2_qty, mine_idx;
    
    int return_val;
    
    bool result, c2_result;


    // ************************************************************************************
    //TEST1
    const char test1[] = "c1= copper, c2= silver, hand >1, c2_qty > 0";

    // clear the game state
    memset(&G, 23, sizeof(struct gameState));

    // initialize new game
    initializeGame(numPlayer, k, seed, &G);

    c1 = copper;
    c2 = silver;
    c1_idx = G.handCount[0]/2;
    mine_idx = 0;
    //c2_qty = 

    G.hand[0][c1_idx] = c1;
    G.hand[0][mine_idx] = mine;
    
    handCount_prev = G.handCount[0];
    deckCount_prev = G.deckCount[0];
    discardCount_prev = G.discardCount[0];
    playedCount_prev = G.playedCardCount;
    c2_qty_Prev = G.supplyCount[c2];
    
    //display_state(&G);    
    
    return_val = _mine(0, &G, mine_idx, c1_idx, c2); // int player, struct gameState *state, int pos, int c1, int c2
    
    //display_state(&G);    
    
    c2_result = false;
    for (i=0; i<G.handCount[0]; i++)
    {
      if (G.hand[0][i] == c2)
      {
        c2_result = true;
        break;
      }
    }
    
    result =  ( (return_val == 0) &&
                (G.handCount[0] - handCount_prev == -1) &&
                (G.playedCardCount - playedCount_prev == 1) &&
                (G.discardCount[0] - discardCount_prev == 0) &&
                (c2_result) &&
                (G.supplyCount[c2] - c2_qty_Prev == -1)
              );

    _assert(result, test1);
    
    
    // ************************************************************************************
    //TEST2
    const char test2[] = "c1= not treasure, c2= silver, hand>1, c2_qty > 0";

    // clear the game state
    memset(&G, 23, sizeof(struct gameState));

    // initialize new game
    initializeGame(numPlayer, k, seed, &G);

    c1 = adventurer;
    c2 = silver;
    c1_idx = G.handCount[0]/2;
    mine_idx = 0;
    //c2_qty = 

    G.hand[0][c1_idx] = c1;
    G.hand[0][mine_idx] = mine;
    
    handCount_prev = G.handCount[0];
    deckCount_prev = G.deckCount[0];
    discardCount_prev = G.discardCount[0];
    playedCount_prev = G.playedCardCount;
    c2_qty_Prev = G.supplyCount[c2];
    
    display_state(&G);    
    
    return_val = _mine(0, &G, mine_idx, c1_idx, c2); // int player, struct gameState *state, int pos, int c1, int c2
    
    display_state(&G);    
    
    c2_result = false;
    for (i=0; i<G.handCount[0]; i++)
    {
      if (G.hand[0][i] == c2)
      {
        c2_result = true;
        break;
      }
    }
    
    result =  ( (return_val == -1)
              );

    _assert(result, test2);


    
    
    return 0;
}
