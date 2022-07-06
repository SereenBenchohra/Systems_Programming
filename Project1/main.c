#include <stdio.h>
#include "ui.h"
#include "game.h"
#include <stdlib.h>
#include <string.h>

int InValidInput(int argc, char *argv[])
{ 
   int Same = 0;
   int isItEqual;
   if(argc > 0 )
   {
      isItEqual = strcmp(argv[1], "-show");
      if(isItEqual == 0)
         Same = 1; 
   }
   return Same;

}
int main(int argc, char *argv[])
{
   
   int numArgs = argc - 1;
   int isSame,seed, getPos, numGuess;
   char maxLet;
   Game game;
   
   isSame = InValidInput(numArgs, argv);
   if((isSame == 0 && numArgs > 0) || numArgs > 1)
   {
      fprintf(stderr,"Usage: mastermind [-show]\n");
      exit(EXIT_FAILURE);
   }  
   
   seed = getSeedNum();
   maxLet = getMaxLet();
   getPos = getPosNum();
   numGuess = getNumGuesses();

   game = makeGame(seed, maxLet, getPos, numGuess);
   generateCombo(&game);

   isSame = InValidInput(numArgs, argv);
   if(isSame == 1) 
      printf("Initialized Game Board: %s\n", game.combo);  
   
   playGame(game);

   return 0;
}
