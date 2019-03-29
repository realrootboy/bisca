#include <stdio.h>
#include <stdlib.h>

#include "hdr/Cards.h"

int main( void ){
    Hand* h = createHand();

    DataCard carta;

    carta.suit = 1;
    carta.number = 7;

    push( h, carta );

    carta.suit = 2;

    push( h, carta );

    carta.suit = 3;

    push( h, carta );

    pop( h );
    
    printList( h );    

    destroyHand( h );

    return 0;
}
