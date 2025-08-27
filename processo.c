#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processo.h"

void criar_lista(Lista *lista){//criando a lista
    lista->inicio = NULL;
}

void inserir_processo_ordenado(Lista *lista,processo proc){//proc armazena todos os dados do vetor pegos no main
    processo *novo = malloc(sizeof(processo));
    processo *aux;

    if(novo){
        novo->PID = proc.PID;
        novo->estado = proc.estado;
        novo->prioridade = proc.prioridade;
        strcpy(novo->nome,proc.nome);
        novo->topo_pilha = copiar_pilha(proc.topo_pilha);

    if(lista->inicio == NULL){
        novo->prox = lista->inicio;
        lista->inicio = novo;
    }else if(novo->prioridade < lista->inicio->prioridade){
        novo->prox = lista->inicio;
        lista->inicio = novo;
    }else{//pode ser que a lista nao esteja vazia e o elemento que desejamos inserir talvez nao seja menor que o primeiro elemento da lista
        aux = lista->inicio;
        while(aux->prox != NULL && novo->prioridade > aux->prox->prioridade){//while para o ponteiro auxiliar andar pela lista e procurar a posicao certa de colocar nosso processo e garantindo que o proximo nao é nulo e olhando que esse novo valor que queremos inserir é maior que o valor do no que o auxiliar aponta
            aux = aux->prox;//continuar andando
        }
            novo->prox = aux->prox;
            aux->prox = novo;
        }
    }else{
    printf("Erro ao alocar memoria");
    return;
    }

}

void criar_listaF(ListaFinalizado *lista){// Inicializa a lista de finalizados apontando para NULL
    lista->inicio = NULL;
}

void adicionar_finalizado(ListaFinalizado *lista,processo *proc_finalizado){
    if(proc_finalizado == NULL){
        // Verifica se o processo é nulo antes de adicionar
        printf("A lista esta vazia");
        return;
    }
    // Insere o processo no início da lista de finalizados
    proc_finalizado->prox = lista->inicio; 
    lista->inicio = proc_finalizado;    
}

void criar_fila(Fila *fila){// Inicializa a fila apontando início e fim para NULL
    fila->inicio = NULL;
    fila->fim = NULL;
}

void processos_fila(Fila *fila, processo proc) {
    processo *novo = malloc(sizeof(processo)); // Aloca memória para o novo processo

    if (novo) { // Verifica se a alocação foi bem-sucedida
        novo->PID = proc.PID;
        novo->estado = proc.estado;
        novo->prioridade = proc.prioridade;
        strcpy(novo->nome,proc.nome);
        novo->topo_pilha = copiar_pilha(proc.topo_pilha);
        novo->prox = NULL;  // O novo nó sempre será o último, então seu 'prox' é NULL

        // Se a fila estiver vazia, o novo elemento é tanto o início quanto o fim
        if (fila->inicio == NULL) {
            fila->inicio = novo;
            fila->fim = novo;
        } else {
            // Se a fila não estiver vazia, o 'prox' do último elemento atual aponta para o novo
            fila->fim->prox = novo;
            // E o novo elemento se torna o novo 'fim' da fila
            fila->fim = novo;
        }
    } else {
        printf("Erro ao alocar memoria para o processo.\n");
    }
}

//processo que vai ser retirado depois porque vai ser jogado na lista
processo* remove_processo_fila(Fila *fila){ 
    if(fila->inicio == NULL){
        return NULL; // Fila de prioridade vazia
    }

    processo *processo_removido = fila->inicio; // O processo de maior prioridade é o primeiro
    fila->inicio = fila->inicio->prox;         // O segundo processo se torna o novo primeiro

    if(fila->inicio == NULL){ // Se a fila ficou vazia após a remoção
        fila->fim = NULL;
    }
    processo_removido->prox = NULL; // Importante para isolar o nó removido
    return processo_removido;
}

void imprimir_fila(Fila fila){ // Rimprime os processos que vao ser executados
    processo *no = fila.inicio;
    printf("\n--- Itens da Fila de Processos ---\n");
    printf("PID\tNome\t\tPrioridade\tEstado\n");
    printf("----------------------------------------------------------\n");
    while(no != NULL){
        printf("%d\t", no->PID);
        printf("%-15s\t", no->nome);
        printf("%d\t\t", no->prioridade);
        printf("%c\n", no->estado);
        no = no->prox;
    }
    printf("\n\n");
}

