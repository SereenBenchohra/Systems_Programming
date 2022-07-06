#include "game.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ui.h"

Game makeGame(int seedNum, char maxLet, int posNum, int numGuess )
{
   
   Game game;   
   game.seedNum = seedNum;
   game.maxLet = maxLet;
   game.posNum = posNum;
   game.numGuess = numGuess;

   return game;

}

void generateCombo(Game *game) 
{ 
   int diff; 
   int i;

   srand(game->seedNum);
   diff = game->maxLet - 'A' + 1 ;

   for(i = 0; i < game->posNum; i++)
   {   
      game->combo[i] =  'A' + (rand() % diff);
   }
   game->combo[game->posNum] = '\0';
}

void ExactGuesses(Game *game, int index)
{ 
   int i; 
   game->ExactGuess= 0;
   for(i = 0; i < game->posNum; i++)
   {
      if(game->guess[i] == game->combo[i])
      {
         game->ExactGuess++;
         game->guess[i] = '1';
         game->combo[i] = '1';
      }

   }

   if(game->ExactGuess == game->posNum)
   {
      printf("\nWow, you won in %d guesses - well done!\n", index);
      exit(EXIT_SUCCESS);
   }
}

void checkComboGuess(Game *game, int i)
{
   int j;
   for(j = 0; j < game->posNum; j++)
   {
      if(game->guess[i] != '1' && game->guess[i] == game->combo[j])
      {
         game->InExactGuess++;
         game->guess[i] = '1';
         game->combo[j] = '1';
      }
   }
}

void InExactGuesses(Game *game)
{

   int i;
   game->InExactGuess = 0;
   for(i = 0; i < game->posNum; i++)
      checkComboGuess(game, i);

}

void Equality(Game *game, int index)
{

   generateCombo(game);
   EnterGuess(index, game);
   ExactGuesses(game, index);
   InExactGuesses(game);

}
