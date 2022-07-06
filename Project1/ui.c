#include <stdio.h>
#include "ui.h"
#include "game.h"
#include <string.h>
#include <stdlib.h>

void printEOFerror()
{
   fprintf(stderr, "Unexpected EOF\n");
   exit(EXIT_FAILURE);
}

void suddenEOF(int input)
{
   if(input == EOF)
      printEOFerror();

}
void remove_extra()
{
   int c;
   while( (c = getchar()) != '\n' && c != EOF);
   suddenEOF(c);

}

int getSeedNum()
{
   int seedNum, isValid;
   do{
      printf("Enter the seed for random number generation: ");
      isValid = scanf(" %d", &seedNum);

      remove_extra();

      if(isValid != 1) 
      {   printf("Seed must be an integer value, please try again\n");

      }
      
   } while(isValid != 1);
   
   return seedNum;
}

char getMaxLet()
{
   char let;
   int isValid;
   do{
      printf("Enter the maximum letter for the game (A-Z): ");
      isValid = scanf(" %c", &let);
      remove_extra();

      if(isValid != 1 || let < 'A' || let > 'Z'  )
      {
         printf("The letter must be uppercase A-Z, please try again\n");
         isValid = 0;

      }
   }  while(isValid != 1);
     
   return let;
}

int getPosNum()
{
   int PosNum, isValid;
   printf("Enter the number of positions for the game (1-8): ");
   isValid = scanf("%d", &PosNum);
      
   remove_extra();
      
   if(isValid != 1 || PosNum < 1 || PosNum > 8)
   {  
      printf("The number of positions must be 1-8, please try again\n");
      isValid = 0;
      getPosNum();   
   }

   return PosNum;
}

int getNumGuesses()
{
   int numGuesses, isValid;
   do { 
      printf("Enter the number of guesses allowed for the game: ");
      isValid = scanf("%d", &numGuesses);
      remove_extra();

      if(isValid != 1 || numGuesses < 1 )
      {
         printf("The number of guesses must be a "
            "positive integer, please try again\n");
         isValid = 0;

      }
   }while(isValid != 1);

   return numGuesses;
}

int isValidInput(Game *game)
{
   int isValid = 1; /* Start of as true; */
   int i;
   for(i = 0; i < game->posNum; i++)
   {
      if((game->guess[i] < 'A') || (game->guess[i]  > game->maxLet))
         isValid = 0;
   }
   
   return isValid;
}
void EnterGuess(int index, Game *game)
{
   int isValid = 0;

   do {   
      
      int i;
      printf("\nEnter guess %d: ", index);
      for(i = 0; i < game->posNum; i++)
         scanf(" %c", &game->guess[i]);   
       
      remove_extra();
      game->guess[game->posNum] = '\0';
 
      isValid = isValidInput(game);
      if(isValid != 1 )  
      {  
         printf("Invalid guess, please try again\n");
      }
       
   }  while(isValid != 1);

}
void playGame(Game game)
{
   int i;
   for(i = 1; i <= game.numGuess; i++)
   {
      Equality(&game, i);
      printf("Nope, %d exact guesses "
         "and %d inexact guesses\n" , game.ExactGuess, game.InExactGuess);
   }
   printf("\nGame over, you ran out of guesses. Better luck next time!\n");
}
