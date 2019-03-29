#include "../hdr/Cards.h"
#include <stdlib.h>
#include <stdio.h>

// Creates the Hand
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

// Destroys the Hand
void destroyHand( Hand* h ){
    
    if( h == NULL ) return;

    if( h->size == 0 ){
        
        free(h);
        return;

    }

    Cards* current = h->head;
    
    h->head = current->next;
    h->size--;

    free(current);

    destroyHand( h );

}

// Push a Card by Hand
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

// Pop a Card by Hand
void pop( Hand *h ){

    if( h == NULL ) return;

    if( h->head == NULL ){
    
        printf("Empty list.\n");
        return;

    }

    Cards* current = h->head;

    h->head = current->next;
    h->size--;
    
    free(current);

}

// Prints the Hand
void printList( Hand *h ){

    if( h == NULL || h->head == NULL ){
        
        printf("Empty list.\n");
        return;

    }

    Cards* current = h->head;

    while( current != NULL ){
        
        printf("[Suit: %d, Number: %d]\n",
                current->data.suit, current->data.number);

        current = current->next;

    }

    printf("\n");

}

// Check if the Hand is Empty
int isEmpty( Hand *h ){ return h->size == 0; }

// Gives the Card in the 'index' Position 
Cards* atPos( Hand *h, int index ){

}

// Gives a Index of Card Named by 'c'
int indexOf( Hand *h, Cards *c ){

}

// Erases the Card in the 'index' Position
void erase( Hand *h, int index ){

}

// Inserts the Card in the 'index' Position
void insert( Hand *h, DataCard card, int index ){

}

// Exchange the Card named by 'cA' with Card by 'cB'
void xchgCards( Hand *h, Cards* cA, Cards* cB ){

}

