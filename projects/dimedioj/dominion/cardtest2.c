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
const char FUNCTION[] = "cardEffect(SMITHY)";

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

    smithy_idx = 0;

    G.hand[0][smithy_idx] = smithy;
    
    handCount_prev = G.handCount[0];
    deckCount_prev = G.deckCount[0];
    discardCount_prev = G.discardCount[0];
    card1 = G.deck[0][0];
    card2 = G.deck[0][1];
    card3 = G.deck[0][2];
    
    return_val = cardEffect(smithy, 0, 0, 0, &G, smithy_idx, bonus);
    
    result =  ( (return_val == 0) &&
                (G.handCount[0] - handCount_prev == 3-1) &&
                ((G.hand[0][G.handCount[0]-3] == card1) && (G.hand[0][G.handCount[0]-2] == card2) && (G.hand[0][G.handCount[0]-1] == card3)) &&
                (G.discardCount[0] == discardCount_prev + 1)
              );

    _assert(result, test1);



    
    return 0;
}
