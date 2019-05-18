#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int _salvager(int player, struct gameState *state, int pos, int c1) {

  //+1 buy
  state->numBuys++;
			
  if (c1)
	{
	  //gain coins equal to trashed card
	  state->coins = state->coins + getCost( handCard(c1, state) );
	  
    //trash card
	  discardCard(c1, player, state, 1);	
	}
			
  //discard card
  discardCard(pos, player, state, 0);
  
  return 0;
}
