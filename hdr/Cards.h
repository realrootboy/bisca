#ifndef _H_CARDS
#define _H_CARDS

// CONVENCAO UTILIZADA

/* 
    -- NAIPES -- 
    suit 0 = Diamonds
    suit 1 = Spades
    suit 2 = Hearts
    suit 3 = Clubs
*/

/*
    -- NUMEROS --
    number 8 = Jack
    number 9 = Lady
    number 10 = King
*/

// ESTRUTURA DE DADOS DE UMA CARTA
typedef struct dataCard {
    int suit;
    int number;
} DataCard;

// LISTA DE CARTAS
typedef struct cards {
    DataCard data;
    struct cards* next;
} Cards;

// ESTRUTURA QUE GUARDA UMA LISTA E O TAMANHO DELA
typedef struct hand{
    int size;
    Cards *head;
} Hand;

// ESTRUTURA QUE GUARDA UMA LISTA DE CARTAS E SEUS
// RESPECTIVOS INDICES
typedef struct tablePlay {
    struct hand *h;
    int *id;
} TablePlay;

// CRIA UMA MAO DE BARALHO
Hand* createHand();
// LIBERA UMA MAO DE BARALHO DA MEMORIA
void destroyHand( Hand *h );
// ADICIONA UMA CARTA A MAO DE BARALHO
void push( Hand *h, DataCard card );
// REMOVE UMA CARTA DA MAO DO BARALHO
void pop( Hand *h );
// IMPRIME UMA LISTA
void printList( Hand *h );
// RETORNA SE A LISTA E VAZIA
int isEmpty( Hand *h );
// RETORNA A CARTA NA POSICAO INDEX
Cards* atPos( Hand *h, int index );
// RETORNA O INDICE DE UMA CARTA NO BARALHO
int indexOf( Hand *h, Cards *c );
// APAGA UMA CARTA DA POSICAO INDEX
void erase( Hand *h, int index );
// REMOVE E RETORNA UMA CARTA DA POSICAO INDEX
Cards* erasePick( Hand *h, int index);
// INSERE UMA CARTA NA POSICAO INDEX
void insert( Hand *h, DataCard card, int index );
// INSERE UMA CARTA(JA EXISTENTE) NA MAO DE BARALHO
void insertNode( Hand *h, Cards *node );
// TROCA OS DADOS DE DUAS CARTAS PRESENTES NO BARALHO
void xchgCards( Hand *h, Cards *cA, Cards *cB );
// PREENCHE O BARALHO COM TODAS AS CARTAS DA BISCA
void fillAllCards( Hand *h );
// EMBARALHA AS CARTAS
void shuffleCards( Hand *h );
// CORTA O BARALHO E RETORNA O TRUNFO
DataCard cutDeck( Hand *h );
// RETORNA CARTAS COM SEUS INDICES QUE POSSUEM NAIPE IGUAL AO NAIPE DE "C"
TablePlay *sameSuit(Hand *h, DataCard c);
// CONTA OS PONTOS DO BARALHO E LIBERA ELES DA MEMORIA
int givePoints(Hand *h);

#endif
