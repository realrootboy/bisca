#ifndef GAME_H
#define GAME_H

#include "Cards.h"
#include "Player.h"

// VETOR DE DIMENSAO 2
typedef struct vector2d{
    int x;
    int y;
} Vector2d;

// RETORNA QUANTAS POSICOES A LISTA CIRCULAR DEVE RODAR
// PARA RETORNAR AO GANHADOR
int whoWin(Hand* table, DataCard trumpInfo, int mode);
// FAZ A JOGADA DE JOGARES NAO-HUMANOS
void botPlay(Player *p, int diff, Hand *table, DataCard trumpInfo);
// EXECUTA A LOGICA DA BISCA
void runGame(PlayersInGame *pig, int mode, int diff);
// CONFIGURACOES FINAIS DE MODO DE JOGO E VALIDACOES ANTES DE INICIAR
// A JOGATINA
void setupGame(char *argv[]);


#endif
