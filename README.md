# Trabalho-IPC-2
Sistema de gerenciamento de processos em C que simula um escalonador de processos com filas de prioridade e pilhas para funções. Permite criar, executar, cancelar e listar processos (prontos e finalizados), com interface de menu interativa, validação de PID único e liberação de memória para evitar vazamentos.


Sistema de Gerenciamento de Processos
Visão Geral
Este é um Sistema de Gerenciamento de Processos implementado em C, projetado para simular um escalonador de processos com uma fila de prioridade e execução de funções baseada em pilha. O sistema permite criar, executar, cancelar e listar processos, mantendo uma organização estruturada dos dados dos processos usando listas encadeadas e pilhas. Possui uma interface de menu interativa, validação de entrada e gerenciamento adequado de memória para evitar vazamentos.
Funcionalidades

Criação de Processos: Permite criar processos com PIDs únicos, nomes, prioridades (1 a 3) e uma pilha de funções a serem executadas.
Fila de Prioridade: Os processos são organizados em uma lista ordenada por prioridade e transferidos para uma fila FIFO para execução.
Execução de Processos: Executa processos em ordem, simulando chamadas de funções ao desempilhar da pilha e atualizando estados ('p' para pronto, 'e' para executando, 'f' para finalizado).
Cancelamento de Processos: Permite cancelar processos por PID, liberando a memória associada.
Listagem de Processos: Exibe listas de processos prontos (na fila) e finalizados.
Gerenciamento de Memória: Libera corretamente toda a memória alocada para listas, filas e pilhas, evitando vazamentos.
Compatibilidade Multiplataforma: Usa compilação condicional para limpar o terminal e pausas, suportando sistemas Windows e Unix-like.
Validação de Entrada: Garante PIDs únicos e valores de prioridade válidos (1 a 3).

Estrutura de Arquivos

main.c: Contém a lógica principal do programa, incluindo o menu interativo e operações centrais de gerenciamento de processos.
processo.c: Implementa as estruturas de dados (listas encadeadas, filas e pilhas) e funções para manipulação de processos, como criação, inserção, execução e liberação de memória.
processo.h: Arquivo de cabeçalho que define as estruturas de dados (processo, nomeChamada, Lista, ListaFinalizado, Fila) e protótipos de funções.
util.c: Fornece funções utilitárias para limpar o buffer de entrada, limpar o terminal, pausas e exibição do menu.
util.h: Arquivo de cabeçalho com protótipos das funções utilitárias.

Como Funciona

Criação de Processos:

O usuário insere um PID único, nome do processo, prioridade (1 a 3) e uma lista de nomes de funções a executar.
As funções são armazenadas em uma pilha (topo_pilha), que é invertida para garantir a ordem correta de execução.
Os processos são inseridos em uma lista ordenada por prioridade (Lista) e transferidos para uma fila FIFO (Fila).


Execução de Processos:

O sistema retira o primeiro processo da fila FIFO, define seu estado como 'executando' (e) e simula a execução das funções desempilhando cada uma da pilha.
Após executar todas as funções, o estado do processo é definido como 'finalizado' (f) e ele é movido para a lista de finalizados (ListaFinalizado).


Cancelamento de Processos:

O usuário pode cancelar um processo especificando seu PID, que é removido da fila e tem sua memória liberada, incluindo a pilha de funções.


Listagem de Processos:

Exibe todos os processos prontos na fila (PID, nome, prioridade, estado) ou todos os processos finalizados na lista de finalizados.


Gerenciamento de Memória:

O programa garante a liberação de toda a memória alocada dinamicamente (processos, pilhas de funções, listas e filas) ao encerrar o programa ou cancelar um processo.



Como Usar

Compile o programa usando um compilador C (exemplo: gcc):gcc -o gerenciador_processos main.c processo.c util.c


Execute o programa:./gerenciador_processos


Siga o menu interativo para:
Criar um novo processo (Opção 1)
Executar o próximo processo na fila (Opção 2)
Listar processos prontos (Opção 3)
Listar processos finalizados (Opção 4)
Cancelar um processo por PID (Opção 5)
Encerrar o programa (Opção 0)



Dependências

Bibliotecas padrão do C: stdio.h, stdlib.h, string.h, locale.h, unistd.h (para sistemas Unix-like) ou equivalentes no Windows.
Não são necessárias bibliotecas externas além da biblioteca padrão do C.

Observações

O programa usa setlocale para suportar caracteres UTF-8 em português na interação com o usuário.
A execução de processos é simulada com pausas (esperar) para imitar o processamento em tempo real.
A validação de entrada garante o tratamento robusto de PIDs inválidos ou prioridades fora do intervalo.
O modelo de execução baseado em pilha permite flexibilidade na definição de processos.


Licença
Este projeto é de código aberto e está disponível sob a Licença MIT.
