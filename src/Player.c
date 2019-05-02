#include "../hdr/Player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Player* createPlayer(char *name){
    Player* p = (Player*) malloc( sizeof( Player ) );
    
    p->points = 0;
    p->h = createHand();
    
    p->name = (char*) malloc( sizeof(char) * (strlen(name) + 1));
    strcpy(p->name, name);
    
    return p;
}

void destroyPlayer(Player* p){
    if( p == NULL ) return;

    free(p->name);
    
    destroyHand(p->h);
    
    free(p);
}

void showPlayerStats(Player *p){
    if( p = NULL ) return;

    printf("Name............: %s\n", p->name);
    printf("Points..........: %d\n", p->points);
    printf("Number of Cards.: %d\n", p->h->size);
    printList(p->h);
}

void insertInTable(Player *p, Hand *table, int index){
    if( p == NULL ) return;
    if( table == NULL ) return;

    Cards* c = erasePick(p->h, index);
    c->next = NULL;

    insertNode( table, c ); 
}

void pickInDeck(Player *p, Hand *deck){
    if( p == NULL ) return;
    if( deck == NULL ) return;

    Cards* c = erasePick(deck, deck->size - 1);
    c->next = NULL;

    insertNode( p->h );
}
