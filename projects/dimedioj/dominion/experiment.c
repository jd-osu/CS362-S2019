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

/*
int num_treasures(int cards[], int n)
{
  int count = 0;
  int i;
  for (i=0; i<n; i++)
  {
    if (cards[i] == copper || cards[i] == silver || cards[i] == gold)
      count++;
  }
  
  return count;
}
*/

int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int p, r, handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    
    printf ("TESTING _adventurer():\n");

    // clear the game state
    memset(&G, 23, sizeof(struct gameState));

    // initialize new game
    initializeGame(numPlayer, k, seed, &G);

    for (p=0; p<numPlayer; p++)
    {
      printf("player=%d\n", p);
      
      printf("handCount=%d\n", G.handCount[p]);
      for (i=0; i<50; i++)
      {
        printf("%d : %d\n", i, G.hand[p][i]);
      }
      
      printf("deckCount=%d\n", G.deckCount[p]);
      for (i=0; i<50; i++)
      {
        printf("%d : %d\n", i, G.deck[p][i]);
      }
      
      printf("discardCount=%d\n", G.discardCount[p]);
      for (i=0; i<50; i++)
      {
        printf("%d : %d\n", i, G.discard[p][i]);
      }
      
      printf("\n");
    }

  int money = 0;
  int smithyPos = -1;
  int adventurerPos = -1;

  int numSmithies = 0;
  int numAdventurers = 0;

  int round = 0;

  while (round < 5) {
    money = 0;
    smithyPos = -1;
    adventurerPos = -1;
    for (i = 0; i < numHandCards(&G); i++) {
      if (handCard(i, &G) == copper)
    money++;
      else if (handCard(i, &G) == silver)
    money += 2;
      else if (handCard(i, &G) == gold)
    money += 3;
      else if (handCard(i, &G) == smithy)
    smithyPos = i;
      else if (handCard(i, &G) == adventurer)
    adventurerPos = i;
    }

    if (whoseTurn(&G) == 0) {
      if (smithyPos != -1) {
        printf("0: smithy played from position %d\n", smithyPos);
        playCard(smithyPos, -1, -1, -1, &G);
        printf("smithy played.\n");
        money = 0;
        i=0;
        while(i<numHandCards(&G)){
          if (handCard(i, &G) == copper){
            playCard(i, -1, -1, -1, &G);
            money++;
          }
          else if (handCard(i, &G) == silver){
            playCard(i, -1, -1, -1, &G);
            money += 2;
          }
          else if (handCard(i, &G) == gold){
            playCard(i, -1, -1, -1, &G);
            money += 3;
          }
          i++;
        }
      }

      if (money >= 8) {
        printf("0: bought province\n");
        buyCard(province, &G);
      }
      else if (money >= 6) {
        printf("0: bought gold\n");
        buyCard(gold, &G);
      }
      else if ((money >= 4) && (numSmithies < 2)) {
        printf("0: bought smithy\n");
        buyCard(smithy, &G);
        numSmithies++;
      }
      else if (money >= 3) {
        printf("0: bought silver\n");
        buyCard(silver, &G);
      }

      printf("0: end turn\n");
      endTurn(&G);
    }
    else {
      if (adventurerPos != -1) {
        printf("1: adventurer played from position %d\n", adventurerPos);
        playCard(adventurerPos, -1, -1, -1, &G);
        money = 0;
        i=0;
        while(i<numHandCards(&G)){
          if (handCard(i, &G) == copper){
            playCard(i, -1, -1, -1, &G);
            money++;
          }
          else if (handCard(i, &G) == silver){
            playCard(i, -1, -1, -1, &G);
            money += 2;
          }
          else if (handCard(i, &G) == gold){
            playCard(i, -1, -1, -1, &G);
            money += 3;
          }
          i++;
        }
      }

      if (money >= 8) {
        printf("1: bought province\n");
        buyCard(province, &G);
      }
      else if ((money >= 6) && (numAdventurers < 2)) {
        printf("1: bought adventurer\n");
        buyCard(adventurer, &G);
        numAdventurers++;
      }else if (money >= 6){
        printf("1: bought gold\n");
	    buyCard(gold, &G);
        }
      else if (money >= 3){
        printf("1: bought silver\n");
	    buyCard(silver, &G);
      }
      printf("1: endTurn\n");

      endTurn(&G);
    }
    
        for (p=0; p<numPlayer; p++)
    {
      printf("player=%d\n", p);
      
      printf("handCount=%d\n", G.handCount[p]);
      for (i=0; i<50; i++)
      {
        printf("%d : %d\n", i, G.hand[p][i]);
      }
      
      printf("deckCount=%d\n", G.deckCount[p]);
      for (i=0; i<50; i++)
      {
        printf("%d : %d\n", i, G.deck[p][i]);
      }
      
      printf("discardCount=%d\n", G.discardCount[p]);
      for (i=0; i<50; i++)
      {
        printf("%d : %d\n", i, G.discard[p][i]);
      }
      
      printf("\n");
    }
    
    round++;
  }



    printf("All done!\n");

    return 0;
}
