#ifndef MENUS_H
#define MENUS_H

#include "tipos.h"

void menu_principal(sensor_t **lista_lista_sensor, setor_t **lista_lista_setor, 
    leitura_t **lista_lista_leitura);
void menu_sensores (sensor_t **lista_lista_sensor, setor_t **lista_lista_setor);
void menu_setores  (sensor_t *lista_sensor, setor_t **lista_lista_setor);
void menu_leituras (sensor_t *lista_sensor, setor_t *lista_setor, 
    leitura_t **lista_lista_leitura);
void menu_relatorios (sensor_t *lista_sensor, setor_t *lista_setor, leitura_t
*lista_leitura);
void menu_consultas (sensor_t *lista_sensor, setor_t *lista_setor);
void menu_arquivos  (sensor_t *lista_sensor, setor_t *lista_setor,
     leitura_t *lista_leitura);
int  menu_tipo_sensor(void);

#endif
