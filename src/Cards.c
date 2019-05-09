#include "../hdr/Cards.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// CRIA UMA MAO DE BARALHO
Hand* createHand(){
    Hand *h = (Hand*) malloc( sizeof( Hand ) );
    
    if( h == NULL ) {
        printf("Error on alloc.\n");    
        return NULL;
    }

    h->size = 0;
    h->head = NULL;

    return h;
}

// LIBERA UMA MAO DE BARALHO DA MEMORIA
void destroyHand( Hand *h ){
    if( h == NULL ) return;
    if( h->size == 0 ){
        free(h);
        return;
    }

    Cards *current = h->head;
    
    h->head = current->next;
    h->size--;

    free(current);

    destroyHand( h );
}

// ADICIONA UMA CARTA A MAO DE BARALHO
void push( Hand *h, DataCard card ){
    Cards *c = (Cards*) malloc( sizeof( Cards ) );
    
    if( c == NULL ){
        printf("Error in alloc the card to push");
        return;
    }
    
    c->data = card;
 
    if( h->head == NULL ){
        h->size++;
        h->head = c;
        (h->head)->next = NULL;
    } else {
        c->next = h->head;
        h->head = c;
        h->size++;
    }
}

// REMOVE UMA CARTA DA MAO DO BARALHO
void pop( Hand *h ){
    if( h == NULL ) return;
    if( h->head == NULL ){
        printf("Empty list.\n");
        return;
    }

    Cards *current = atPos(h, h->size - 1);
    Cards *previous;

    h->size--;
    
    if( current == h->head ){
        free(current);
        h->head = NULL;
        return;
    }

    previous = atPos(h, h->size - 1);
    previous->next = NULL;

    free(current);
}

// IMPRIME UMA LISTA
void printList( Hand *h ){
    char suitString[4][7] = {"\u2662", "\u2660", "\u2661", "\u2663"};

    if( h == NULL ){
        printf("Empty list.\n");
        return;
    }

    if( h->head == NULL ){
        printf("Empty list.\n");
        return;
    }
    int i = 1;
    Cards *current = h->head;
    
    while( current != NULL ){
        printf("%d - [Suit: %s, Number: %d]\n",
                i, suitString[current->data.suit], current->data.number);
        current = current->next;
        i++;
    }
    
    printf("\n");
}

// RETORNA SE A LISTA E VAZIA
int isEmpty( Hand *h ){ return h->size == 0; }

// RETORNA A CARTA NA POSICAO INDEX
Cards* atPos( Hand *h, int index ){
    if( h == NULL ) return NULL;
    if( index >= h->size || index < 0 ){
        printf("Index out of list.\n");
        return NULL;
    }
    
    int i = 0;
    
    Cards *current = h->head;

    for( i = 0 ; i < index ; i++ ) current = current->next;

    return current;
}

// RETORNA O INDICE DE UMA CARTA NO BARALHO
int indexOf( Hand *h, Cards *c ){
    if( h == NULL ) return -1;
    if( h->head == NULL ) return -1;

    int count = 0;
    
    Cards *current = h->head;

    while( current != NULL ){
        if( current == c ) return count;
        
        current = current->next;
        count++;
    }

    return -1;
}

// APAGA UMA CARTA DA POSICAO INDEX
void erase( Hand *h, int index ){
    if( h == NULL ) return;
    if( index >= h->size || index < 0 ){
        printf("Index out of list.");
        return;
    }

    Cards *current = atPos(h, index);
    Cards *previous;

    h->size--;

    if( current == h->head ){
        h->head = current->next;
        free(current);
        return;
    }

    previous = atPos(h, index - 1);
    previous->next = current->next;

    free(current);
}
// REMOVE E RETORNA UMA CARTA DA POSICAO INDEX
Cards* erasePick( Hand *h, int index){
    if( h == NULL ) return NULL;
    if( index >= h->size || index < 0 ){
        printf("Index out of list.");
        return NULL;
    }

    Cards *current = atPos(h, index);
    Cards *previous;

    h->size--;

    if( current == h->head ){
        h->head = current->next;
        return current;
    }

    previous = atPos(h, index - 1);
    previous->next = current->next;

    return current;
}

