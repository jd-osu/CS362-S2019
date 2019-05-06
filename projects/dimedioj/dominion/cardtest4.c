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
const char FUNCTION[] = "cardEffect(SALVAGER)";

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
  
  printf("BUYS: %d\n", state->numBuys);
  printf("\n");
  
  printf("COINS: %d\n", state->coins);
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

    int handCount_prev, deckCount_prev, discardCount_prev, playedCount_prev, coins_prev, buys_prev;
    
    int c1, c1_idx, salv_idx;
    
    int *bonus;
    
    int return_val;
    
    bool result, c1_salv_result;


    // ************************************************************************************
    //TEST1
    const char test1[] = "c1=mine, c1_idx=0, salv_idx = last";

    // clear the game state
    memset(&G, 23, sizeof(struct gameState));

    // initialize new game
    initializeGame(numPlayer, k, seed, &G);

    c1 = mine;
    c1_cost = getCost(c1);
    c1_idx = 0;
    salv_idx = G.handCount[0]-1;

    for (i=0; i<G.handCount[0]; i++)
      G.hand[0][i] = 1;

    G.hand[0][c1_idx] = c1;
    G.hand[0][salv_idx] = salvager;
    
    handCount_prev = G.handCount[0];
    deckCount_prev = G.deckCount[0];
    discardCount_prev = G.discardCount[0];
    playedCount_prev = G.playedCardCount;
    coins_prev = G.coins;
    buys_prev = G.buys;
    
    display_state(&G);    
    
    return_val = cardEffect(salvager, c1_idx, 0, 0, &G, salv_idx, bonus);
    
    display_state(&G);    
    
    c1_salv_result = false;
    for (i=0; i<G.handCount[0]; i++)
    {
      if (G.hand[0][i] == c1 || G.hand[0][i] == salvager)
      {
        c1_salv_result = true;
        break;
      }
    }
    
    result =  ( (return_val == 0) &&
                (G.handCount[0] - handCount_prev == -2) &&
                (G.playedCardCount - playedCount_prev == 1) &&
                (G.discardCount[0] - discardCount_prev == 0) &&
                (G.deckCount[0] - deckCount_prev == 0) &&
                (c1_salv_result == false) &&
                (G.coins - coins_prev == c1_cost) &&
                (G.numBuys - buys_prev == 1)
              );

    _assert(result, test1);
    
    


    
    return 0;
}
