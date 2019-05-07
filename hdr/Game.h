#ifndef GAME_H
#define GAME_H


#include "Cards.h"
#include "Player.h"

typedef struct vector2d{
    int x;
    int y;
} Vector2d;

void botPlay(Player *p, int diff, Hand *table, DataCard trumpInfo);
void setupGame(char *argv[]);
void runGame(PlayersInGame *pig, int mode, int diff);
int whoWin(Hand* table, DataCard trumpInfo, int mode);

#endif
