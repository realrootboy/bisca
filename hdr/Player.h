#ifndef PLAYER_H
#define PLAYER_H

#include "Cards.h"

typedef struct player{
    int points;
    Hand* h;
    char* name;
} Player;

typedef struct playersInGame{
    Player *p;
    struct playersInGame *next;
} PlayersInGame;

PlayersInGame* createPlayersInGame();
void destroyPlayersInGame(PlayersInGame *pig);
void insertPlayerInGame(PlayersInGame *pig, Player *p);

Player* createPlayer(char *name);
void destroyPlayer(Player *p);
void showPlayerStats(Player *p);
void insertInTable(Player *p, Hand *table, int index);
void pickInDeck(Player *p, Hand *deck);

#endif
