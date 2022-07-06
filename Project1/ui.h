#include "game.h"

#include <stdio.h>
#include "game.h"
#include <string.h>
#include <stdlib.h>

#ifndef UI_H
#define UI_H

void remove_extra();
int getSeedNum();
char getMaxLet();
int getPosNum();
int getNumGuesses();
void EnterGuess(int index, Game *game);
void playGame(Game game);

#endif
