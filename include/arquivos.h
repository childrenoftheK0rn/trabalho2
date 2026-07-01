#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include "tipos.h"


void      salvar_binario(sensor_t *lista_sen, setor_t *lista_set);
void      carregar_binario(sensor_t **lista_sen, setor_t **lista_set);


void      exportar_csv(sensor_t *lista_sen, setor_t *lista_set,
                       leitura_t *lista_lei, const char *nome_arq);
void      exportar_html(sensor_t *lista_sen, setor_t *lista_set,
                        leitura_t *lista_lei, const char *nome_arq);

#endif
