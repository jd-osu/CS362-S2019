#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int _adventurer(int player, struct gameState *state) {
  int drawntreasure=0;
  int cardDrawn;
  int temphand[MAX_HAND];
  int z = 0;// this is the counter for the temp hand


  while(drawntreasure<2){
    if (state->deckCount[player] < 1){//if the deck is empty we need to shuffle discard and add to deck
      shuffle(player, state);
    }
    
    drawCard(player, state);
	
    cardDrawn = state->hand[player][state->handCount[player]-1];//top card of hand is most recently drawn card.
    
    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
      drawntreasure++;
    else{
      temphand[z]=cardDrawn;
      state->handCount[player]--; //this should just remove the top card (the most recently drawn one).
      z++;
    }
  }

  while(z-1>=0){
    state->discard[player][state->discardCount[player]++]=temphand[z-1]; // discard all cards in play that have been drawn
    
    z=z-1;
  }
  
  return 0;
}