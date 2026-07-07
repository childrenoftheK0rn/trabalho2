#include <stdio.h>
#include <stdlib.h>

#include "tipos.h"
#include "menus.h"
#include "arquivos.h"


int main() {
    /*
     1⁰ - Na main, três structs do tipo, respectivamente,
     sensor_t, setor_t e leitura_t. Utilização de algumas funções de 
     arquivos de 'arquivos.c' como a carregar binário e salvar binários  
     
     2⁰ - Loops (while sensores, while setores, while leituras)
     para liberarem as memórias alocadas dinamicamente, para não causar vazamento de memória.

     
     3⁰ - seguindo o intuito do último programa de só chamar uma função principal:
     'menu_principal' ele aparece como "eixo" do programa, 
     por sua vez chama as outras funções. 
     
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
