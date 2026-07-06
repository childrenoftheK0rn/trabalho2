#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#include "../include/utils.h"

const char *nome_tipo(int tipo) {
    switch (tipo) {
        case 1: return "Temperatura";
        case 2: return "Umidade";
        case 3: return "Pressao";
        case 4: return "Vibracao";
        case 5: return "Corrente";
        default: return "Desconhecido";
    }
}

void formatar_maiuscula(char *str) {
    for (char *p = str; *p != '\0'; p++)
        *p = toupper((unsigned char)*p);
}


void retirar_enter(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

void obter_data_hora(char *data, char *horario) {
    time_t t = time(NULL);
    struct tm *tm_local = localtime(&t);
    strftime(data,    11, "%d/%m/%Y", tm_local);
    strftime(horario,  6, "%H:%M",    tm_local);
}


int lista_sensor_vazia(sensor_t *lista) {
    if (lista == NULL) {
        printf("Nenhum sensor cadastrado!\n");
        return 1;
    }
    return 0;
}

int lista_setor_vazia(setor_t *lista) {
    if (lista == NULL) {
        printf("Nenhum setor cadastrado!\n");
        return 1;
    }
    return 0;
}

int lista_leituras_vazia(leitura_t *lista) {
    if (lista == NULL) {
        printf("Nenhuma leitura realizada!\n");
        return 1;
    }
    return 0;
}
