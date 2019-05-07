#ifndef _H_CARDS
#define _H_CARDS

// suit 0 = Diamonds
// suit 1 = Spades
// suit 2 = Hearts
// suit 3 = Clubs

// number 8 = Jack
// number 9 = Lady
// number 10 = King

typedef struct dataCard {
    int suit;
    int number;
} DataCard;

typedef struct cards {
    DataCard data;
    struct cards* next;
} Cards;

typedef struct hand{
    int size;
    Cards *head;
} Hand;

typedef struct tablePlay {
    struct hand *h;
    int *id;
} TablePlay;

// Creates the Hand
Hand* createHand();
// Destroys the Hand
void destroyHand( Hand *h );
// Push a Card by Hand
void push( Hand *h, DataCard card );
// Pop a Card by Hand
void pop( Hand *h );
// Prints the Hand
void printList( Hand *h );
// Check if the Hand is Empty
int isEmpty( Hand *h );
// Gives the Card in the 'index' Position 
Cards* atPos( Hand *h, int index );
// Gives a Index of Card Named by 'c'
int indexOf( Hand *h, Cards *c );
// Erases the Card in the 'index' Position
void erase( Hand *h, int index );
// Erases the Card in the 'index' Position and Return;
Cards* erasePick( Hand *h, int index);
// Inserts the Card in the 'index' Position
void insert( Hand *h, DataCard card, int index );
// Inserts a Existent Node at last position
void insertNode( Hand *h, Cards *node );
// Exchange the Card named by 'cA' with Card by 'cB'
void xchgCards( Hand *h, Cards *cA, Cards *cB );
// Fill all cards
void fillAllCards( Hand *h );
// Shuffle cards
void shuffleCards( Hand *h );
// "Cutts" the deck
DataCard cutDeck( Hand *h );
// Check if have a same suit and return them
TablePlay *sameSuit(Hand *h, DataCard c);
// Give points and free cards
int givePoints(Hand *h);

#endif
