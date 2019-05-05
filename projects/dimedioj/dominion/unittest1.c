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

// bool type defined
typedef enum {false, true} bool;

const char PASS[] = "PASS";
const char FAIL[] = "FAIL";
const char FUNCTION[] = "_adventurer()";

int _assert(bool condition, const char *test_name)
{
  printf("%s: ", FUNCTION);
  
  if (condition == true)
    printf("%s", PASS);
  else
    printf("%s", FAIL);
  
  printf(" when test %s\n", test_name);
}


int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int p, r, handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    int handCount_prev, deckCount_prev, discardCount_prev;
    
    int tr1, tr2;
    
    bool result;

    // clear the game state
    memset(&G, 23, sizeof(struct gameState));

    // initialize new game
    initializeGame(numPlayer, k, seed, &G);

    printf ("TESTING _adventurer():\n");
    
    //TEST1 - 1st 2 cards of deck are treasure cards
    const char test1[] = "1st 2 cards of deck are treasure cards";
    tr1 = 4;
    tr2 = 5;

    G.deck[0][0] = tr1;
    G.deck[0][0] = tr2;
    
    handCount_prev = G.handCount[0];
    deckCount_prev = G.deckCount[0];
    discardCount_prev = G.discardCount[0];
    
    // CALL FUNCTION
    _adventurer(0, &G);
    
    result =  (  (G.handCount[0] - handCount_prev == 2) &&
                ((G.hand[0][G.handCount[0]-2] == tr1) && (G.hand[0][G.handCount[0]-1] == tr2)) &&
                (G.deckCount[0] + G.discardCount[0] - deckCount_prev - discardCount_prev == -2)
              );
    /*
    printf("Hand diff = %d, expected = %d\n", G.handCount[0] - handCount_prev, 2);
    printf("Last two in hand = %d,%d, expected %d, %d\n", G.hand[0][G.handCount[0]-2], G.hand[0][G.handCount[0]-1], tr1, tr2);
    printf("Deck/discard diff = %d, expected = %d\n", G.deckCount[0] + G.discardCount[0] - deckCount_prev - discardCount_prev, -2);
    */

    _assert(result, test1);

    return 0;
}
