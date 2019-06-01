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
const char FUNCTION[] = "_salvager()";

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
    
  int selected_card_idx, selected_card, selected_card_cost;
  int num_total, num_total_prev, num_deck, num_deck_prev, num_hand, num_hand_prev, num_discard, num_discard_prev;
  int coins_prev, coins, eval_coins;
  int salvager_pos;
  int num_played, num_played_prev;
  int buys_prev, buys, eval_buys;
  int eval_trash, eval_played;
    
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
  selected_card_idx = get_random_number(0, num_hand_prev - 1);
  coins_prev = get_random_number(0, 100);
  buys_prev = get_random_number(0, 100);
  
  if (num_hand_prev == 0)
    salvager_pos = 0;
  else
    salvager_pos = get_random_number(0,num_hand_prev - 1);
   
  //printf("num_total_prev=%d\n", num_total_prev);
  //printf("num_deck_prev=%d\n", num_deck_prev);
  //printf("num_hand_prev=%d\n", num_hand_prev);
  //printf("num_discard_prev=%d\n", num_discard_prev);
  //printf("num_played_prev=%d\n", num_played_prev);
  //printf("selected_card_idx=%d\n", selected_card_idx);
  //printf("coins_prev=%d\n", coins_prev);
  //printf("buys_prev=%d\n", buys_prev);
  //printf("salvager_pos=%d\n", salvager_pos);
  
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
    G.hand[0][salvager_pos] = salvager;     
  
  G.coins = coins_prev;
  G.numBuys = buys_prev;

  if (num_hand_prev > 0)
  {
	  selected_card = G.hand[0][selected_card_idx];
    selected_card_cost = getCost(selected_card);
	  eval_coins = selected_card_cost;
	  eval_trash = 1;
    eval_played = 1;
  }
  else
  {
    selected_card = -1;
    selected_card_cost = -9;
    eval_coins = 0;
    eval_trash = 0;
    eval_played = -9;
  }

  eval_buys = buys_prev + 1;
  //printf("selected_card=%d\n", selected_card);
  //printf("selected_card_cost=%d\n", selected_card_cost);  
  //printf("eval_coins=%d\n", eval_coins);
  //printf("eval_buys=%d\n", eval_buys);
  //printf("eval_trash=%d\n", eval_trash);
  //printf("eval_played=%d\n", eval_played);



  //display_state(&G);


  return_val = _salvager(0, &G, salvager_pos, selected_card_idx);
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
  
  coins = G.coins;
  buys = G.numBuys;
  //printf("buys=%d\n", buys);
  //printf("coins=%d\n", coins);

  // evaluate result
  result = 	(	(return_val != 0) ||
  
				(	(return_val == 0) &&
					(num_total_prev == num_total + eval_trash) &&
					(num_hand_prev == num_hand + eval_trash + eval_played) &&
          (num_played == num_played_prev + eval_played) &&
					(G.playedCards[G.playedCardCount-1] == salvager) &&
					(coins == coins_prev + eval_coins) &&
					(buys == eval_buys) &&
					(num_deck == num_deck_prev) &&
          (num_discard == num_discard_prev)
				)
			);
  //printf("result=%d\n", result);
  
  
    
  //display_state(&G);
 
  // set up print string
  sprintf(test, "(dk:%d|hnd:%d|disc:%d|pld:%d|$:%d|bys:%d|svg:%d|sel:%d,%d)->(dk:%d|hnd:%d|disc:%d|pld:%d|$:%d|bys:%d); ret=%d",
					num_deck_prev,
					num_hand_prev,
					num_discard_prev,
          num_played_prev,
					coins_prev,
          buys_prev,
          salvager_pos,
          selected_card_idx, selected_card_cost,
					num_deck,
					num_hand,
					num_discard,
          num_played,
					coins,
          buys,
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
