#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sensores.h"
#include "utils.h"


sensor_t *novo_sensor(sensor_t *lista) {
    sensor_t *novo = (sensor_t *) malloc(sizeof(sensor_t));
    if (!novo) { perror("malloc"); return lista; }

    int tipo_int, id_existe;

    printf("\n=== NOVO SENSOR ===\n");

    do {
        printf("ID do sensor (ex: EX00): ");
        fgets(novo->id, T_STR, stdin);
        retirar_enter(novo->id);
        formatar_maiuscula(novo->id);

        id_existe = 0;
        for (sensor_t *p = lista; p != NULL; p = p->proximo) {
            if (strcmp(p->id, novo->id) == 0) {
                id_existe = 1;
                break;
            }
        }
        if (id_existe) printf("ID ja cadastrado! Tente outro.\n");
    } while (id_existe);


    do {
        printf("Tipo (1-Temp 2-Umid 3-Press 4-Vibr 5-Corr): ");
        scanf("%d", &tipo_int);
        getchar();
        if (tipo_int < 1 || tipo_int > 5)
            printf("Tipo invalido! Digite entre 1 e 5.\n");
    } while (tipo_int < 1 || tipo_int > 5);
    novo->tipo = tipo_int;


    do {
        printf("Faixa minima: ");
        scanf("%f", &novo->faixa_leitura_min);
        getchar();
        printf("Faixa maxima: ");
        scanf("%f", &novo->faixa_leitura_max);
        getchar();
        if (novo->faixa_leitura_max <= novo->faixa_leitura_min)
            printf("Maximo deve ser maior que o minimo!\n");
    } while (novo->faixa_leitura_max <= novo->faixa_leitura_min);

    novo->proximo = lista;
    printf("Sensor %s cadastrado com sucesso!\n", novo->id);
    return novo; 
}


void relatorio_sensores_geral(sensor_t *lista) {
    if (lista_sensor_vazia(lista)) return;

    printf("\n=== RELATORIO DE SENSORES (GERAL) ===\n");
    for (sensor_t *p = lista; p != NULL; p = p->proximo) {
        printf("ID: %-10s | Tipo: %-12s | Faixa: %.2f - %.2f\n",
               p->id,
               nome_tipo(p->tipo),
               p->faixa_leitura_min,  
               p->faixa_leitura_max);
    }
}

void listar_sensores_geral(sensor_t *lista) {
    relatorio_sensores_geral(lista);
}

void relatorio_sensores_por_tipo(sensor_t *lista) {
    if (lista_sensor_vazia(lista)) return;

    int tipo_int;
    do {
        printf("Tipo (1-Temp 2-Umid 3-Press 4-Vibr 5-Corr): ");
        scanf("%d", &tipo_int);
        getchar();
        if (tipo_int < 1 || tipo_int > 5)
            printf("Tipo invalido!\n");
    } while (tipo_int < 1 || tipo_int > 5);

    printf("\n--- SENSORES DO TIPO %s ---\n", nome_tipo(tipo_int));
    int encontrou = 0;
    for (sensor_t *p = lista; p != NULL; p = p->proximo) {
        if (p->tipo == tipo_int) {
            printf("ID: %-10s | Faixa: %.2f - %.2f\n",
                   p->id, p->faixa_leitura_min, p->faixa_leitura_max);
            encontrou = 1;
        }
    }
    if (!encontrou) printf("Nenhum sensor deste tipo.\n");
}

void listar_sensores_por_tipo(sensor_t *lista) {
    relatorio_sensores_por_tipo(lista);
}

void exibir_relatorio_medias(sensor_t *lista) {
    if (lista_sensor_vazia(lista)) return;

    printf("\n=== RELATORIO DE MEDIAS POR SENSOR ===\n");
    float soma_geral = 0;
    int   total      = 0;

    for (sensor_t *p = lista; p != NULL; p = p->proximo) {
        float media = (p->faixa_leitura_min + p->faixa_leitura_max) / 2.0f;
        printf("Sensor: %-10s | Media da faixa: %.2f (min: %.2f, max: %.2f)\n",
               p->id, media, p->faixa_leitura_min, p->faixa_leitura_max);
        soma_geral += media;
        total++;
    }
    printf("\nMedia geral das faixas: %.2f\n", soma_geral / total);
}

void consultar_sensor_tipo_rec(sensor_t *lista, int tipo, int *encontrou) {
    if (lista == NULL) return;

    if (lista->tipo == tipo) {
        printf("ID: %-10s | Faixa: %.2f - %.2f\n",
               lista->id, lista->faixa_leitura_min, lista->faixa_leitura_max);
        *encontrou = 1;
    }
    consultar_sensor_tipo_rec(lista->proximo, tipo, encontrou);
}

void consultar_sensor_tipo(sensor_t *lista) {
    if (lista_sensor_vazia(lista)) return;

    int tipo;
    do {
        printf("Tipo (1-Temp 2-Umid 3-Press 4-Vibr 5-Corr): ");
        scanf("%d", &tipo);
        getchar();
        if (tipo < 1 || tipo > 5) printf("Invalido!\n");
    } while (tipo < 1 || tipo > 5);

    printf("\n--- SENSORES DO TIPO %s (busca recursiva) ---\n", nome_tipo(tipo));
    int encontrou = 0;
    consultar_sensor_tipo_rec(lista, tipo, &encontrou);
    if (!encontrou) printf("Nenhum sensor deste tipo.\n");
}
