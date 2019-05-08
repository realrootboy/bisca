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
    int have8 = 0;
    int have9 = 0;
    int have10 = 0;
    int nonHighTrump = 0;
    int i_have_trump = 0;
    int my_trump_number = -1;
    int trumpIndex = -1;
    int highCardValue = 0;
    int highCardIndex = -1;
    int significantHigh = 1;
    int insignificantCardMinValue = 7;
    int insignificantCardIndex = 0;
    int i = 0;

    Cards *aux = NULL;
    

    if(diff == 1){
        insertInTable(p, table, rand() % p->h->size);
        printList(table);
    } else {
        aux = p->h->head;
        while( aux != NULL ){
            if(aux->data.suit == trumpInfo.suit){
                i_have_trump = 1;
                my_trump_number = aux->data.number;
                trumpIndex = i;
            }
            if(aux->data.number > 8 || aux->data.number > highCardValue){
                if(table->size){
                    if(table->head->data.suit == aux->data.suit){
                        highCardValue = aux->data.number;
                        highCardIndex = i;
                    }
                }
            }
            if(aux->data.number < insignificantCardMinValue && aux->data.number > 1){
                insignificantCardMinValue = aux->data.number;
                insignificantCardIndex = i;
            }
            i++;
            aux = aux->next;
        }

        aux = table->head;
        while( aux != NULL ){
            if(aux->data.number == 1) have1 = 1;
            if(aux->data.number == 7) have7 = 1;
            if(aux->data.number == 8) have8 = 1;
            if(aux->data.number == 9) have9 = 1;
            if(aux->data.number == 10) have10 = 1;
            if(aux->data.suit == trumpInfo.suit){
                if( my_trump_number > aux->data.number ) nonHighTrump = 1;
            }
            if(aux->data.number > highCardValue) significantHigh = 0;
            aux = aux->next;
        }

        if( i_have_trump ){
            if(nonHighTrump){
                if(have1 || have7) {
                    insertInTable(p, table, trumpIndex);
                    printList(table);
                    return;
                }
            }
        }

        if( have1 || have7 || have8 || have9 || have10 ){
            if(highCardValue && significantHigh) {
                insertInTable(p, table, highCardIndex);
                printList(table);
                return;
            }
        }

        if( insignificantCardIndex ){
            insertInTable(p, table, insignificantCardIndex);
            printList(table);
            return;
        }

        insertInTable(p, table, rand() % p->h->size);
        printList(table);

    }
}

void runGame(PlayersInGame *pig, int mode, int diff){
    
    int team_1_points = 0;
    int team_2_points = 0;

    char suitString[4][7] = {"\u2662", "\u2660", "\u2661", "\u2663"};

    char buffer[64];

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
                scanf("%s", buffer);
                cardToPlay = atoi(buffer);

                while( cardToPlay < 1 || cardToPlay > current->p->h->size){
                    printf("Please select a valid index:\n");
                    scanf("%s", buffer);
                    cardToPlay = atoi(buffer);
                }
            
                insertInTable(current->p, table, cardToPlay - 1);

                printf("%s plays...\n", current->p->name);
                printList(table);
            } else botPlay(current->p, diff, table, trumpInfo);
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
