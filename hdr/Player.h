#ifndef PLAYER_H
#define PLAYER_H

#include "Cards.h"

typedef struct player{
    int points;
    Hand* h;
    char* name;
} Player;

Player* createPlayer(char* name);
void showPlayerStats(Player *p);
void insertInTable(Player *p, Hand *table, int index);
void pickInDeck(Player *p, Hand *deck);

#endif
