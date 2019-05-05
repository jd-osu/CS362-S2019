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
const char FUNCTION[] = "_cardEffect(ADVENTURER)";

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

    int *bonus;

    int handCount_prev, deckCount_prev, discardCount_prev;
    
    int tr1, tr2, tr1_idx, tr2_idx;
    
    int return_val;
    
    bool result;


    // ************************************************************************************
    //TEST1
    const char test1[] = "1st 2 cards of deck are treasure cards";

    // clear the game state
    memset(&G, 23, sizeof(struct gameState));

    // initialize new game
    initializeGame(numPlayer, k, seed, &G);

    tr1 = 4;
    tr2 = 5;
    tr1_idx = 0;
    tr2_idx = 0;

    G.deck[0][tr1_idx] = tr1;
    G.deck[0][tr2_idx] = tr2;
    
    handCount_prev = G.handCount[0];
    deckCount_prev = G.deckCount[0];
    discardCount_prev = G.discardCount[0];
    
    return_val = cardEffect(7, 0, 0, 0, &G, 0, &bonus);
    
    result =  ( (return_val == 0) &&
                (G.handCount[0] - handCount_prev == 2) &&
                ((G.hand[0][G.handCount[0]-2] == tr1) && (G.hand[0][G.handCount[0]-1] == tr2)) &&
                (G.deckCount[0] + G.discardCount[0] - deckCount_prev - discardCount_prev == -2)
              );

    _assert(result, test1);


    // ************************************************************************************
    //TEST2
    const char test2[] = "no cards in deck";

    // clear the game state
    memset(&G, 23, sizeof(struct gameState));

    // initialize new game
    initializeGame(numPlayer, k, seed, &G);

    G.discardCount[0] = 10;
    G.deckCount[0] = 0;

    tr1 = 4;
    tr2 = 5;
    tr1_idx = 0;
    tr2_idx = 1;

    for (i=0; i<G.deckCount[0]; i++)
      G.deck[0][i] = 1;

    for (i=0; i<G.discardCount[0]; i++)
      G.discard[0][i] = 1;

    G.discard[0][tr1_idx] = tr1;
    G.discard[0][tr2_idx] = tr2;
    
    handCount_prev = G.handCount[0];
    deckCount_prev = G.deckCount[0];
    discardCount_prev = G.discardCount[0];
    
    return_val = cardEffect(7, 0, 0, 0, &G, 0, &bonus);
    
    result =  ( (return_val == 0) &&
                (G.handCount[0] - handCount_prev == 2) &&
                ((G.hand[0][G.handCount[0]-2] == tr1) && (G.hand[0][G.handCount[0]-1] == tr2)) &&
                (G.deckCount[0] + G.discardCount[0] - deckCount_prev - discardCount_prev == -2)
              );

    _assert(result, test2);


    // ************************************************************************************
    //TEST3
    const char test3[] = "only 1 treasure card";

    // clear the game state
    memset(&G, 23, sizeof(struct gameState));

    // initialize new game
    initializeGame(numPlayer, k, seed, &G);

    tr1 = 4;
    tr1_idx = 0;

    for (i=0; i<G.deckCount[0]; i++)
      G.deck[0][i] = 1;

    G.deck[0][tr1_idx] = tr1;
    
    handCount_prev = G.handCount[0];
    deckCount_prev = G.deckCount[0];
    discardCount_prev = G.discardCount[0];
    
    return_val = cardEffect(7, 0, 0, 0, &G, 0, &bonus);
    
    result =  ( (return_val == 0) &&
                (G.handCount[0] - handCount_prev == 1) &&
                (G.hand[0][G.handCount[0]-1] == tr1) &&
                (G.deckCount[0] + G.discardCount[0] - deckCount_prev - discardCount_prev == -1)
              );

    _assert(result, test3);
    
    // ************************************************************************************
    //TEST4
    const char test4[] = "no treasure cards";

    // clear the game state
    memset(&G, 23, sizeof(struct gameState));

    // initialize new game
    initializeGame(numPlayer, k, seed, &G);

    for (i=0; i<G.deckCount[0]; i++)
      G.deck[0][i] = 1;
    
    handCount_prev = G.handCount[0];
    deckCount_prev = G.deckCount[0];
    discardCount_prev = G.discardCount[0];
    
    return_val = cardEffect(7, 0, 0, 0, &G, 0, &bonus);
    
    result =  ( (return_val == 0) &&
                (G.handCount[0] - handCount_prev == 0) &&
                (G.deckCount[0] + G.discardCount[0] - deckCount_prev - discardCount_prev == 0)
              );

    _assert(result, test4);
    
    return 0;
}
