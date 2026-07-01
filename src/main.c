#include <stdio.h>
#include <stdlib.h>

#include "tipos.h"
#include "menus.h"
#include "arquivos.h"


int main(void) {
    sensor_t  *sensores = NULL;   /* lista de sensores cadastrados */
    setor_t   *setores  = NULL;   /* lista de setores              */
    leitura_t *leituras = NULL;   /* lista de leituras             */

  
    carregar_binario(&sensores, &setores);

    /* Loop principal */
    menu_principal(&sensores, &setores, &leituras);

    /* Persiste ao sair */
    salvar_binario(sensores, setores);

    /* Libera memória  */
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
