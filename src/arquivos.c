#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/arquivos.h"
#include "../include/utils.h"

#define ARQ_SENSORES "sensores.bin"
#define ARQ_SETORES  "setores.bin"


typedef struct {
    char  id[T_STR];
    int   tipo;
    float faixa_leitura_max;
    float faixa_leitura_min;
} sensor_disco_t;

typedef struct {
    char id[T_STR];
    char tipo[T_STR];
    char horario1[6];
    char horario2[6];
    float leitura1;
    float leitura2;
    int   leitura1_registrada;
    int   leitura2_registrada;
} sensor_inst_disco_t;

typedef struct {
    char id[T_STR];
    char nome_local[TAM_VERIF];
    char descricao[T_STR];
    int  num_sensores;
} setor_disco_t;


void salvar_binario(sensor_t *lista_sen, setor_t *lista_set) {
    FILE *fp;


    fp = fopen(ARQ_SENSORES, "wb");
    if (!fp) { perror("Erro ao salvar sensores"); return; }

    for (sensor_t *p = lista_sen; p != NULL; p = p->proximo) {
        sensor_disco_t sd;
        strcpy(sd.id, p->id);
        sd.tipo              = p->tipo;
        sd.faixa_leitura_max = p->faixa_leitura_max;
        sd.faixa_leitura_min = p->faixa_leitura_min;
        fwrite(&sd, sizeof(sensor_disco_t), 1, fp);
    }
    fclose(fp);

  
    fp = fopen(ARQ_SETORES, "wb");
    if (!fp) { perror("Erro ao salvar setores"); return; }

    for (setor_t *p = lista_set; p != NULL; p = p->proximo) {
        setor_disco_t sd;
        strcpy(sd.id,         p->id);
        strcpy(sd.nome_local, p->nome_local);
        strcpy(sd.descricao,  p->descricao);
        sd.num_sensores = p->num_sensores;
        fwrite(&sd, sizeof(setor_disco_t), 1, fp);

        
        for (sensor_instalado_t *si = p->sensores; si != NULL; si = si->proximo) {
            sensor_inst_disco_t sid;
            strcpy(sid.id,   si->id);
            strcpy(sid.tipo, si->tipo);
            strcpy(sid.horario1, si->horario1);
            strcpy(sid.horario2, si->horario2);
            sid.leitura1              = si->leitura1;
            sid.leitura2              = si->leitura2;
            sid.leitura1_registrada   = si->leitura1_registrada;
            sid.leitura2_registrada   = si->leitura2_registrada;
            fwrite(&sid, sizeof(sensor_inst_disco_t), 1, fp);
        }
    }
    fclose(fp);
    printf("Dados salvos com sucesso.\n");
}

void carregar_binario(sensor_t **lista_sen, setor_t **lista_set) {
    FILE *fp;
    sensor_disco_t sd;
    setor_disco_t  ssd;
    sensor_inst_disco_t sid;

    /* ── Sensores ── */
    fp = fopen(ARQ_SENSORES, "rb");
    if (fp) {
        while (fread(&sd, sizeof(sensor_disco_t), 1, fp) == 1) {
            sensor_t *novo = (sensor_t *) malloc(sizeof(sensor_t));
            if (!novo) break;
            strcpy(novo->id, sd.id);
            novo->tipo              = sd.tipo;
            novo->faixa_leitura_max = sd.faixa_leitura_max;
            novo->faixa_leitura_min = sd.faixa_leitura_min;
            novo->proximo  = *lista_sen;
            *lista_sen     = novo;
        }
        fclose(fp);
    }

   
    fp = fopen(ARQ_SETORES, "rb");
    if (fp) {
        while (fread(&ssd, sizeof(setor_disco_t), 1, fp) == 1) {
            setor_t *novo = (setor_t *) malloc(sizeof(setor_t));
            if (!novo) break;
            strcpy(novo->id,         ssd.id);
            strcpy(novo->nome_local, ssd.nome_local);
            strcpy(novo->descricao,  ssd.descricao);
            novo->num_sensores = ssd.num_sensores;
            novo->sensores     = NULL;

          
            for (int i = 0; i < ssd.num_sensores; i++) {
                if (fread(&sid, sizeof(sensor_inst_disco_t), 1, fp) != 1) break;
                sensor_instalado_t *si = (sensor_instalado_t *) malloc(sizeof(sensor_instalado_t));
                if (!si) break;
                strcpy(si->id,   sid.id);
                strcpy(si->tipo, sid.tipo);
                strcpy(si->horario1, sid.horario1);
                strcpy(si->horario2, sid.horario2);
                si->leitura1 = sid.leitura1;
                si->leitura2= sid.leitura2;
                si->leitura1_registrada =sid.leitura1_registrada;
                si->leitura2_registrada= sid.leitura2_registrada;
                si->proximo = novo->sensores;
                novo->sensores = si;
            }
            novo->proximo = *lista_set;
            *lista_set= novo;
        }
        fclose(fp);
    }
}

