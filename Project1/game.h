#ifndef GAME_H
   #define GAME_H
   
   typedef struct
   {
      int seedNum; 
      char maxLet; 
      int posNum; 
      int numGuess;
      char combo[8];
      char guess[8];
      int ExactGuess;
      int InExactGuess;
   } Game;

   Game makeGame(int seedNum, char maxLet, int posNum, int numGuess );
   void generateCombo(Game *game);

   /*void IsEqual(Game *game, int i); */

   void ExactGuesses(Game *game, int i);
   void InExactGuesses(Game *game);

   void Equality(Game *game, int index);

#endif
