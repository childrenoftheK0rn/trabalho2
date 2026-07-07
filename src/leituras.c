#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/leituras.h"
#include "../include/utils.h"


leitura_t *registrar_leitura(leitura_t *lista, sensor_t  *lista_sen, setor_t *lista_set)
{
    /*registrar(ou criar) leitura
    1⁰ verifica se o limite de leituras foi atingifo
    e  se existe as listas de sensores e setores....

    2⁰ alocação dinâmica com malloc de um novo ponteiro para estrutura
    fo tipo 'leitura_t'. Se o ponteiro for nulo, o conteúdo 
    da linha 33 até a 36 impede que com que a operação resulte em crash(quando
    o programa tenta mexer em um local da memória que não pertence a ele)
    
    3⁰ Registro da leitura e verificação da existência de um sensor e setor
    4⁰ Verifica se sensor está instalado no setor */
    
    //1⁰
    if (lista_sensor_vazia(lista_sen)){
         return lista;
    }
    if (lista_setor_vazia(lista_set)){
         return lista;
    }

 
    int total = 0;
    for (leitura_t *p = lista; p != NULL; p = p->proximo) total++;
    if (total >= MAX_LEITURAS) {
        printf("Limite de leituras atingido!\n");
        return lista;
    }

    //2⁰
    leitura_t *nova = (leitura_t *) malloc(sizeof(leitura_t));
    if (!nova) { 
        printf("erro!!"); 
        return lista;
     }
    
    //3⁰
    printf("\n=== REGISTRAR LEITURA ===\n");

    printf("ID do sensor: ");
    fgets(nova->id, T_STR, stdin);
    retirar_enter(nova->id);
    formatar_maiuscula(nova->id);

    sensor_t *sen = NULL;
    for (sensor_t *p = lista_sen; p != NULL; p = p->proximo) {
        if (strcmp(p->id, nova->id) == 0) {
             sen = p;
              break;
             }
    }
    if (!sen) { 
        printf("Sensor nao cadastrado!\n");
         free(nova); 
         return lista; 
        }

    printf("ID do setor: ");
    fgets(nova->local_setor, TAM_VERIF, stdin); //tam_verif é 20 e está em utils.h
    retirar_enter(nova->local_setor);
    formatar_maiuscula(nova->local_setor);

    setor_t *set = NULL;
    for (setor_t *p = lista_set; p != NULL; p = p->proximo) {
        if (strcmp(p->id, nova->local_setor) == 0) { 
            set = p;
             break;
             }
    }
    if (!set){
         printf("Setor nao encontrado!\n"); 
         free(nova); 
         return lista; 
        }

    //4⁰
    int instalado = 0;
    for (sensor_instalado_t *si = set->sensores; si != NULL; si = si->proximo) {
        if (strcmp(si->id, nova->id) == 0) { instalado = 1; break; }
    }
    if (!instalado) {
        printf("Sensor nao esta instalado neste setor!\n");
        free(nova);
        return lista;
    }

  
    do {
        printf("Qual leitura (1-primeira, 2-segunda): ");
        scanf("%d", &nova->opc_leitura);
        getchar();
        if (nova->opc_leitura != 1 && nova->opc_leitura != 2)
            printf("Digite apenas 1 ou 2!\n");
    } while (nova->opc_leitura != 1 && nova->opc_leitura != 2);

    do {
        printf("Valor lido (faixa: %.2f - %.2f): ",
               sen->faixa_leitura_min, sen->faixa_leitura_max);
        scanf("%f", &nova->valor);
        getchar();
        if (nova->valor < sen->faixa_leitura_min || nova->valor > sen->faixa_leitura_max)
            printf("Valor fora da faixa do sensor!\n");
    } while (nova->valor < sen->faixa_leitura_min || nova->valor > sen->faixa_leitura_max);

    obter_data_hora(nova->data, nova->horario);

    nova->proximo = lista;

    printf("\nLeitura registrada!\n");
    printf("Sensor: %s | Local: %s | Data: %s %s | Valor: %.2f | Leitura: %d\n",
           nova->id, nova->local_setor, nova->data,
           nova->horario, nova->valor, nova->opc_leitura);

    return nova; 
}


