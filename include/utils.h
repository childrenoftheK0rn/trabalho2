#ifndef UTILS_H
#define UTILS_H

#include "tipos.h"

const char *nome_tipo(int tipo);
void formatar_maiuscula(char *str);
void retirar_enter(char *str);
void obter_data_hora(char *data, char *horario);

/* Verificações de lista vazia — retornam 1 se vazia, 0 caso contrário */
int lista_sensor_vazia(sensor_t *lista);
int lista_setor_vazia(setor_t *lista);
int lista_leituras_vazia(leitura_t *lista);

#endif
