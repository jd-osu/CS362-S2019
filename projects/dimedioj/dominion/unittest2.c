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
const char FUNCTION[] = "_smithy()";

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

    int handCount_prev, deckCount_prev, playedCount_prev;
    
    int smithy_idx, card1, card2, card3;
    
    int return_val;
    
    bool result;


    // ************************************************************************************
    //TEST1
    const char test1[] = "deck count > 3, smithy card is first in hand";

    // clear the game state
    memset(&G, 23, sizeof(struct gameState));

    // initialize new game
    initializeGame(numPlayer, k, seed, &G);

    smithy_idx = G.handCount[0]-1;

    G.hand[0][smithy_idx] = smithy;
    
    handCount_prev = G.handCount[0];
    deckCount_prev = G.deckCount[0];
    playedCount_prev = G.playedCardCount;
    card1 = G.deck[0][G.deckCount[0]-1];
    card2 = G.deck[0][G.deckCount[0]-2];
    card3 = G.deck[0][G.deckCount[0]-3];

    //display_state(&G);
    
    return_val = _smithy(0, &G, smithy_idx);

    //display_state(&G);
    
    result =  ( (return_val == 0) &&
                (G.handCount[0] - handCount_prev == 3-1) &&
                ((G.hand[0][G.handCount[0]-3] == card1) && (G.hand[0][G.handCount[0]-2] == card2) && (G.hand[0][G.handCount[0]-1] == card3)) &&
                (G.playedCardCount == playedCount_prev + 1)
              );

    _assert(result, test1);

    // ************************************************************************************
    //TEST2
    const char test2[] = "deck is empty, discard is empty";

    // clear the game state
    memset(&G, 23, sizeof(struct gameState));

    // initialize new game
    initializeGame(numPlayer, k, seed, &G);

    smithy_idx = G.handCount[0]-1;

    G.hand[0][smithy_idx] = smithy;
    
    G.deckCount[0] = 0;
    G.discardCount[0] = 0;
    
    //display_state(&G);
    
    return_val = _smithy(0, &G, smithy_idx);

    //display_state(&G);
    
    printf("return=%d\n", return_val);
    
    result =  ( (return_val == -1)
              );

    _assert(result, test2);


    // ************************************************************************************
    //TEST3
    const char test3[] = "deck count > 3, smithy card is only card in hand";

    // clear the game state
    memset(&G, 23, sizeof(struct gameState));

    // initialize new game
    initializeGame(numPlayer, k, seed, &G);

    smithy_idx = 0;

    G.handCount[0] = 1;

    G.hand[0][smithy_idx] = smithy;
    
    handCount_prev = G.handCount[0];
    deckCount_prev = G.deckCount[0];
    playedCount_prev = G.playedCardCount;
    card1 = G.deck[0][G.deckCount[0]-1];
    card2 = G.deck[0][G.deckCount[0]-2];
    card3 = G.deck[0][G.deckCount[0]-3];

    display_state(&G);
    
    return_val = _smithy(0, &G, smithy_idx);

    display_state(&G);
    
    result =  ( (return_val == 0) &&
                (G.handCount[0] - handCount_prev == 3-1) &&
                ((G.hand[0][G.handCount[0]-3] == card1) && (G.hand[0][G.handCount[0]-2] == card2) && (G.hand[0][G.handCount[0]-1] == card3)) &&
                (G.playedCardCount == playedCount_prev + 1)
              );

    _assert(result, test3);
    
    return 0;
}