void exportar_csv(sensor_t *lista_sen, setor_t *lista_set, leitura_t *lista_lei, const char *base)
{
    string nome;
    FILE *fp;
    strcpy(nome, base);
    strcat(nome, "_sensores.csv");
    fp = fopen(nome, "w");
    if (fp) {
        fprintf(fp, "ID;Tipo;Min;Max\n");
        for (sensor_t *p = lista_sen; p != NULL; p = p->proximo)
         fprintf(fp, "%s;%s;%.2f;%.2f\n", p->id, nome_tipo(p->tipo),
         p->faixa_leitura_min, p->faixa_leitura_max);
         fclose(fp);
         printf("Exportado: %s\n", nome);
    }
    
    strcpy(nome, base);
    strcat(nome, "_setores.csv");
    fp = fopen(nome, "w");
    if (fp) {
        fprintf(fp, "ID;Nome;Descricao;Num_sensores\n");
        for (setor_t *p = lista_set; p != NULL; p = p->proximo)
            fprintf(fp, "%s;%s;%s;%d\n",
                    p->id, p->nome_local,
                    p->descricao, p->num_sensores);
        fclose(fp);
        printf("Exportado: %s\n", nome);
    }

    
    strcpy(nome, base);
    strcat(nome, "_leituras.csv");
    fp = fopen(nome, "w");
    if (fp) {
        fprintf(fp, "ID_sensor;Setor;Data;Horario;Valor;Leitura\n");
        for (leitura_t *p = lista_lei; p != NULL; p = p->proximo)
            fprintf(fp, "%s;%s;%s;%s;%.2f;%d\n",
                    p->id, p->local_setor,
                    p->data, p->horario,
                    p->valor, p->opc_leitura);
        fclose(fp);
        printf("Exportado: %s\n", nome);
    }
}


void exportar_html(sensor_t  *lista_sen, setor_t   *lista_set, leitura_t *lista_lei, const char *nome_arq)
{
    FILE *fp = fopen(nome_arq, "w");
    if (!fp) { perror("Erro ao criar HTML"); return; }

    fprintf(fp, "<html><body>\n");

    fprintf(fp, "<h2>Sensores</h2>\n");
    fprintf(fp, "<table>\n");
    fprintf(fp, "<thead>\n");
    fprintf(fp, "<tr><th>ID</th><th>Tipo</th><th>Min</th><th>Max</th></tr>\n");
    fprintf(fp, "</thead>\n");
    fprintf(fp, "<tbody>\n");
    for (sensor_t *p = lista_sen; p != NULL; p = p->proximo) {
        fprintf(fp, "<tr>\n");
        fprintf(fp, "<td>%s</td>", p->id);
        fprintf(fp, "<td>%s</td>", nome_tipo(p->tipo));
        fprintf(fp, "<td>%.2f</td>", p->faixa_leitura_min);
        fprintf(fp, "<td>%.2f</td>\n", p->faixa_leitura_max);
        fprintf(fp, "</tr>\n");
    }
    fprintf(fp, "</tbody>\n");
    fprintf(fp, "</table>\n");

    fprintf(fp, "<h2>Setores</h2>\n");
    fprintf(fp, "<table>\n");
    fprintf(fp, "<thead>\n");
    fprintf(fp, "<tr><th>ID</th><th>Nome</th><th>Descricao</th><th>Sensores</th></tr>\n");
    fprintf(fp, "</thead>\n");
    fprintf(fp, "<tbody>\n");
    for (setor_t *p = lista_set; p != NULL; p = p->proximo) {
        fprintf(fp, "<tr>\n");
        fprintf(fp, "<td>%s</td>", p->id);
        fprintf(fp, "<td>%s</td>", p->nome_local);
        fprintf(fp, "<td>%s</td>", p->descricao);
        fprintf(fp, "<td>%i</td>\n", p->num_sensores);
        fprintf(fp, "</tr>\n");
    }
    fprintf(fp, "</tbody>\n");
    fprintf(fp, "</table>\n");

    fprintf(fp, "<h2>Leituras</h2>\n");
    fprintf(fp, "<table>\n");
    fprintf(fp, "<thead>\n");
    fprintf(fp, "<tr><th>Sensor</th><th>Setor</th><th>Data</th>"
                "<th>Horario</th><th>Valor</th><th>Leitura</th></tr>\n");
    fprintf(fp, "</thead>\n");
    fprintf(fp, "<tbody>\n");
    for (leitura_t *p = lista_lei; p != NULL; p = p->proximo) {
        fprintf(fp, "<tr>\n");
        fprintf(fp, "<td>%s</td>", p->id);
        fprintf(fp, "<td>%s</td>", p->local_setor);
        fprintf(fp, "<td>%s</td>", p->data);
        fprintf(fp, "<td>%s</td>", p->horario);
        fprintf(fp, "<td>%.2f</td>", p->valor);
        fprintf(fp, "<td>%i</td>\n", p->opc_leitura);
        fprintf(fp, "</tr>\n");
    }
    fprintf(fp, "</tbody>\n");
    fprintf(fp, "</table>\n");

    fprintf(fp, "</body></html>\n");

    fclose(fp);
    printf("HTML exportado: %s\n", nome_arq);
}