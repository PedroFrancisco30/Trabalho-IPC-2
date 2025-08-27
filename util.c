#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "util.h"

void limpar_buffer_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limparTerminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void esperar(int seg) {
    #ifdef _WIN32
        Sleep(seg *1000);
    #else
        sleep(seg);
    #endif
}

void menu(){ 
    printf("\n|--------------Menu-----------------|\n");
    printf("|                                   |\n");
    printf("| |1| Criar Processo                |\n");
    printf("| |2| Executar Processo             |\n");
    printf("| |3| Imprimir Processos Prontos    |\n");
    printf("| |4| Imprimir Lista de Finalizados |\n");
    printf("| |5| Cancelar Processo             |\n");
    printf("| |0| Finalizar Programa            |\n");
    printf("|                                   |\n");
    printf("|-----------------------------------|\n\n");
}
