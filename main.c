#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <unistd.h>
#include "processo.h"
#include "util.h"

int main(){
    setlocale(LC_ALL, "Portuguese_Portugal.UTF-8");
    int operacao = -1;

    Fila fila;//nomeando a lista do tipo fila

    criar_fila(&fila);//criando a fila

    Lista lista;//criando a variavel lista 

    criar_lista(&lista);//criando a lista que iremos organizar os processos

    ListaFinalizado listaF;//criando a variavel da lista de processos

    criar_listaF(&listaF);//criando a lista de processos finalizados

    processo dados;//declarando a variavel que vamos usar para jogar na lista os dados do processo

    int chamadas;//quantidade de funções que serao feitas no processo

    char funcao_nome[80];//nome das funções do processo
    
    int continuar_cadastro = 1;//variavel que controla o while de adicionar mais processos

    int continuar_execucao = 1;//variavel que controla o while de executar outro processo

    do{
        if(operacao < 0 || operacao > 5){
            limparTerminal();
        }

        menu();
        scanf("%d", &operacao);

        switch (operacao){

            case 1:
                continuar_cadastro = 1;
                while(continuar_cadastro == 1){
                    
                    while(1){
                        //Leitura dos dados
                        printf("Digite o PID do seu processo: ");
                        scanf("%d",&dados.PID);
                        limpar_buffer_stdin();
                        if(dados.PID < 0){
                            printf("Digite um valor maior ou igual a 0 \n");
                            continue;
                        }
                        if(verificar_PID(&fila,dados.PID)){
                            break;
                        }
                        printf("PID ja existente ,digite um novo PID \n");
                    }

                    printf("Digite o nome do seu processo: ");
                    fgets(dados.nome,50,stdin);
                    dados.nome[strlen(dados.nome)-1] = '\0';

                    while(1){
                        printf("Digite a prioridade que tera seu processo(1 ao 3): ");
                        scanf("%d",&dados.prioridade);
                        limpar_buffer_stdin();
                            if(dados.prioridade <=3 && dados.prioridade >=1){
                                break;
                            }   
                        printf("Digite um valor valido de prioridade");
                        limpar_buffer_stdin();
                    }

                    dados.estado = 'p';
                    dados.topo_pilha = NULL;//inicio da pilha apontando para null


                    printf("Quantas funções voce quer fazer nesse processo: ");
                    scanf("%d",&chamadas);
                    limpar_buffer_stdin();

                    for(int i=0;i<chamadas;i++){
                        printf("Nome da %dº funcao: ",i+1);
                        fgets(funcao_nome,80,stdin);
                        funcao_nome[strlen(funcao_nome)-1] = '\0';

                        dados.topo_pilha = empilhar_funcao_pilha(dados.topo_pilha,funcao_nome);//jogando os nomes das funções na pilha

                    }

                    dados.topo_pilha = inverter_pilha(dados.topo_pilha);//função que arruma os nomes das funções 

                    printf("\nDeseja cadastrar outro processo(1 - Sim, 0 - Nao): ");
                    scanf("%d", &continuar_cadastro);
                    limpar_buffer_stdin();

                    inserir_processo_ordenado(&lista,dados);//insere os processos na lista para serem ordenados

                    transferir_processos_para_fila(&lista, &fila);//transferindo os processos ordenados na fila

                    if (continuar_cadastro == 1) {
                        limparTerminal();
                    }
                }
                break;
            case 2:
                continuar_execucao = 1;
            while(continuar_execucao == 1){
                 if(fila.inicio == NULL){
                        printf("\nNao ha processos para serem executados no momento.\n");
                        continuar_execucao = 0; // Sai do loop de execucao se a fila estiver vazia
                        esperar(2);
                        break; // Sai do switch case
                    }

                processo *processo_execucao = fila.inicio;

                printf("\n--- Executando Processo ---\n");
                printf("\nPID: %d | Nome: %s | Prioridade: %d\n", processo_execucao->PID, processo_execucao->nome, processo_execucao->prioridade);

                processo_execucao->estado = 'e';

                printf("\n--- Estado do processo %s: Executando (e) ---\n", processo_execucao->nome);
                    esperar(1);

                printf("\nIniciando execucao das funcoes para o processo %s...\n", processo_execucao->nome);
                    esperar(1);

                while(processo_execucao->topo_pilha != NULL){
                        nomeChamada *funcao_atual = processo_execucao->topo_pilha; // Pega o nó da função no topo

                        printf(" \n Executando funcao: %s\n", funcao_atual->nome);
                        esperar(0.5); // Pequena pausa para simular execução de cada função

                        // "Desempilha" a funcao: o topo agora aponta para a proxima
                        processo_execucao->topo_pilha = funcao_atual->prox;
                    }

                printf("\n Processo %s \n",processo_execucao->nome);

                processo_execucao->estado = 'f';

                processo_execucao = remove_processo_fila(&fila);//removendo processo da fila

                printf("\n Todas as funcoes do processo %s foram executadas.\n", processo_execucao->nome);
                printf("\n Estado do processo %s: Finalizado (f)\n", processo_execucao->nome);
                esperar(1);
                adicionar_finalizado(&listaF, processo_execucao);//adicionando o processo que sai da fila e vai para lista de finalizados


                printf("\n Deseja executar outro processo?(1 - Sim, 0 - Nao):");
                scanf("%d",&continuar_execucao);
                limparTerminal();
            }
                break;
            case 3:
                limparTerminal();
                imprimir_fila(fila);//imprimindo a fila dos processos
                esperar(2);
                break;
            case 4:
                limparTerminal();
                imprimir_lista(listaF);//imprimindo a lista de finalizados
                esperar(2);
                break;
            case 5:
                int pid_cancelar;
                printf("Digite o PID do processo que deseja cancelar: ");
                scanf("%d", &pid_cancelar);
                cancelar_processo(&fila, pid_cancelar);//funcao que busca o PID falado e tira ele
                break;
            case 0:
                printf("Finalizando Programa...\n");
                esperar(2);
                break;
            default:
                printf("Opção inválida\n");
                esperar(2);
        }
    }while(operacao != 0);

    liberando_listas_fila(&fila,&lista,&listaF);

    return 0;
}