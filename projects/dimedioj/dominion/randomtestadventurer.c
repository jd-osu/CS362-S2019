/* -----------------------------------------------------------------------
 * Author: Jason DiMedio
 * CS362, Spring 2019
 * NOTE: 
 * The following code was adapted from unittest1.c, which was submitted as
 * a part of Assignment 3 for OSU CS362 (Spring 2019).
 *
 * In turn, unittest1.c was adapted from testUpdateCoins.c provided as a
 * template to be used in Assignment 3 for CS362.
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "rngs.h"

#define MAX_HAND 500
#define MAX_DECK 500
#define MAX_STR 1000

#define MAX_PLAYERS 4

// bool type defined
typedef enum {false, true} bool;

const char PASS[] = "PASS";
const char FAIL[] = "FAIL";
const char FUNCTION[] = "_adventurer()";

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

int get_random_number(int low, int high)
{

  int number = low + (rand() % (high-low+1));
  
  return number;
}

int get_random_card()
{
  return get_random_number(0,26);
}

void test_run()
{
  int i;
  int seed = 1000;
  int numPlayer = 2;
  int p, r, handCount;
  int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
  struct gameState G;

  int handCount_prev, deckCount_prev, discardCount_prev;
    
  int num_tr_found, eval_tr, tr1, tr2, hand1, hand2;
  int num_total, num_total_prev, num_deck, num_deck_prev, num_hand, num_hand_prev, num_discard, num_discard_prev;
  int num_deck_tr = 0;
  int num_hand_tr = 0;
  int num_discard_tr = 0;
  int num_deck_tr_prev = 0;
  int num_hand_tr_prev = 0;
  int num_discard_tr_prev = 0;
    
  int return_val;
    
  bool result;

  // ************************************************************************************
  //TEST1
  const char test[MAX_STR];

  // clear the game state
  memset(&G, 23, sizeof(struct gameState));

  // initialize new game
  initializeGame(numPlayer, k, seed, &G);

  // generate random parameters
  num_total_prev = get_random_number(0,500);
  num_deck_prev = get_random_number(0, num_total_prev);
  num_discard_prev = get_random_number(0, num_total_prev - num_deck_prev);
  num_hand_prev = num_total_prev - num_deck_prev - num_discard_prev;
  printf("num_total_prev=%d\n", num_total_prev);
  printf("num_deck_prev=%d\n", num_deck_prev);
  printf("num_hand_prev=%d\n", num_hand_prev);
  printf("num_discard_prev=%d\n", num_discard_prev);
  
  // modify new game based on random parameters  
  G.deckCount[0] = num_deck_prev;
  G.handCount[0] = num_hand_prev;
  G.discardCount[0] = num_discard_prev;

  // populate deck, hand and discard with random cards	
  for (i = 0; i < G.deckCount[0]; i++)
    G.deck[0][i] = get_random_card();

  for (i = 0; i < G.handCount[0]; i++)
    G.hand[0][i] = get_random_card();      
	  
  for (i = 0; i < G.discardCount[0]; i++)
    G.discard[0][i] = get_random_card();

  // count how many treasures are in each pile
  for (i = 0; i < G.deckCount[0]; i++)
  {
	  if (G.deck[0][i] > 3 && G.deck[0][i] < 7)
		  num_deck_tr_prev++;
  }

  for (i = 0; i < G.handCount[0]; i++)
  {
	  if (G.hand[0][i] > 3 && G.hand[0][i] < 7)
		  num_hand_tr_prev++;
  }      
	  
  for (i = 0; i < G.discardCount[0]; i++)
  {
	  if (G.discard[0][i] > 3 && G.discard[0][i] < 7)
		  num_discard_tr_prev++;
  }

  if (num_deck_tr_prev >= 2)
	  eval_tr = 2;
  else if (num_deck_tr_prev == 1)
	  eval_tr = 1;
  else
	  eval_tr = 0;
  
  num_tr_found = 0;

  // find the treasures in the deck
  tr1 = -1;
  tr2 = -1;
  for (i = G.deckCount[0]-1; i >= 0; i--)
  {
	  if (G.deck[0][i] > 3 && G.deck[0][i] < 7)
	  {
		num_tr_found++;
		
		if (num_tr_found == 1)
			tr1 = G.deck[0][i];
		else if (num_tr_found == 2)
		{
			tr2 = G.deck[0][i];
			break;
		}
	  }
  }

  printf("num_deck_tr_prev=%d\n", num_deck_tr_prev);
  printf("num_hand_tr_prev=%d\n", num_hand_tr_prev);
  printf("num_discard_tr_prev=%d\n", num_discard_tr_prev);
  printf("tr1=%d\n", tr1);
  printf("tr2=%d\n", tr2);
  printf("num_tr_found=%d\n", num_tr_found);
  printf("eval_tr=%d\n", eval_tr);
  
  //display_state(&G);




  return_val = _adventurer(0, &G);
  printf("return_val=%d\n", return_val);

  // get resulting data
  num_deck = G.deckCount[0];
  num_hand = G.handCount[0];
  num_discard = G.discardCount[0];
  num_total = num_deck + num_hand + num_discard;
  printf("num_total=%d\n", num_total);
  printf("num_deck=%d\n", num_deck);
  printf("num_hand=%d\n", num_hand);
  printf("num_discard=%d\n", num_discard);
  
  // count how many treasures are in each pile
  for (i = 0; i < G.deckCount[0]; i++)
  {
	  if (G.deck[0][i] > 3 && G.deck[0][i] < 7)
		  num_deck_tr++;
  }

  for (i = 0; i < G.handCount[0]; i++)
  {
	  if (G.hand[0][i] > 3 && G.hand[0][i] < 7)
		  num_hand_tr++;
  }      
	  
  for (i = 0; i < G.discardCount[0]; i++)
  {
	  if (G.discard[0][i] > 3 && G.discard[0][i] < 7)
		  num_discard_tr++;
  }
  printf("num_deck_tr=%d\n", num_deck_tr);
  printf("num_hand_tr=%d\n", num_hand_tr);
  printf("num_discard_tr=%d\n", num_discard_tr);

  // get 1-2 most recently added cards to hand
  hand1 = -1;
  hand2 = -1;
  if (G.handCount[0] >= 2)
    hand1 = G.hand[0][G.handCount[0]-2];
  if (G.handCount[0] >= 1)
	  hand2 = G.hand[0][G.handCount[0]-1];
  printf("hand1=%d\n", hand1);
  printf("hand2=%d\n", hand2);
  

  // evaluate result
  result = 	(	(return_val != 0) ||
  
				(	(return_val == 0) &&
					(num_deck + eval_tr + (num_discard - num_discard_prev) == num_deck_prev) &&
					(num_deck_tr_prev == num_deck_tr + eval_tr) &&
					(num_hand == num_hand_prev + eval_tr) &&
					(num_hand_tr == num_hand_tr_prev + eval_tr) &&
					(num_discard_tr_prev == num_discard_tr) &&
					(num_total_prev == num_total) &&
					(tr1 == hand1) &&
					(tr2 == hand2)
				)
			);
  printf("result=%d\n", result);
  
  
    
  //display_state(&G);
    
  // set up print string
  sprintf(test, "(deck:%d,%d_tr|hand:%d,%d_tr|discard:%d,%d_tr)->(deck:%d,%d_tr|hand:%d,%d_tr|discard:%d,%d_tr); return=%d",
					num_deck_prev, num_deck_tr_prev,
					num_hand_prev, num_hand_tr_prev,
					num_discard_prev, num_discard_tr_prev,
					num_deck, num_deck_tr,
					num_hand, num_hand_tr,
					num_discard, num_discard_tr,
					return_val);


    _assert(result, test);
	
}

int main() {

/*
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int p, r, handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    int handCount_prev, deckCount_prev, discardCount_prev;
    
    int num_tr, eval_tr, tr1, tr2, tr1_idx, tr2_idx;
	int num_deck, num_hand, num_discard;
    
    int return_val;
    
    bool result;


    // ************************************************************************************
    //TEST1
    const char test1[] = "1st 2 cards of deck are treasure cards";

    // clear the game state
    memset(&G, 23, sizeof(struct gameState));

    // initialize new game
    initializeGame(numPlayer, k, seed, &G);

	// modify new game based on random parameters
	num_deck = 
	



    tr1 = 4;
    tr2 = 5;
    tr1_idx = G.deckCount[0]-1;
    tr2_idx = G.deckCount[0]-2;

    G.deck[0][tr1_idx] = tr1;
    G.deck[0][tr2_idx] = tr2;
    
    handCount_prev = G.handCount[0];
    deckCount_prev = G.deckCount[0];
    discardCount_prev = G.discardCount[0];
    
    //display_state(&G);    
    
    return_val = _adventurer(0, &G);
    
    //display_state(&G);    
    
    result =  ( (return_val == 0) &&
                (G.handCount[0] - handCount_prev == num_tr) &&
				(num_tr <= 2) &&
				(G.handCount[0] - handCount_prev == num_tr) &&
                ((G.hand[0][G.handCount[0]-2] == tr1) && (G.hand[0][G.handCount[0]-1] == tr2)) &&
                (G.deckCount[0] + G.discardCount[0] - deckCount_prev - discardCount_prev == -2)
              );

    _assert(result, test1);


    // ************************************************************************************
    //TEST2
    const char test2[] = "last 2 cards of deck are treasure cards";

    // clear the game state
    memset(&G, 23, sizeof(struct gameState));

    // initialize new game
    initializeGame(numPlayer, k, seed, &G);

    tr1 = 4;
    tr2 = 5;
    tr1_idx = 1;
    tr2_idx = 0;

    for (i=0; i<G.deckCount[0]; i++)
      G.deck[0][i] = 1;


    G.deck[0][tr1_idx] = tr1;
    G.deck[0][tr2_idx] = tr2;
    
    handCount_prev = G.handCount[0];
    deckCount_prev = G.deckCount[0];
    discardCount_prev = G.discardCount[0];
    
    //display_state(&G);    
    
    return_val = _adventurer(0, &G);
    
    //display_state(&G);  
    
    result =  ( (return_val == 0) &&
                (G.handCount[0] - handCount_prev == 2) &&
                ((G.hand[0][G.handCount[0]-2] == tr1) && (G.hand[0][G.handCount[0]-1] == tr2)) &&
                (G.deckCount[0] + G.discardCount[0] - deckCount_prev - discardCount_prev == -2) &&
                (G.discardCount[0] == deckCount_prev - 2) &&
                (G.deckCount[0] == 0)
              );

    _assert(result, test2);


    // ************************************************************************************
    //TEST3
    const char test3[] = "1 treasure card in deck, 1 treasure card in discard";

    // clear the game state
    memset(&G, 23, sizeof(struct gameState));

    // initialize new game
    initializeGame(numPlayer, k, seed, &G);

    G.discardCount[0] = 5;

    tr1 = 4;
    tr2 = 5;
    tr1_idx = G.deckCount[0]/2;
    tr2_idx = G.discardCount[0]/2;

    for (i=0; i<G.deckCount[0]; i++)
      G.deck[0][i] = 1;

    for (i=0; i<G.discardCount[0]; i++)
      G.discard[0][i] = 1;

    G.deck[0][tr1_idx] = tr1;
    G.discard[0][tr2_idx] = tr2;
    
    handCount_prev = G.handCount[0];
    deckCount_prev = G.deckCount[0];
    discardCount_prev = G.discardCount[0];
    
    //display_state(&G);    
    
    return_val = _adventurer(0, &G);
    
    //display_state(&G); 
    
    result =  ( (return_val == 0) && 
                (G.handCount[0] - handCount_prev == 2) &&
                ((G.hand[0][G.handCount[0]-2] == tr1) && (G.hand[0][G.handCount[0]-1] == tr2)) &&
                (G.deckCount[0] + G.discardCount[0] - deckCount_prev - discardCount_prev == -2)
              );

    _assert(result, test3);
    
  */
	srand(time(NULL));
	test_run();
  
    return 0;
}