void cancelar_processo(Fila *fila, int PID){// Remove processo da fila com base no PID
    if (fila->inicio == NULL){
        printf("Fila vazia.\n");
        return;
    }

    processo *atual = fila->inicio;
    processo *anterior = NULL;

    // Percorre a fila buscando o processo com o PID informado
    while (atual != NULL){
        if (atual->PID == PID){
            if (anterior == NULL){
                // O processo a ser removido está no início da fila
                fila->inicio = atual->prox;
                if (fila->fim == atual){
                    fila->fim = NULL;
                }
            } else {
                // O processo está no meio ou fim da fila
                anterior->prox = atual->prox;
                if (fila->fim == atual){
                    fila->fim = anterior;
                }
            }
            nomeChamada *chamada_atual = atual->topo_pilha;//liberando a memoria da pilha do processo que escolhemos
            nomeChamada *proxima_chamada;
            while(chamada_atual != NULL){
                proxima_chamada = chamada_atual->prox;
                free(chamada_atual);
                chamada_atual = proxima_chamada;
            }
            free(atual);// Libera a memória do processo removido
            printf("Processo com PID: %d removido.\n", PID);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }

    printf("ID %d não encontrado na fila.\n", PID);
}

void imprimir_lista(ListaFinalizado lista){ 
    processo *no = lista.inicio;
    printf("\n--- Itens da Lista Finalizada ---\n");
    printf("PID\tNome\t\tPrioridade\tEstado\n");
    printf("----------------------------------------------------------\n");
    while(no != NULL){
        printf("%d\t", no->PID);
        printf("%-15s\t", no->nome);
        printf("%d\t\t", no->prioridade);
        printf("%c\n", no->estado);
        no = no->prox;
    }
    printf("\n\n");
}

void transferir_processos_para_fila(Lista *lista_origem, Fila *fila_destino) {
    // Transfere todos os processos da lista ordenada para a fila FIFO
    if (lista_origem->inicio == NULL) {
        printf("Nao ha processos na lista para transferir para a fila.\n");
        return;
    }
    processo *atual = lista_origem->inicio;

    while (atual != NULL) {
        processo temp = *atual; // Faz uma cópia dos dados do processo atual
        temp.prox = NULL; // Evita manter ponteiros antigos
        processos_fila(fila_destino, temp); // Insere na fila
        atual = atual->prox; // Avança para o próximo processo
    }

    //liberando memoria da lista usada
    atual = lista_origem->inicio;
    processo *prox;
    while (atual != NULL) {
        prox = atual->prox;
        liberar_pilha(atual->topo_pilha);
        free(atual);
        atual = prox;
    }
    lista_origem->inicio = NULL; // Após a transferência, esvazia a lista
}

nomeChamada *empilhar_funcao_pilha(nomeChamada *topo_atual,char nome_funcao[]){
     // Empilha uma nova função no topo da pilha de chamadas
    nomeChamada *novo = malloc(sizeof(nomeChamada));

    if(novo){
        strcpy(novo->nome,nome_funcao);//copiando o nome da função
        novo->prox = topo_atual;       // O topo agora aponta para o anterior
        return novo;
    }
    else{
    printf("Erro ao alocar memoria");
    return topo_atual;
    }
}

//funçao para desempilhar a pilha de funções

nomeChamada* inverter_pilha(nomeChamada *pilha_original){
    // Cria uma nova pilha inicialmente vazia (topo = NULL)
    nomeChamada *pilha_invertida = NULL;

     // Enquanto ainda houver elementos na pilha original
    while(pilha_original != NULL){
         // Salva o topo atual da pilha original
        nomeChamada *temp = pilha_original;

        // Avança o topo da pilha original para o próximo nó
        pilha_original = pilha_original->prox;

        // O ponteiro do nó atual (temp) agora aponta para o topo da nova pilha invertida
        temp->prox = pilha_invertida;

         // Atualiza o topo da pilha invertida para o novo nó (temp)
        pilha_invertida = temp;
    }

    // Retorna o novo topo da pilha, agora com os elementos na ordem invertida
    return pilha_invertida;
} 

int verificar_PID(Fila *fila, int PID){//funcao que anada pela fila e verifica se o PID ja existe
    processo *temp = fila->inicio;

    while(temp != NULL){
        if(temp->PID == PID){
            return 0;
        }
        temp = temp->prox;
    }
    return 1;
}

void liberar_pilha(nomeChamada *topo){//funcao que libera a memoria da pilha de cada processo
    nomeChamada *atual = topo;
    nomeChamada *prox;

    while(atual != NULL){
        prox = atual->prox;
        free(atual);
        atual = prox;
    }

}

void liberando_listas_fila(Fila *fila,Lista *lista,ListaFinalizado *listaF){//funcao que libera lista , fila e lista de finalizados e as pilhas em cada um

    // Liberação da memória alocada para os nós da fila
    processo *atual = fila->inicio;
    processo *proximo_temp;

    while (atual != NULL) {
            proximo_temp = atual->prox; // Salva o próximo nó antes de liberar o atual
            liberar_pilha(atual->topo_pilha);
            free(atual); // Libera a memória do nó atual
            atual = proximo_temp; // Avança para o próximo nó
        }
    fila->inicio = NULL; // Opcional: Garante que a lista esteja "vazia" após a liberação
    fila->fim = NULL;

    //liberação da lista
    atual = lista->inicio;

    while(atual != NULL) {
        proximo_temp = atual->prox;
        liberar_pilha(atual->topo_pilha);
        free(atual);
        atual = proximo_temp;
    }

    lista->inicio = NULL;

    //liberação da lista finalizados

    atual = listaF->inicio;

    while(atual != NULL) {
        proximo_temp = atual->prox;
        liberar_pilha(atual->topo_pilha);
        free(atual);
        atual = proximo_temp;
    }

    listaF->inicio = NULL;

}

nomeChamada *copiar_pilha(nomeChamada *topo){//funcao que foi feita para copiar a pilha de maneira que nao copiasse um lixo de memoria
    if(topo == NULL){
        return NULL;
    }

    nomeChamada *nova_pilha = NULL;
    nomeChamada *aux = topo;

    while(aux != NULL){
        nomeChamada *novo = malloc(sizeof(nomeChamada));
        strcpy(novo->nome, aux->nome);
        novo->prox = nova_pilha;
        nova_pilha = novo;
        aux = aux->prox;
    }

    return inverter_pilha(nova_pilha);
}