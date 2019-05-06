#include <stdio.h>
#include <stdlib.h>

#include "hdr/Cards.h"
#include "hdr/Player.h"
#include <locale.h>

void botPlay(Player *p, int diff, Hand *table);
void setupGame(char *argv[]);
void runGame(PlayersInGame *pig, int mode, int diff);

void botPlay(Player *p, int diff, Hand *table){
    printf("%s plays...\n", p->name);
    insertInTable(p, table, 0);
    printList(table);
}

void runGame(PlayersInGame *pig, int mode, int diff){
    Hand *table = createHand();
    Hand *deck = createHand();
    
    fillAllCards(deck);
    shuffleCards(deck);
    
    int playerNumber = mode == 1 ? 2 : 4;
    int i = 0;
    int cardToPlay = 0;

    DataCard trumpInfo = cutDeck(deck);

    PlayersInGame *current = pig;
    Player *you = pig->p;

    Player *firstPlayer;

    for( i = 0 ; i < playerNumber * 3 ; i++ ){
        pickInDeck(current->p, deck);
        current = current->next;
    }

    while(deck->size != 0){
        system("clear");
        printf("Trump Card\n");
        printf("Suit: %d\n", trumpInfo.suit);
        printf("Number: %d\n\n", trumpInfo.number);


        for( i = 0 ; i < playerNumber ; i++ ){
            if( current->p == you){
                printf("Select a card to play:\n\n");
                showPlayerStats(current->p);
                scanf("%d", &cardToPlay);
                
                while( cardToPlay < 1 || cardToPlay > current->p->h->size){
                    printf("Please select a valid index:\n");
                    scanf("%d", &cardToPlay);
                }
            
                insertInTable(current->p, table, cardToPlay - 1);

                printf("%s plays...\n", current->p->name);
                printList(table);
            } else botPlay(current->p, diff, table);
            system("sleep 1");
     
            current = current->next;
        }

        firstPlayer = current->p;

        printf("Verificando quem ganhou a rodada...\n");
        system("sleep 5");

        for( i = 0 ; i < playerNumber ; i++ ){
            pickInDeck(current->p, deck);
            current = current->next;
        }

        current = current->next;
    }

    destroyHand(deck);
    destroyHand(table);
}

void setupGame(char *argv[]){

    int mode = atoi(argv[2]);
    int diff = atoi(argv[3]);

    if( (mode < 1 || mode > 2)||(diff < 1 || diff > 2) ){
        printf("Parametros incorretos... Execução encerrada.\n");
        return;
    }

    PlayersInGame *pig = createPlayersInGame();

    Player *p1 = createPlayer(argv[1]);
    Player *p2 = createPlayer("Atilio");

    insertPlayerInGame(pig, p1);
    insertPlayerInGame(pig, p2);

    if( mode == 2 ){
        Player *p3 = createPlayer("Boladao");
        Player *p4 = createPlayer("Pittol");
        insertPlayerInGame(pig, p3);
        insertPlayerInGame(pig, p4);
    }

    runGame(pig, mode, diff);

    destroyPlayersInGame(pig);
    
}

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
    

    setupGame(argv);

    return 0;
}
