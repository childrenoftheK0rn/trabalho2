#ifndef SETORES_H
#define SETORES_H

#include "tipos.h"

setor_t *novo_setor(setor_t *lista);
void     relatorio_setores(setor_t *lista);
void     consultar_setor_por_descricao(setor_t *lista);
void     instalar_sensor_setor(sensor_t *lista_sen, setor_t *lista_set);
void     retirar_sensor_setor(setor_t *lista);

#endif
