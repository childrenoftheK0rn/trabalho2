#include <stdio.h>
#include <stdlib.h>

#include "tipos.h"
#include "menus.h"
#include "arquivos.h"


int main() {
    /*Na main, três structs do tipo, respectivamente,
     sensor_t, setor_t e leitura_t. Utilização de algumas funções de 
     arquivos de 'utils.c',
     
     */
    
    sensor_t *sensores = NULL;  
    setor_t *setores  = NULL;   
    leitura_t *leituras = NULL;  

  
    carregar_binario(&sensores, &setores);
    menu_principal(&sensores, &setores, &leituras);
    
    salvar_binario(sensores, setores);
    while (sensores) {
        sensor_t *tmp = sensores->proximo;
        free(sensores);
        sensores = tmp;
    }
    while (setores) {
        sensor_instalado_t *si = setores->sensores;
        while (si) {
            sensor_instalado_t *ts = si->proximo;
            free(si);
            si = ts;
        }
        setor_t *tmp = setores->proximo;
        free(setores);
        setores = tmp;
    }
    while (leituras) {
        leitura_t *tmp = leituras->proximo;
        free(leituras);
        leituras = tmp;
    }

    return 0;
}
