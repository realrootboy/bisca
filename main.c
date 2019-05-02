#include <stdio.h>
#include <stdlib.h>

#include "hdr/Cards.h"

int main( void ){
    Hand* h = createHand();

    DataCard carta;

    Cards *c1, *c2;

    carta.suit = 1;
    carta.number = 7;

    push( h, carta );

    carta.suit = 2;

    push( h, carta );

    carta.suit = 3;

    push( h, carta );

    c1 = atPos(h, 0);
    c2 = atPos(h, 2);

    printList( h );

    xchgCards(h, c1, c2);

    printList( h );

    destroyHand( h );

    return 0;
}
