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

// Prints the Hand
void printList( Hand *h ){
    if( h == NULL ){
        printf("Empty list.\n");
        return;
    }

    if( h->head == NULL ){
        printf("Empty list.\n");
        return;
    }

    Cards *current = h->head;

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
    if( h == NULL ) return NULL;
    if( index >= h->size || index < 0 ){
        printf("Index out of list.\n");
        return NULL;
    }
    
    int i = 0;
    
    Cards *current = h->head;

    for( i = 0 ; i < index ; i++ ) current = current->next;

    printf("Card in %d => [Suit: %d, Number: %d]\n",
                index, current->data.suit, current->data.number);

    return current;
}

// Gives a Index of Card Named by 'c'
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

// Erases the Card in the 'index' Position
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

// Inserts the Card in the 'index' Position
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

// Exchange the Card named by 'cA' with Card by 'cB'
void xchgCards( Hand *h, Cards *cA, Cards *cB ){
    if( h == NULL ) return;
    if( cA == NULL || cB == NULL ) return;
    if( cA == cB ) return;

    int iA = indexOf(h, cA);
    int iB = indexOf(h, cB);

    if( iA == -1 || iB == -1 ) return;
}

