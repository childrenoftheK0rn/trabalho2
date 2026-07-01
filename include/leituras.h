#ifndef LEITURAS_H
#define LEITURAS_H

#include "tipos.h"

leitura_t *registrar_leitura(leitura_t *lista, sensor_t *lista_sen, setor_t *lista_set);
void       exibir_leituras(leitura_t *lista);
void       relatorio_leituras(leitura_t *lista);
void       relatorio_variacao_leitura(leitura_t *lista);

#endif
