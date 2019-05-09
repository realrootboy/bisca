#include "../hdr/Player.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// CRIA UMA LISTA DE JOGADORES IN GAME
PlayersInGame* createPlayersInGame(){
    PlayersInGame *pig = (PlayersInGame*) malloc( sizeof(PlayersInGame) );
    
    pig->p = NULL;
    pig->next = NULL;
    
    return pig;
}

// LIBERA UMA LISTA DE JOGADORES IN GAME DA MEMORIA
void destroyPlayersInGame(PlayersInGame *pig){
    if(pig == NULL) return;
    if(pig->p == NULL) return;

    destroyPlayer(pig->p);
    pig->p = NULL;

    destroyPlayersInGame(pig->next);

    free(pig);
}

// INSERE UM JOGADOR NA LISTA DE JOGADORES IN GAME
void insertPlayerInGame(PlayersInGame *pig, Player *p){
    if(pig == NULL) return;

    if(pig->p == NULL){
        pig->p = p;
        pig->next = pig;
        return;
    }

    PlayersInGame *aux = pig;
    PlayersInGame *newNode = createPlayersInGame();
    newNode->p = p;

    while(aux->next != pig) aux = aux->next;

    aux->next = newNode;
    newNode->next = pig;
}

// CRIA UM JOGADOR
Player* createPlayer(char *name){
    Player* p = (Player*) malloc( sizeof(Player) );
    
    p->points = 0;
    p->h = createHand();
    
    p->name = (char*) malloc( sizeof(char) * (strlen(name) + 1));
    strcpy(p->name, name);
    
    return p;
}

// LIBERA UM JOGADOR DA MEMORIA
void destroyPlayer(Player *p){
    if( p == NULL ) return;

    free(p->name);
    
    destroyHand(p->h);
    
    free(p);
}

// MOSTRA STATUS DE UM JOGADOR
void showPlayerStats(Player *p){
    if( p == NULL ) return;

    printf("Name............: %s\n", p->name);
    printf("Points..........: %d\n", p->points);
    printf("Number of Cards.: %d\n\n", p->h->size);
    if(p->h->size){
        printf("Cards in hand\n\n");
        printList(p->h);
    }
    printf("\n");
}

// INSERE UMA CARTA NA POSICAO INDEX DA MAO DO JOGADOR
// NA MAO DE TRABALHO CHAMADA TABLE
void insertInTable(Player *p, Hand *table, int index){
    if( p == NULL ) return;
    if( table == NULL ) return;

    Cards* c = erasePick(p->h, index);
    c->next = NULL;

    insertNode( table, c ); 
}

// PEGA A PRIMEIRA CARTA DE UM DECK E INSERE NA MAO DO JOGADOR
void pickInDeck(Player *p, Hand *deck){
    if( p == NULL ) return;
    if( deck == NULL ) return;
    if( deck->size == 0 ) return;

    Cards* c = erasePick(deck, 0);
    c->next = NULL;

    insertNode( p->h, c );
}