void exibir_leituras(leitura_t *lista) {
    /*função de exibir as leituras:
    1⁰ verifica se existe itens na lista
    2⁰ exibe o histórico através de um for de listas encadeadas... 
    */

    //1⁰
    if (lista_leituras_vazia(lista)) return;

    printf("\n=== HISTORICO DE LEITURAS ===\n");
    for (leitura_t *p = lista; p != NULL; p = p->proximo) {
        printf("Sensor: %-8s | Local: %-8s | Data: %s %s | Valor: %7.2f | Leitura: %d\n",
               p->id, p->local_setor, p->data,
               p->horario, p->valor, p->opc_leitura);
    }
}

void relatorio_leituras(leitura_t *lista) {
    /*Essa função de relatório de leituras, pode escolher se é por local
    ou todos, que retorna a função acima
    
    1⁰ verifica a existência de leituras 
    
    2⁰ a seguir um algoritmo simples para escolher entre listar leituras
    por local ou todos, isso é, se opc != 1, então é chamada a função acima
    */

    //1⁰
    if (lista_leituras_vazia(lista)) {
        return;
    }
    
    //2⁰
    int opc;
    printf("1 - Por local  2 - Todos: ");
    scanf("%d", &opc);
    getchar();

    if (opc == 1) {
        verificar local;
        printf("Nome do local (ID do setor): ");
        fgets(local, TAM_VERIF, stdin);
        retirar_enter(local);
        formatar_maiuscula(local);

        printf("\n=== LEITURAS DO LOCAL: %s ===\n", local);
        int encontrou = 0;
        for (leitura_t *p = lista; p != NULL; p = p->proximo) {
            if (strcmp(p->local_setor, local) == 0) {
                printf("Sensor: %-8s | Data: %s %s | Valor: %7.2f | Leitura: %d\n",
                       p->id, p->data, p->horario, p->valor, p->opc_leitura);
                encontrou = 1;
            }
        }
        if (!encontrou) printf("Nenhuma leitura para este local.\n");
    } else { //else(opc != 1 -> 2);
        exibir_leituras(lista);
    }
}

void relatorio_variacao_leitura(leitura_t *lista) {
    /*Relatório da variação de leitura de um sensor em um setor
  1⁰ verifica se existe uma lista com leituras.

  2⁰ criação de variáveis de controle, seleção e uma string para ser o 'filtro'
  de procura.

  3⁰ algoritmo que, objetivamente, faz a variação de leitura,
  para cada leitura tipo 1, procura uma tipo 2 do mesmo sensor e setor, então
  se bater com o filtro (setor ou sensor), calcula a variação, com isso
  exibe os dados das duas leituras e a variação encontrada, e 
  se nenhum par for encontrado, exibe mensagem de erro.
 
    */
    if (lista_leituras_vazia(lista)) 
    {
        return;
    }
    //2⁰
    printf("\n=== RELATORIO DE VARIAÇÃO ===\n");

    int opc;
    verificar filtro;
    int encontrou = 0;

    printf("1 - Por setor  2 - Por sensor: ");
    scanf("%d", &opc);
    getchar();
    if (opc == 1) {
        printf("ID do setor: ");
    } else {
        printf("ID do sensor: ");
    }
    fgets(filtro, TAM_VERIF, stdin);
    retirar_enter(filtro);
    formatar_maiuscula(filtro);
    
    //3⁰
   for (leitura_t *a = lista; a != NULL; a = a->proximo) {
    
    if (a->opc_leitura == 1)
     {
     for (leitura_t *b = lista; b != NULL; b = b->proximo) {
       if (b->opc_leitura == 2) {
         if (strcmp(a->id, b->id) == 0 && 
            strcmp(a->local_setor, b->local_setor) == 0) {
             int bate = 0;
             if (opc == 1 && strcmp(a->local_setor, filtro) == 0) {
             bate = 1;
            }
            if (opc == 2 && strcmp(a->id, filtro) == 0) {
                bate = 1;
                        }
                if (bate != 0) {
                float variacao = b->valor - a->valor;
                printf("\nSensor: %s | Local: %s\n", a->id, a->local_setor);
                printf("1a leitura: %.2f (%s %s)\n", a->valor, a->data, a->horario);
                printf("2a leitura: %.2f (%s %s)\n", b->valor, b->data, b->horario);
                printf("Variação: %+.2f\n", variacao);
                encontrou = 1;
              }
           }
        }
    }
   }
 }
    
    if (encontrou == 0) {
        printf("Nenhuma variação encontrada.\n");
    }
}

