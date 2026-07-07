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

/*void formatar_maiuscula(char *str) {

    for (char *p = str; *p != '\0'; p++)
        *p = toupper((unsigned char)*p);
}
*/ 

void formatar_maiuscula(char *str) {
    //formata maiúscula, percorrendo cada caracter...
    while (*str) {
        *str = toupper(*str);
        str++;
    }
}

void retirar_enter(char *str) {
    /*percorre até o final da string e 
    se não for vazia e o último caractere for '\n' então = '\0'*/
    char *p;
    for (p = str; *p != '\0'; p++);
    if (p > str && *(p - 1) == '\n')
        *(p - 1) = '\0';
}

/*void retirar_enter(char *str) {

    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}
        */

void obter_data_hora(char *data, char *horario) {
    /*obter data hora atuais no formato DD/MM/AAAA, ex 6/7/2026
    funcionamento do strftime: string + tamanho do buffer + formatação da string + ponteiro para a struct tm);
    */
    time_t t = time(NULL);
    struct tm *tm_local = localtime(&t);
    strftime(data,11, "%d/%m/%Y", tm_local); //data dd/mm/aa, para
    strftime(horario, 6, "%H:%M", tm_local); //horário hh/mm;
}


int lista_sensor_vazia(sensor_t *lista) {
    //função do tipo int, podendo retornar 0 ou 1
    if (lista == NULL) {
        printf("Nenhum sensor cadastrado!\n");
        return 1;
    }
    return 0;
}

int lista_setor_vazia(setor_t *lista) {
    //funçao do tipo int, podendo retornar 0 ou 1
    if (lista == NULL) {
        printf("Nenhum setor cadastrado!\n");
        return 1;
    }
    return 0;
}

int lista_leituras_vazia(leitura_t *lista) {
    //função do tipo int, podendo retornar 0 ou 1
    if (lista == NULL) {
        printf("Nenhuma leitura realizada!\n");
        return 1;
    }
    return 0;
}
