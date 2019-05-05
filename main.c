#include <stdio.h>
#include <stdlib.h>

#include "hdr/Cards.h"
#include "hdr/Player.h"
#include <locale.h>

int main( int argc, char *argv[] ){

    setlocale(LC_ALL, "Portuguese_Brasil");

    if( argc <= 3 ){
        printf("Instruções para a execução do programa:\n\n");
        printf("Modo: \n(1) 2 Jogadores\n(2) 4 Jogadores\n\n");
        printf("Dificuldade: \n(1) Facil\n(2) Intermediário\n\n");
        printf("Executar: ./main <Seu Nome> <Modo> <Dificuldade>\n");
        printf("Exemplo: ./main Renan 1 2\n");
        return 0;
    }

    int modo = atoi(argv[2]);
    int dificuldade = atoi(argv[3]);

    if( (modo < 1 || modo > 2)||(dificuldade < 1 || dificuldade > 2) ){
        printf("Parametros incorretos... Execução encerrada.\n");
        return 0;
    }

    PlayersInGame *pig = createPlayersInGame();
    
    Player* p1 = createPlayer(argv[1]);
    Player* p2 = createPlayer("Atilio");
    
    insertPlayerInGame(pig, p1);
    insertPlayerInGame(pig, p2);

    if( modo == 2 ){
        Player* p3 = createPlayer("Boladao");
        Player* p4 = createPlayer("Pittol");
        insertPlayerInGame(pig, p3);
        insertPlayerInGame(pig, p4);
    }

    Hand* table = createHand();

    fillAllCards(table);
    shuffleCards(table);


    destroyPlayersInGame(pig);
    destroyHand(table);

    return 0;
}
