#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include "hdr/Cards.h"
#include "hdr/Player.h"
#include "hdr/Game.h"


int main( int argc, char *argv[] ){
    // PARA IMPRIMIR CARACTERES UTF-8
    setlocale(LC_ALL, "Portuguese_Brasil");

    // CONTROLE DE ENTRADA DE ARGUMENTOS VALIDOS PARA A EXECUCAO DO PROGRAMA
    if( argc <= 3 ){
        printf("Instruções para a execução do programa:\n\n");
        printf("Modo: \n(1) 2 Jogadores\n(2) 4 Jogadores\n\n");
        printf("Dificuldade: \n(1) Facil\n(2) Intermediário\n\n");
        printf("Executar: ./main <Seu Nome> <Modo> <Dificuldade>\n");
        printf("Exemplo: ./main Renan 1 2\n");
        return 0;
    }
    
    // INICIA AS CONFIGURACOES INICIAIS
    setupGame(argv);

    return 0;
}
