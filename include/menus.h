#ifndef MENUS_H
#define MENUS_H

#include "tipos.h"

void menu_principal(sensor_t **psen, setor_t **pset, leitura_t **plei);
void menu_sensores (sensor_t **psen, setor_t **pset);
void menu_setores  (sensor_t *sen,   setor_t **pset);
void menu_leituras (sensor_t *sen,   setor_t *set, leitura_t **plei);
void menu_relatorios(sensor_t *sen,  setor_t *set, leitura_t *lei);
void menu_consultas (sensor_t *sen,  setor_t *set);
void menu_arquivos  (sensor_t *sen,  setor_t *set, leitura_t *lei);
int  menu_tipo_sensor(void);

#endif
