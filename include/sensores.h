#ifndef SENSORES_H
#define SENSORES_H

#include "tipos.h"

sensor_t *novo_sensor(sensor_t *lista);
void listar_sensores_geral(sensor_t *lista);
void listar_sensores_por_tipo(sensor_t *lista);
void relatorio_sensores_geral(sensor_t *lista);
void relatorio_sensores_por_tipo(sensor_t *lista);
void exibir_relatorio_medias(sensor_t *lista);
/* Busca recursiva por tipo */
void consultar_sensor_tipo_rec(sensor_t *lista, int tipo, int *encontrou);
void consultar_sensor_tipo(sensor_t *lista);

#endif
