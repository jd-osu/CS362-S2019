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
  
  printf("BUYS: %d\n", state->numBuys);
  printf("\n");
  
  printf("COINS: %d\n", state->coins);
  printf("\n");
  
}



int _assert(bool condition, const char *test_name)
{
  //printf("%s: ", FUNCTION);
  
  if (condition == true);
    //printf("%s", PASS);
  else
    printf("%s: %s when %s\n", FUNCTION, FAIL, test_name);
  
  //printf(" when %s\n", test_name);
}

int get_random_number(int low, int high)
{
  int number;
  if ((high - low + 1) != 0)
    number = low + (rand() % (high-low+1));
  else
    number = 0;
  
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
    
  int c1_idx, c1, c2, c1_cost, c2_cost;
  int num_total, num_total_prev, num_deck, num_deck_prev, num_hand, num_hand_prev, num_discard, num_discard_prev;
  int mine_pos;
  int num_played, num_played_prev;
  int eval_cost, eval_played, eval_trash, eval_gained;
  int c2_supply_prev, c2_supply;
  int gained_card, played_card;
    
  int return_val;
    
  bool result;

  // ************************************************************************************
  //TEST
  char test[MAX_STR];

  // clear the game state
  memset(&G, 23, sizeof(struct gameState));

  // initialize new game
  initializeGame(numPlayer, k, seed, &G);

  // generate random parameters
  num_total_prev = get_random_number(0,500);
  num_deck_prev = get_random_number(0, num_total_prev);
  num_discard_prev = get_random_number(0, num_total_prev - num_deck_prev);
  num_hand_prev = get_random_number(0, num_total_prev - num_deck_prev - num_discard_prev);
  num_played_prev = num_total_prev - num_deck_prev - num_discard_prev - num_hand_prev;
  c1_idx = get_random_number(0, num_hand_prev - 1);
  c2 = get_random_number(0, treasure_map);
  c2_supply_prev = get_random_number(0,10); 
  
  if (num_hand_prev == 0)
    mine_pos = 0;
  else
    mine_pos = get_random_number(0,num_hand_prev - 1);
   
  //printf("num_total_prev=%d\n", num_total_prev);
  //printf("num_deck_prev=%d\n", num_deck_prev);
  //printf("num_hand_prev=%d\n", num_hand_prev);
  //printf("num_discard_prev=%d\n", num_discard_prev);
  //printf("num_played_prev=%d\n", num_played_prev);
  //printf("c1_idx=%d\n", c1_idx);
  //printf("c2=%d\n", c2);
  //printf("c2_supply_prev=%d\n", c2_supply_prev);
  //printf("mine_pos=%d\n", mine_pos);
  
  // modify new game based on random parameters  
  G.deckCount[0] = num_deck_prev;
  G.handCount[0] = num_hand_prev;
  G.discardCount[0] = num_discard_prev;
  G.playedCardCount = num_played_prev;

  // populate deck, hand and discard with random cards	
  for (i = 0; i < G.deckCount[0]; i++)
    G.deck[0][i] = get_random_card();

  for (i = 0; i < G.handCount[0]; i++)
    G.hand[0][i] = get_random_card();      
	  
  for (i = 0; i < G.discardCount[0]; i++)
    G.discard[0][i] = get_random_card();
  
  for (i = 0; i < G.playedCardCount; i++)
    G.playedCards[i] = get_random_card();

  if (num_hand_prev > 0)
    G.hand[0][mine_pos] = mine;
  
  if (num_hand_prev > 0)
  {
	  c1 = G.hand[0][c1_idx];
    c1_cost = getCost(c1);
    c2_cost = getCost(c2);
	  eval_cost = 3;
	  eval_trash = 1;
    if (c1_idx == mine_pos)
      eval_played = 0;
    else
      eval_played = 1;
    if (c2_supply_prev == 0)
      eval_gained = 0;
    else
      eval_gained = 1;
  }
  else
  {
	  c1 = -9;
    c1_cost = -9;
    c2_cost = getCost(c2);
	  eval_cost = 3;
	  eval_trash = 0;
    eval_played = -9;
    if (c2_supply_prev == 0)
      eval_gained = 0;
    else
      eval_gained = 1;
  }

  //printf("c1=%d\n", c1);
  //printf("c1_cost=%d\n", c1_cost);  
  //printf("c2_cost=%d\n", c2_cost);
  //printf("eval_cost=%d\n", eval_cost);
  //printf("eval_trash=%d\n", eval_trash);
  //printf("eval_played=%d\n", eval_played);
  //printf("eval_gained=%d\n", eval_gained);

  //randomize c2 supply
  G.supplyCount[c2] = c2_supply_prev;

  //display_state(&G);

  return_val = _mine(0, &G, mine_pos, c1_idx, c2);
  //printf("return_val=%d\n", return_val);

  // get resulting data
  num_deck = G.deckCount[0];
  num_hand = G.handCount[0];
  num_discard = G.discardCount[0];
  num_played = G.playedCardCount;
  num_total = num_deck + num_hand + num_discard + num_played;
  //printf("num_total=%d\n", num_total);
  //printf("num_deck=%d\n", num_deck);
  //printf("num_hand=%d\n", num_hand);
  //printf("num_discard=%d\n", num_discard);
  //printf("num_played=%d\n", num_played);
  
  if (eval_gained != 0)
    gained_card = G.hand[0][G.handCount[0]-1];
  else
    gained_card = -9;
  played_card = G.playedCards[G.playedCardCount-1];
  c2_supply = G.supplyCount[c2];
  //printf("gained_card=%d\n", gained_card);
  //printf("played_card=%d\n", played_card);
  //printf("c2_supply=%d\n", c2_supply);

  // evaluate result
  result = 	(	(return_val != 0) ||
  
				(	(return_val == 0) &&
					(num_total_prev == num_total + eval_trash) &&
					(num_hand_prev == num_hand + eval_trash + eval_played) &&
          (num_played == num_played_prev + eval_played) &&
					((played_card == mine) || (eval_played == 0)) &&
					((gained_card == c2) || (eval_gained == 0)) &&
					((c2_cost <= c1_cost + eval_cost) || (eval_gained == 0)) &&
					(c2_supply_prev == c2_supply + eval_gained) &&
					(num_deck == num_deck_prev) &&
          (num_discard == num_discard_prev)
				)
			);
  //printf("result=%d\n", result);
  

  //display_state(&G);
 
  // set up print string 
  sprintf(test, "(dk:%d|hnd:%d|disc:%d|pld:%d|qty:%d|mn:%d|c1:[%d]=%d,%d|c2:%d,%d)->(dk:%d|hnd:%d|disc:%d|pld:%d|qty:%d|gnd:%d); ret=%d",
					num_deck_prev,
					num_hand_prev,
					num_discard_prev,
          num_played_prev,
					c2_supply_prev,
          mine_pos,
          c1_idx, c1, c1_cost,
          c2, c2_cost,
					num_deck,
					num_hand,
					num_discard,
          num_played,
					c2_supply,
          gained_card,
					return_val);

  //printf("test=%s\n", test);

  _assert(result, test);
}

int main() {
  srand(time(NULL));

  int trials = 100;
  int current = 1;
  
  while (current <= trials)
  {
	test_run();

    current++;  
  }
  
    return 0;
}
