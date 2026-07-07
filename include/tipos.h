#ifndef TIPOS_H
#define TIPOS_H

#define T_STR            100
#define MAX_SENS_POR_SETOR 3
#define MAX_LEITURAS     100
#define TAM_VERIF         20

typedef char string[T_STR];
typedef char verificar[TAM_VERIF];


typedef struct sensor_t {
    string id;
    int    tipo;
    float  faixa_leitura_max;
    float  faixa_leitura_min;
    struct sensor_t *proximo;
} sensor_t;


typedef struct sensor_instalado_t {
    string id;
    string tipo;
    char horario1[6]; //formatação da data
    char horario2[6]; //formatação horário
    float leitura1;
    float leitura2;
    int leitura1_registrada;
    int leitura2_registrada;
    struct sensor_instalado_t *proximo;
} sensor_instalado_t;


typedef struct setor_t {
    string id;
    verificar nome_local;
    string descricao;
    sensor_instalado_t *sensores; 
    int num_sensores;
    struct setor_t *proximo;
} setor_t;


typedef struct leitura_t {
    string id;
    verificar local_setor;
    char data[11]; //formatação data
    char horario[6]; //formatação horário
    float valor;
    int opc_leitura;
    struct leitura_t *proximo;
} leitura_t;

#endif /* TIPOS_H */