// INSERE UMA CARTA NA POSICAO INDEX
void insert( Hand *h, DataCard card, int index ){
    if( h == NULL ) return;
    if( index > h->size || index < 0 ) return;

    Cards* cardn = (Cards*) malloc( sizeof(Cards) );
    cardn->data = card;

    h->size++;

    if( index == 0 ){
        cardn->next = h->head;
        h->head = cardn;
        return;
    }
    
    Cards* previous = atPos(h, index - 1);
    
    cardn->next = previous->next;
    
    previous->next = cardn;
}

// INSERE UMA CARTA(JA EXISTENTE) NA MAO DE BARALHO
void insertNode( Hand *h, Cards *node ){
    if( h == NULL ) return;
    if( node == NULL ) return;

    h->size++;

    if( h->head == NULL ){
        h->head = node;
        return;
    }

    Cards* aux = h->head;

    while( aux->next != NULL ){
        aux = aux->next;
    }

    aux->next = node;
}

// TROCA OS DADOS DE DUAS CARTAS PRESENTES NO BARALHO
void xchgCards( Hand *h, Cards *cA, Cards *cB ){
    if( h == NULL ) return;
    if( cA == NULL || cB == NULL ) return;
    if( cA == cB ) return;
    
    int iA = indexOf(h, cA);
    int iB = indexOf(h, cB);

    if( iA == -1 || iB == -1 ) return; 

    DataCard dAux = cA->data;
    cA->data = cB->data;
    cB->data = dAux;
}

// PREENCHE O BARALHO COM TODAS AS CARTAS DA BISCA
void fillAllCards( Hand *h ){
    if( h == NULL ) return;
    
    int i = 0;
    int j = 0;

    DataCard carta;

    for( i = 0 ; i < 4 ; i++ )
        for( j = 1 ; j < 11 ; j++ ){
            carta.suit = i;
            carta.number = j;
            push( h, carta );
        }
}

// EMBARALHA AS CARTAS
void shuffleCards( Hand *h ){
    if( h == NULL ) return;

    int i = 0;
    int j = 0;

    srand(time(NULL));

    int val_max = h->size;

    for( i = 0 ; i < h->size ; i++ )
        for( j = 0 ; j < h->size ; j++ ){
            xchgCards(h, atPos(h, rand() % val_max), 
                atPos(h, rand() % val_max));
        }

}

// CORTA O BARALHO E RETORNA O TRUNFO
DataCard cutDeck( Hand *h ){
    Cards* trump = atPos(h, h->size/2);
    Cards* trumpR = (Cards*) malloc( sizeof(Cards) );

    trumpR->data = trump->data;
    trumpR->next = NULL;
    
    erase(h, h->size/2);

    insertNode(h, trumpR);

    return trumpR->data;
}

// RETORNA CARTAS COM SEUS INDICES QUE POSSUEM NAIPE IGUAL AO NAIPE DE "C"
TablePlay* sameSuit(Hand *h, DataCard c){
    if( h == NULL ) return NULL;
    
    int i = 0;
    int j = 0;

    TablePlay *sameCards = (TablePlay*) malloc(sizeof(TablePlay));
    
    sameCards->h = createHand();
    sameCards->id = (int*) malloc(sizeof(int) * h->size);

    Cards *aux = h->head;

    for( i = 0 ; i < h->size ; i++ ){
        if( aux->data.suit == c.suit ){
            insert(sameCards->h, aux->data, sameCards->h->size);
            sameCards->id[j] = i;
            j++;
        }
        aux = aux->next;
    }

    sameCards->id = (int*) realloc(sameCards->id, sizeof(int) * j);

    return sameCards;
}

// CONTA OS PONTOS DO BARALHO E LIBERA ELES DA MEMORIA
int givePoints(Hand *h){
    int points = 0;

    Cards *aux = h->head;

    while(aux != NULL){
        switch(aux->data.number){
            case 1:
                points += 11;
            break;
            case 7:
                points += 10;
            break;
            case 10:
                points += 4;
            break;
            case 9:
                points += 3;
            break;
            case 8:
                points += 2;
            break;
            default:
                break;
        }
        
        erase(h, 0);

        aux = h->head;
        
    }

    return points;
}