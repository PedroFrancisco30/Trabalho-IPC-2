#ifndef PROCESSO_H
#define PROCESSO_H

typedef struct nome_chamada{
    char nome[80];
    struct nome_chamada *prox;
}nomeChamada;

typedef struct processo{
    int PID;
    char nome[50];
    int prioridade;
    char estado;
    struct processo* prox;
    nomeChamada *topo_pilha;
}processo;

typedef struct {
    processo *inicio;//ponteiro que aponta para o inicio da lista
}Lista;

typedef struct{
    processo *inicio;
}ListaFinalizado;

typedef struct {
    processo *inicio; // Ponteiro para o início da fila (head)
    processo *fim;    // Ponteiro para o fim da fila (tail)
}Fila;

nomeChamada *copiar_pilha(nomeChamada *topo);

void criar_lista(Lista *lista);
void inserir_processo_ordenado(Lista *lista, processo proc);

void criar_listaF(ListaFinalizado *lista);
void adicionar_finalizado(ListaFinalizado *lista, processo *proc_finalizado);

void criar_fila(Fila *fila);
void processos_fila(Fila *fila, processo proc);
processo* remove_processo_fila(Fila *fila);
void cancelar_processo(Fila *fila, int PID);

void imprimir_fila(Fila fila);
void imprimir_lista(ListaFinalizado lista);

void transferir_processos_para_fila(Lista *lista_origem, Fila *fila_destino);

nomeChamada *empilhar_funcao_pilha(nomeChamada *topo_atual, char nome_funcao[]);

nomeChamada* inverter_pilha(nomeChamada *pilha_original);

int verificar_PID(Fila *fila, int PID);

void liberando_listas_fila(Fila *fila,Lista *lista,ListaFinalizado *listaF);

void liberar_pilha(nomeChamada *topo);



#endif