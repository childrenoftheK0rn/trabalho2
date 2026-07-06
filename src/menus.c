#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/menus.h"
#include "../include/sensores.h"
#include "../include/setores.h"
#include "../include/leituras.h"
#include "../include/arquivos.h"
#include "../include/utils.h"

int menu_tipo_sensor(void) {
    int opc;
    printf("\nTipos de sensor:\n");
    printf("  1 - Temperatura\n");
    printf("  2 - Umidade\n");
    printf("  3 - Pressao\n");
    printf("  4 - Vibracao\n");
    printf("  5 - Corrente\n");
    printf("Escolha: ");
    scanf("%d", &opc);
    getchar();
    return opc;
}

void menu_arquivos(sensor_t *sen, setor_t *set, leitura_t *lei) {
    int opc;
    string nome;

    do {
        printf("\n=== MENU ARQUIVOS ===\n");
        printf("1. Exportar CSV\n");
        printf("2. Exportar HTML\n");
        printf("0. Voltar\n");
        printf(":::: ");
        scanf("%d", &opc);
        getchar();

        switch (opc) {
            case 1:
                printf("Nome base dos arquivos (sem extensao): ");
                fgets(nome, T_STR, stdin);
                retirar_enter(nome);
                exportar_csv(sen, set, lei, nome);
                break;
            case 2:
                printf("Nome do arquivo HTML (ex: relatorio.html): ");
                fgets(nome, T_STR, stdin);
                retirar_enter(nome);
                exportar_html(sen, set, lei, nome);
                break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opc != 0);
}

void menu_relatorios(sensor_t *sen, setor_t *set, leitura_t *lei) {
    int opc;
    do {
        printf("\n=== MENU RELATORIOS ===\n");
        printf("1. Sensores (geral)\n");
        printf("2. Sensores (por tipo)\n");
        printf("3. Setores\n");
        printf("4. Leituras\n");
        printf("5. Variacao de leituras\n");
        printf("6. Medias por sensor\n");
        printf("0. Voltar\n");
        printf(":::: ");
        scanf("%d", &opc);
        getchar();

        switch (opc) {
            case 1: relatorio_sensores_geral(sen);     break;
            case 2: relatorio_sensores_por_tipo(sen);  break;
            case 3: relatorio_setores(set);            break;
            case 4: relatorio_leituras(lei);           break;
            case 5: relatorio_variacao_leitura(lei);   break;
            case 6: exibir_relatorio_medias(sen);      break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opc != 0);
}

void menu_consultas(sensor_t *sen, setor_t *set) {
    int opc;
    do {
        printf("\n=== MENU CONSULTAS ===\n");
        printf("1. Sensor por tipo (busca recursiva)\n");
        printf("2. Setor por descricao\n");
        printf("0. Voltar\n");
        printf(":::: ");
        scanf("%d", &opc);
        getchar();

        switch (opc) {
            case 1: consultar_sensor_tipo(sen);          break;
            case 2: consultar_setor_por_descricao(set);  break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opc != 0);
}

void menu_leituras(sensor_t *sen, setor_t *set, leitura_t **plei) {
    int opc;
    do {
        printf("\n=== MENU LEITURAS ===\n");
        printf("1. Registrar leitura\n");
        printf("2. Historico de leituras\n");
        printf("0. Voltar\n");
        printf(":::: ");
        scanf("%d", &opc);
        getchar();

        switch (opc) {
            case 1: *plei = registrar_leitura(*plei, sen, set); break;
            case 2: exibir_leituras(*plei);                     break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opc != 0);
}

void menu_setores(sensor_t *sen, setor_t **pset) {
    int opc;
    do {
        printf("\n=== MENU SETORES ===\n");
        printf("1. Cadastrar setor\n");
        printf("2. Instalar sensor em setor\n");
        printf("3. Retirar sensor de setor\n");
        printf("4. Listar setores\n");
        printf("0. Voltar\n");
        printf(":::: ");
        scanf("%d", &opc);
        getchar();

        switch (opc) {
            case 1: *pset = novo_setor(*pset);               break;
            case 2: instalar_sensor_setor(sen, *pset);       break;
            case 3: retirar_sensor_setor(*pset);             break;
            case 4: relatorio_setores(*pset);                break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opc != 0);
}

void menu_sensores(sensor_t **psen, setor_t **pset) {
    (void)pset; 
    int opc;
    do {
        printf("\n=== MENU SENSORES ===\n");
        printf("1. Novo sensor\n");
        printf("2. Listar sensores\n");
        printf("0. Voltar\n");
        printf(":::: ");
        scanf("%d", &opc);
        getchar();

        switch (opc) {
            case 1: *psen = novo_sensor(*psen);        break;
            case 2: listar_sensores_geral(*psen);      break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opc != 0);
}

void menu_principal(sensor_t **psen, setor_t **pset, leitura_t **plei) {
    int opc;
    do {
        printf("\n=========================\n");
        printf("      MENU PRINCIPAL       \n");
        printf("===========================\n");
        printf("1. Menu Sensores         \n");
        printf("2. Menu Setores          \n");
        printf("3. Menu Leituras         \n");
        printf("4. Menu Relatorios       \n");
        printf("5. Menu Consultas        \n");
        printf("6. Menu Arquivos         \n");
        printf("0. Sair (salva e fecha)  \n");
        printf("============================\n");
        printf(":::: ");
        scanf("%d", &opc);
        getchar();

        switch (opc) {
            case 1: menu_sensores(psen, pset);             break;
            case 2: menu_setores(*psen, pset);             break;
            case 3: menu_leituras(*psen, *pset, plei);     break;
            case 4: menu_relatorios(*psen, *pset, *plei);  break;
            case 5: menu_consultas(*psen, *pset);          break;
            case 6: menu_arquivos(*psen, *pset, *plei);    break;
            case 0: printf("Encerrando...\n");             break;
            default: printf("Opcao invalida!\n");
        }
    } while (opc != 0);
}
