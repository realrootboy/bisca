#include "../hdr/Game.h"

#include <stdlib.h>
#include <stdio.h>

int whoWin(Hand* table, DataCard trumpInfo, int mode){
    int y = -1;
    int i = 0;
    Cards *max;
    Cards *aux;

    TablePlay *sameTrump = sameSuit(table, trumpInfo);

    if(sameTrump->h->size){
        aux = sameTrump->h->head;
        y = sameTrump->id[i];
        max = aux;
        while( aux != NULL ){
            if( aux->data.number > max->data.number ){
                max = aux;
                y = sameTrump->id[i];
            }
            aux = aux->next;
            i++;

        }

        destroyHand(sameTrump->h);
        free(sameTrump->id);
        free(sameTrump);

        return y;
    }

    destroyHand(sameTrump->h);
    free(sameTrump->id);
    free(sameTrump);

    Vector2d v;
    v.x = 0;
    v.y = 0;

    max = table->head;
    aux = max;

    while( aux != NULL ){
        if( max->data.suit == aux->data.suit )
            if( aux->data.number > max->data.number ){
                v.y = v.x;
                max = aux;
            }
       v.x++;
       aux = aux->next;
    }

    
    return v.y;
}

void botPlay(Player *p, int diff, Hand *table, DataCard trumpInfo){
    printf("%s plays...\n", p->name);

    int have1 = 0;
    int have7 = 0;
    int nonHighTrump = 0;
    int i_have_trump = 0;
    int i_have_high_1 = 0;

    if(diff == 1){
        insertInTable(p, table, rand() % p->h->size);
        printList(table);
    } else {

    }
}

void runGame(PlayersInGame *pig, int mode, int diff){
    
    int team_1_points = 0;
    int team_2_points = 0;

    char suitString[4][7] = {"\u2662", "\u2660", "\u2661", "\u2663"};

    Hand *table = createHand();
    Hand *deck = createHand();
    
    fillAllCards(deck);
    shuffleCards(deck);
    
    int playerNumber = mode == 1 ? 2 : 4;
    int i = 0;
    int cardToPlay = 0;
    int dataWin = 0;

    DataCard trumpInfo = cutDeck(deck);

    PlayersInGame *current = pig;
    Player *you = pig->p;

    for( i = 0 ; i < playerNumber * 3 ; i++ ){
        pickInDeck(current->p, deck);
        current = current->next;
    }

    while(pig->p->h->size){
        printf("Trump Card\n");
        printf("Suit: %s\n", suitString[trumpInfo.suit]);
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

        for( i = 0 ; i < playerNumber ; i++ ){
            pickInDeck(current->p, deck);
            current = current->next;
        }
    	

        dataWin = whoWin(table, trumpInfo, mode);

        for( i = 0 ; i < dataWin ; i++)
            current = current->next;

        

        printf("Winner %s with %d\n\n", current->p->name, dataWin + 1);

        current->p->points += givePoints(table);

    }

    system("clear");

    printf("Calculating points...\n\n");

    current = pig;

    for( i = 0 ; i < mode ; i++ ){
        team_1_points += current->p->points;
        showPlayerStats(current->p);
        current = current->next;
        team_2_points +=  current->p->points;
        showPlayerStats(current->p);
        current = current->next;
    }
        

    printf("Team 1: %d\n", team_1_points);
    printf("Team 2: %d\n", team_2_points);
    printf("\nWinner: ");
    if( team_1_points > team_2_points ) printf("Team 1 !!!\n");
    else if( team_2_points > team_1_points ) printf("Team 2 !!!\n");
    else printf("DRAW!!!\n");

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
    Player *p2 = createPlayer("Atilio \u267F");

    insertPlayerInGame(pig, p1);
    insertPlayerInGame(pig, p2);

    if( mode == 2 ){
        Player *p3 = createPlayer("Chuveirinho \u262D");
        Player *p4 = createPlayer("Pittol \u265A");
        insertPlayerInGame(pig, p3);
        insertPlayerInGame(pig, p4);
    }

    runGame(pig, mode, diff);

    destroyPlayersInGame(pig);
    
}
