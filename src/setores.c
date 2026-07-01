#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "setores.h"
#include "utils.h"

setor_t *novo_setor(setor_t *lista) {
    setor_t *novo = (setor_t *) malloc(sizeof(setor_t));
    if (!novo) { perror("malloc"); return lista; }

    int id_existe;
    printf("\n=== NOVO SETOR ===\n");

    do {
        printf("ID do setor (ex: AL09): ");
        fgets(novo->id, T_STR, stdin);
        retirar_enter(novo->id);
        formatar_maiuscula(novo->id);

        id_existe = 0;
        for (setor_t *p = lista; p != NULL; p = p->proximo) {
            if (strcmp(p->id, novo->id) == 0) { id_existe = 1; break; }
        }
        if (id_existe) printf("ID ja cadastrado! Tente outro.\n");
    } while (id_existe);

    printf("Nome do local: ");
    fgets(novo->nome_local, TAM_VERIF, stdin);
    retirar_enter(novo->nome_local);

    printf("Descricao: ");
    fgets(novo->descricao, T_STR, stdin);
    retirar_enter(novo->descricao);

    novo->sensores     = NULL;
    novo->num_sensores = 0;
    novo->proximo      = lista;

    printf("Setor %s cadastrado com sucesso!\n", novo->id);
    return novo;
}

void relatorio_setores(setor_t *lista) {
    if (lista_setor_vazia(lista)) return;

    printf("\n=== RELATORIO DE SETORES ===\n");
    for (setor_t *p = lista; p != NULL; p = p->proximo) {
        printf("\nID: %s | Nome: %s\nDescricao: %s\nSensores instalados: %d\n",
               p->id, p->nome_local, p->descricao, p->num_sensores);

        int i = 0;
        for (sensor_instalado_t *si = p->sensores; si != NULL; si = si->proximo) {
            printf("  [%d] ID: %s | Tipo: %s\n", ++i, si->id, si->tipo);
        }
    }
}

/* CONSULTA POR DESCRIÇÃO (iterativa) */
void consultar_setor_por_descricao(setor_t *lista) {
    if (lista_setor_vazia(lista)) return;

    string busca;
    printf("Digite parte da descricao: ");
    fgets(busca, T_STR, stdin);
    retirar_enter(busca);

    printf("\n--- SETORES ENCONTRADOS ---\n");
    int achou = 0;
    for (setor_t *p = lista; p != NULL; p = p->proximo) {
        if (strstr(p->descricao, busca) != NULL) {
            printf("ID: %s | Nome: %s | Descricao: %s\n",
                   p->id, p->nome_local, p->descricao);
            achou = 1;
        }
    }
    if (!achou) printf("Nenhum setor encontrado.\n");
}


void instalar_sensor_setor(sensor_t *lista_sen, setor_t *lista_set) {
    if (lista_sensor_vazia(lista_sen)) return;
    if (lista_setor_vazia(lista_set))  return;

    string id_sensor, id_setor;

    printf("\n=== INSTALAR SENSOR EM SETOR ===\n");

    printf("ID do sensor: ");
    fgets(id_sensor, T_STR, stdin);
    retirar_enter(id_sensor);
    formatar_maiuscula(id_sensor);

    sensor_t *sen = NULL;
    for (sensor_t *p = lista_sen; p != NULL; p = p->proximo) {
        if (strcmp(p->id, id_sensor) == 0) { sen = p; break; }
    }
    if (!sen) { printf("Sensor nao encontrado!\n"); return; }

    printf("ID do setor: ");
    fgets(id_setor, T_STR, stdin);
    retirar_enter(id_setor);
    formatar_maiuscula(id_setor);

    setor_t *set = NULL;
    for (setor_t *p = lista_set; p != NULL; p = p->proximo) {
        if (strcmp(p->id, id_setor) == 0) { set = p; break; }
    }
    if (!set) { printf("Setor nao encontrado!\n"); return; }

    if (set->num_sensores >= MAX_SENS_POR_SETOR) {
        printf("Setor ja possui o maximo de %d sensores!\n", MAX_SENS_POR_SETOR);
        return;
    }

    /* Verifica duplicata */
    for (sensor_instalado_t *si = set->sensores; si != NULL; si = si->proximo) {
        if (strcmp(si->id, id_sensor) == 0) {
            printf("Sensor ja instalado neste setor!\n");
            return;
        }
    }

    sensor_instalado_t *novo = (sensor_instalado_t *) malloc(sizeof(sensor_instalado_t));
    if (!novo) { perror("malloc"); return; }

    strcpy(novo->id,   sen->id);
    strcpy(novo->tipo, nome_tipo(sen->tipo));
    novo->leitura1_registrada = 0;
    novo->leitura2_registrada = 0;
    novo->proximo = set->sensores;
    set->sensores = novo;
    set->num_sensores++;

    printf("Sensor %s instalado no setor %s com sucesso!\n", id_sensor, set->nome_local);
}

void retirar_sensor_setor(setor_t *lista) {
    if (lista_setor_vazia(lista)) return;

    string id_setor, id_sensor;

    printf("\n=== RETIRAR SENSOR DE SETOR ===\n");
    printf("ID do setor: ");
    fgets(id_setor, T_STR, stdin);
    retirar_enter(id_setor);
    formatar_maiuscula(id_setor);

    setor_t *set = NULL;
    for (setor_t *p = lista; p != NULL; p = p->proximo) {
        if (strcmp(p->id, id_setor) == 0) { set = p; break; }
    }
    if (!set) { printf("Setor nao encontrado!\n"); return; }

    if (set->sensores == NULL) {
        printf("Nenhum sensor instalado neste setor.\n");
        return;
    }

    printf("ID do sensor a retirar: ");
    fgets(id_sensor, T_STR, stdin);
    retirar_enter(id_sensor);
    formatar_maiuscula(id_sensor);

    sensor_instalado_t *ant = NULL;
    sensor_instalado_t *cur = set->sensores;

    while (cur != NULL && strcmp(cur->id, id_sensor) != 0) {
        ant = cur;
        cur = cur->proximo;
    }

    if (!cur) { printf("Sensor nao encontrado neste setor!\n"); return; }

    if (ant == NULL)
        set->sensores = cur->proximo;  /* era o primeiro */
    else
        ant->proximo = cur->proximo;

    free(cur);
    set->num_sensores--;
    printf("Sensor %s retirado do setor %s.\n", id_sensor, set->nome_local);
}
