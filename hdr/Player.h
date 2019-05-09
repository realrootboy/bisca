#ifndef PLAYER_H
#define PLAYER_H

#include "Cards.h"

// ESTRUTURA DE DADOS DE UM JOGADOR
typedef struct player{
    int points;
    Hand *h;
    char *name;
} Player;

// LISTA CIRCULAR DE JOGADORES
typedef struct playersInGame{
    Player *p;
    struct playersInGame *next;
} PlayersInGame;

// CRIA UMA LISTA DE JOGADORES IN GAME
PlayersInGame* createPlayersInGame();
// LIBERA UMA LISTA DE JOGADORES IN GAME DA MEMORIA
void destroyPlayersInGame(PlayersInGame *pig);
// INSERE UM JOGADOR NA LISTA DE JOGADORES IN GAME
void insertPlayerInGame(PlayersInGame *pig, Player *p);
// CRIA UM JOGADOR
Player* createPlayer(char *name);
// LIBERA UM JOGADOR DA MEMORIA
void destroyPlayer(Player *p);
// MOSTRA STATUS DE UM JOGADOR
void showPlayerStats(Player *p);
// INSERE UMA CARTA NA POSICAO INDEX DA MAO DO JOGADOR
// NA MAO DE TRABALHO CHAMADA TABLE
void insertInTable(Player *p, Hand *table, int index);
// PEGA A PRIMEIRA CARTA DE UM DECK E INSERE NA MAO DO JOGADOR
void pickInDeck(Player *p, Hand *deck);

#endif
