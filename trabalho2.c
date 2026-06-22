#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define T_STR       100
#define MAX_SENSORES  10
#define FIM         0
#define tmhcod      5
#define MAX_SETORES     10
#define MAX_SENS_POR_SETOR 3
#define MAX_LEITURAS 100

typedef char string[T_STR];

const char *nome_tipo(int tipo) {
    switch (tipo) {
        case 1: return "Temperatura";
        case 2: return "Umidade";
        case 3: return "Pressao";
        case 4: return "Vibracao";
        case 5: return "Corrente";
        default: return "Desconhecido";
    }
}


struct sensor_t{
    string id;
    int tipo;
    float faixa_leitura_max;
    float faixa_leitura_min;
    nome_tipo(tipo);
    struct sensor_t *proximo;
};

struct leitura_t{
    string id;
    char local_setor[20];
    char data[11];
    char horario[6];
    float valor;
    int opc_leitura;
    struct leitura_t *proximo;
};

struct media_t{
    string id_sensor;
    string local_setor;
    float media;
    int total_leituras;
    char data_calculo[11];
    char horario_calculo[6];
    struct media_t *proximo;
};

struct sensor_instalado_t {
    string id;
    string tipo;
    char horario1[6];
    char horario2[6];
    float leitura1;
    float leitura2;
    int leitura1_registrada;
    int leitura2_registrada;
    struct sensor_instalado_t *proximo;
};

struct setor_t{
    string id;
    char nome_local[20];
    char descricao[100];
    sensor_instalado_t sensores[MAX_SENS_POR_SETOR];
    int num_sensores;
    struct setor_t *proximo;
};

// Variáveis globais
//sensor_t sensores[MAX_SENSORES];
//leitura_t leituras[MAX_LEITURAS];
//setor_t setores[MAX_SETORES];
//media_t medias[MAX_LEITURAS];
//int tot_sensores = 0;
//int total_setores = 0;
//int total_leituras = 0;
//int total_medias = 0;




// Protótipos
void formatar_maiuscula(string *str);
void retirar_enter(string *str);
void obter_data_hora(char *data, char *horario);
void menu_principal(void);
void menu_sensores(void);
void menu_relatorios(void);
void menu_consultas(void);
void menu_leituras(void);
int menu_sensoresensor(void);
void registrar_leitura(void);
void exibir_leituras(void);
sensor_t *novo_sensor(void);
sensor_t *cadastrar_sensor(struct sensor_t **lista, struct sensor_t *novo);
void listar_sensores(struct sensor_t *lista);
struct setor_t *cadastrar_setor(struct setor_t **lista, struct setor_t *novo);
void relat_sensores_geral(void);
void relat_sensores_por_tipo(void);
void relat_setores(void);
void relat_leituras(void);
void relat_varlet(void);
void exibir_relatorio_medias(void);
void consulsensortipo(void);
void consultarSetorPorDescricao(void);
void instalar_sensor_setor(void);

void verificacaodelimite();

int main() {
    menu_principal();
    return 0;
}

// Implementações

void formatar_maiuscula(string str) {
    for (int i = 0; i < strlen(str); i++) {
        str[i] = toupper(str[i]);
    }
}

void retirar_enter(string *str) {
    *(str + strlen(str) - 1) = '\0';
}

void obter_data_hora(char *data, char *horario) {
    time_t t = time(NULL);
    struct tm *tm_local = localtime(&t);
    strftime(data, 11, "%d/%m/%Y", tm_local);
    strftime(horario, 6, "%H:%M", tm_local);
}

int menu_sensoresensor() {
    int opcao;
    printf("\nTipos de sensor:\n");
    printf("1 -> Temperatura\n");
    printf("2 -> Umidade\n");
    printf("3 -> Pressao\n");
    printf("4 -> Vibracao\n");
    printf("5 -> Corrente\n");
    printf("Escolha: ");
    scanf("%d", &opcao);
    getchar();
    return opcao;
}

void menu_principal() {
    int opcao;

    do {
        printf("\n||    MENU PRINCIPAL    ||\n");
        printf("----------------------------\n");
        printf("1. Menu dos sensores\n");
        printf("2. Menu de Relatorios\n");
        printf("3. Menu de Consultas\n");
        printf("4. Menu de Leituras\n");
        printf("0. Sair\n");
        printf("----------------------------\n");
        printf(":::: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: menu_sensores(); break;
            case 2: menu_relatorios(); break;
            case 3: menu_consultas(); break;
            case 4: menu_leituras(); break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

void menu_sensores() {
    int opcao;
    do {
        printf("\n||      MENU SENSORES     ||\n");
        printf("------------------------------\n");
        printf("1. Cadastrar sensor\n");
        printf("2. Sensores cadastrados\n");
        printf("3. Cadastrar setor\n");
        printf("4. Instalar sensor em um setor\n");
        printf("0. Voltar\n");
        printf("------------------------------\n");
        printf(":::: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                cadastrar_sensor();
                break;

            case 2:
                listar_sensores();
                break;

            case 3:
                cadastrar_setor();
                break;
            case 4:
                instalar_sensor_setor();
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);
}
void menu_relatorios() {
    int opcao;
    do {
        printf("\n||       MENU RELATORIOS       ||\n");
        printf("---------------------------------\n");
        printf("1. Relatorio de sensores (geral)\n");
        printf("2. Relatorio de sensores (por tipo)\n");
        printf("3. Relatorio de setores\n");
        printf("4. Relatorio de leituras\n");
        printf("5. Relatorio de variacao\n");
        printf("6. Relatorio de medias\n");
        printf("0. Voltar\n");
        printf("---------------------------------\n");
        printf(":::: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: relat_sensores_geral(); break;
            case 2: relat_sensores_por_tipo(); break;
            case 3: relat_setores(); break;
            case 4: relat_leituras(); break;
            case 5: relat_varlet(); break;
            case 6: exibir_relatorio_medias(); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

void menu_consultas() {
    int opcao;
    do {
        printf("\n||       MENU CONSULTAS       ||\n");
        printf("--------------------------------\n");
        printf("1. Pesquisar sensor por tipo\n");
        printf("2. Pesquisar setor por descricao\n");
        printf("0. Voltar\n");
        printf("--------------------------------\n");
        printf(":::: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: consulsensortipo(); break;
            case 2: consultarSetorPorDescricao(); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

void menu_leituras() {
    int opcao;
    do {
        printf("\n=== MENU LEITURAS ===\n");
        printf("1. Registrar leitura\n");
        printf("2. Exibir historico de leituras\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();
        
        switch(opcao) {
            case 1: registrar_leitura(); break;
            case 2: exibir_leituras(); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

struct sensor_t *novo_sensor(struct sensor_t *lista) {
    struct sensor_t *novo = NULL;
    novo = (sensor_t *) malloc(sizeof(sensor_t))
    int tipo_int;
    int id_exist;
    printf("\n=== NOVO SENSOR ===\n");

    do {
    printf("ID do sensor (ex: EX00): ");
    fgets(novo->id, T_STR, stdin);
    retirar_enter(s->id);
    formatar_maiuscula(s->id);

    id_exist = 0;
    for (lista; lista != NULL; lista = lista->proximo) {
        if (strcmp(sensores[i].id, s.id) == 0){
            id_exist = 1;
            break;
        }
    }
    if (id_exist) {
        printf("Id já cadastrado!\n");
    }
    } while (id_exist);


    do {
        printf("Tipo (1-Temp 2-Umid 3-Press 4-Vibr 5-Corr): ");
        scanf("%i", &novo->nome_tipo(tipo_int));
        getchar();

        if (tipo_int < 1 || tipo_int > 5) {
            printf("Tipo invalido! Digite um valor entre 1 e 5.\n");
        }

    } while (tipo_int < 1 || tipo_int > 5);

    strcpy(novo->tipo, nome_tipo(tipo_int));

    do {
    printf("Faixa de leitura (valor minimo): ");
    scanf("%f", &novo->faixa_leitura_min);
    getchar();

    printf("Faixa de leitura (valor maximo): ");
    scanf("%f", &novo->faixa_leitura_max);
    getchar();

    if (novo->faixa_leitura_max <= novo->faixa_leitura_min) {
        printf("Erro: o valor maximo deve ser maior que o minimo!\n");
        }

    } while (novo->faixa_leitura_max <= novo->faixa_leitura_min);

    return novo;
}

sensor_t *cadastrar_sensor(struct sensor_t **lista, struct sensor_t *novo){
    if (tot_sensores >= MAX_SENSORES) {
        printf("Limite de sensores atingido!\n");
        return;
    }

    sensor_t s = novo_sensor();
    for (int i = 0; i < tot_sensores; i++) {
        if (strcmp(sensores[i].id, s.id) == 0) {
            printf("Erro: ID ja existe!\n");
            return;
        }
    }
    sensores[tot_sensores] = s;
    tot_sensores++;
    printf("Sensor %s cadastrado com sucesso!\n", s.id);
}

void listar_sensores() {
    if (tot_sensores == 0) {
        printf("Nenhum sensor cadastrado.\n");
        return;
    }
    printf("\n------------------------------------\n");
    printf("%-10s %-10s %-15s %-15s\n", "ID", "Tipo", "Faixa Min", "Faixa Max");
    printf("------------------------------------\n");
    for (int i = 0; i < tot_sensores; i++) {
        printf("%-10s %-10s %-15.2f %-15.2f\n",
               sensores[i].id,
               sensores[i].tipo,
               sensores[i].faixa_leitura_min,
               sensores[i].faixa_leitura_max);
    }
    printf("------------------------------------\n");
}

void registrar_leitura() {
    if (total_setores == 0) {
        printf("Nenhum setor cadastrado!\n");
        return;
    }

    if (total_leituras >= MAX_LEITURAS) {
        printf("Limite de leituras atingido!\n");
        return;
    }

    leitura_t nova_leitura;

    printf("\n=== REGISTRAR LEITURA ===\n");

    printf("ID do sensor (EX00): ");
    fgets(nova_leitura.id, T_STR, stdin);
    retirar_enter(nova_leitura.id);
    formatar_maiuscula(nova_leitura.id);

    int sensor_existe = 0;

    for (int i = 0; i < tot_sensores; i++) {
        if (strcmp(sensores[i].id, nova_leitura.id) == 0) {
            sensor_existe = 1;
            break;
        }
    }

    if (!sensor_existe) {
        printf("Sensor nao cadastrado!\n");
        return;
    }

    printf("ID do setor: ");
    fgets(nova_leitura.local_setor, 20, stdin);
    retirar_enter(nova_leitura.local_setor);
    formatar_maiuscula(nova_leitura.local_setor);  

    int setor_existe = 0;

    for (int i = 0; i < total_setores; i++) {
        if (strcmp(setores[i].id, nova_leitura.local_setor) == 0) {
            setor_existe = 1;
            break;
        }
    }

    if (!setor_existe) {
        printf("Setor nao encontrado!\n");
        return;
    }
    
    int instalado = 0;

    for (int i = 0; i < total_setores; i++) {
    
        if (strcmp(setores[i].id, nova_leitura.local_setor) == 0) {
            for (int j = 0; j < setores[i].num_sensores; j++) {
                if (strcmp(setores[i].sensores[j].id, nova_leitura.id) == 0) {
                    instalado = 1;
                    break;
                }
            }
        }
    }

    if (!instalado) {
        printf("Sensor nao esta instalado neste setor!\n");
        return;
    }

    do {
        printf("Qual leitura (1-primeira, 2-segunda): ");
        scanf("%d", &nova_leitura.opc_leitura);
        getchar();

        if (nova_leitura.opc_leitura != 1 && nova_leitura.opc_leitura != 2) {
            printf("Digite apenas 1 ou 2.\n");
        }

    } while (nova_leitura.opc_leitura != 1 && nova_leitura.opc_leitura != 2);

    printf("Valor lido: ");
    scanf("%f", &nova_leitura.valor);
    getchar();

    obter_data_hora(nova_leitura.data, nova_leitura.horario);

    leituras[total_leituras] = nova_leitura;
    total_leituras++;

    printf("\nLeitura registrada com sucesso!\n");
    printf("Sensor: %s\n", nova_leitura.id);
    printf("Local: %s\n", nova_leitura.local_setor);
    printf("Data: %s\n", nova_leitura.data);
    printf("Horario: %s\n", nova_leitura.horario);
    printf("Valor: %.2f\n", nova_leitura.valor);
    printf("Leitura numero: %d\n", nova_leitura.opc_leitura);
}


void exibir_leituras() {
    if (total_leituras == 0) {
        printf("\nNenhuma leitura registrada.\n");
        return;
    }
    
    printf("\n=== HISTORICO DE LEITURAS ===\n");
    for (int i = 0; i < total_leituras; i++) {
        printf("Sensor: %s | Local: %s | Data: %s | Horario: %s | Valor: %.2f | Leitura: %d\n",
               leituras[i].id,
               leituras[i].local_setor,
               leituras[i].data,
               leituras[i].horario,
               leituras[i].valor,
               leituras[i].opc_leitura);
    }
}

void relat_sensores_geral() {
    if (tot_sensores == 0) {
        printf("Nenhum sensor cadastrado.\n");
        return;
    }
    printf("\n--- RELATORIO GERAL DE SENSORES ---\n");
    for (int i = 0; i < tot_sensores; i++) {
        printf("ID: %s | Tipo: %s | Faixa: %.2f-%.2f\n",
               sensores[i].id, sensores[i].tipo, 
               sensores[i].faixa_leitura_min, sensores[i].faixa_leitura_max);
    }
}

void relat_sensores_por_tipo() {
    int tipo_int;
    printf("Tipo (1-Temperatura 2-Umidade 3-Pressão 4-Vibração 5-Corrente): ");
    scanf("%d", &tipo_int);
    getchar();

    int encontrou = 0;
    printf("\n--- SENSORES DO TIPO %s ---\n", nome_tipo(tipo_int));
    for (int i = 0; i < tot_sensores; i++) {
        if (strcmp(sensores[i].tipo, nome_tipo(tipo_int)) == 0) {
            printf("ID: %s | Faixa: %.2f-%.2f\n",
                   sensores[i].id, sensores[i].faixa_leitura_min, sensores[i].faixa_leitura_max);
            encontrou = 1;
        }
    }
    
    if (!encontrou) {
        printf("Nenhum sensor deste tipo.\n"); 
    }
        
}

void relat_setores() {
    if (total_setores == 0) {
        printf("Nenhum setor cadastrado!\n");
        return;
    }

    printf("\n=== RELATORIO DE SETORES ===\n");
    for (int i = 0; i < total_setores; i++) {
        printf("\nSetor ID: %s\n", setores[i].id);  
        printf("Nome: %s\n", setores[i].nome_local);
        printf("Descricao: %s\n", setores[i].descricao);
        printf("Sensores instalados: %d\n", setores[i].num_sensores);
        for (int j = 0; j < setores[i].num_sensores; j++) {
            printf("  Sensor: %s Tipo: %s\n",  
                setores[i].sensores[j].id,
                setores[i].sensores[j].tipo);
        }
    }
}

void relat_leituras() {
    if (total_leituras == 0) {
        printf("Nenhuma leitura registrada.\n");
        return;
    }

    int opc;
    printf("1- Por local\n2- Todos os locais: ");
    scanf("%d", &opc);
    getchar();

    if (opc == 1) {
        char local[20];
        printf("Nome do local: ");
        fgets(local, 20, stdin);
        retirar_enter(local);

        printf("\n=== LEITURAS DO LOCAL: %s ===\n", local);
        int achou = 0;
        for (int i = 0; i < total_leituras; i++) {
            if (strcmp(leituras[i].local_setor, local) == 0) {
                printf("Sensor: %s | Data: %s | Horario: %s | Valor: %.2f | Leitura: %d\n",
                       leituras[i].id,
                       leituras[i].data,
                       leituras[i].horario,
                       leituras[i].valor,
                       leituras[i].opc_leitura);
                achou = 1;
            }
        }
        if (!achou) printf("Nenhuma leitura para este local.\n");
    } else {
        exibir_leituras();
        }   
}


void relat_varlet() {
    if (total_leituras < 2) {
        printf("Leituras insuficientes para calcular variacao.\n");
        return;
    }

    printf("\n=== RELATORIO DE VARIACAO ===\n");

    int opc;
    string filtro;
    int encontrou = 0;
    
    printf("1 - Por setor  2 - Por sensor: ");
    scanf("%d", &opc);
    getchar();

    if (opc == 1) {
        printf("Nome do setor: ");
    } else {
        printf("ID do sensor: ");
    }
    fgets(filtro, T_STR, stdin);
    retirar_enter(filtro);
    formatar_maiuscula(filtro);

    for (int i = 0; i < total_leituras; i++) {
        for (int j = i + 1; j < total_leituras; j++) {
            if (strcmp(leituras[i].id, leituras[j].id) == 0 &&
                strcmp(leituras[i].local_setor, leituras[j].local_setor) == 0 &&
                leituras[i].opc_leitura == 1 && leituras[j].opc_leitura == 2) {

                char local_upper[20];
                strcpy(local_upper, leituras[i].local_setor);
                formatar_maiuscula(local_upper);

                char sensor_upper[T_STR];
                strcpy(sensor_upper, leituras[i].id);
                formatar_maiuscula(sensor_upper);

                int bate = (opc == 1 && strcmp(local_upper,  filtro) == 0) ||
                           (opc == 2 && strcmp(sensor_upper, filtro) == 0);

                if (bate) {
                    float variacao = leituras[j].valor - leituras[i].valor;
                    printf("\nSensor: %s | Local: %s\n", leituras[i].id, leituras[i].local_setor);
                    printf("1a leitura: %.2f (%s %s)\n", leituras[i].valor, leituras[i].data, leituras[i].horario);
                    printf("2a leitura: %.2f (%s %s)\n", leituras[j].valor, leituras[j].data, leituras[j].horario);
                    printf("Variacao: %.2f\n", variacao);
                    encontrou = 1;
                }
            }
        }
    }
    if (!encontrou) {
    printf("Nenhuma variacao encontrada.\n");
    }
}

void exibir_relatorio_medias() {
    if (total_leituras == 0) {
        printf("Nenhuma leitura registrada.\n");
        return;
    }
    
    printf("\n=== RELATORIO DE MEDIAS POR SENSOR ===\n");
    char sensores_unicos[MAX_LEITURAS][T_STR];
    float somas[MAX_LEITURAS] = {0};
    int contagens[MAX_LEITURAS] = {0};
    int qtd = 0;
    
    for (int i = 0; i < total_leituras; i++) {
        int encontrado = -1;
        for (int j = 0; j < qtd; j++) {
            if (strcmp(sensores_unicos[j], leituras[i].id) == 0) {
                encontrado = j;
                break;
            }
        }
        if (encontrado == -1) {
            strcpy(sensores_unicos[qtd], leituras[i].id);
            somas[qtd] = leituras[i].valor;
            contagens[qtd] = 1;
            qtd++;
        } else {
            somas[encontrado] += leituras[i].valor;
            contagens[encontrado]++;
        }
    }
    
    for (int i = 0; i < qtd; i++) {
        float media = somas[i] / contagens[i];
        printf("Sensor: %s | Media: %.2f (%d leituras)\n", sensores_unicos[i], media, contagens[i]);
    }
}

void consulsensortipo() {
    if (tot_sensores == 0) {
        printf("Nenhum sensor cadastrado.\n");
        return;
    }

    int tipo = menu_sensoresensor();

    int encontrou = 0;
    printf("\n--- SENSORES DO TIPO %s ---\n", nome_tipo(tipo));

    for (int i = 0; i < tot_sensores; i++) {
        if (strcmp(sensores[i].tipo, nome_tipo(tipo)) == 0) {
            printf("ID: %s | Faixa: %.2f-%.2f\n",
                   sensores[i].id,
                   sensores[i].faixa_leitura_min,
                   sensores[i].faixa_leitura_max);
            encontrou = 1;
        }
    }

    if (!encontrou)
        printf("Nenhum sensor deste tipo.\n");
}

void consultarSetorPorDescricao() {
    if (total_setores == 0) {
        printf("Nenhum setor cadastrado.\n");
        return;
    }
    char busca[100];
    printf("Digite parte da descricao: ");
    fgets(busca, 100, stdin);
    retirar_enter(busca);
    
    printf("\n--- SETORES ENCONTRADOS ---\n");
    int achou = 0;
    for (int i = 0; i < total_setores; i++) {
        if (strstr(setores[i].descricao, busca) != NULL) { 
            printf("ID: %s | Nome: %s | Descricao: %s\n", 
                   setores[i].id, setores[i].nome_local, setores[i].descricao);
            achou = 1;
        }
    }
    if (!achou) printf("Nenhum setor encontrado.\n");
}

void cadastrar_setor() {
    if (total_setores >= MAX_SETORES) {
        printf("Limite de setores atingido!\n");
        return;
    }

    setor_t s;

    printf("ID do setor (ex: AL09): "); 
    fgets(s.id, T_STR, stdin);
    retirar_enter(s.id);
    formatar_maiuscula(s.id);  
    
    for (int i = 0; i < total_setores; i++) {
        if (strcmp(setores[i].id, s.id) == 0) {
            printf("Erro: ID de setor ja cadastrado!\n");
            return;
        }
    }
    
    printf("Nome do local: ");
    fgets(s.nome_local, 20, stdin);
    retirar_enter(s.nome_local);

    
    printf("Descricao: ");
    fgets(s.descricao, 100, stdin);
    retirar_enter(s.descricao);

    s.num_sensores = 0;

    setores[total_setores] = s;
    total_setores++;

    printf("Setor cadastrado com sucesso!\n");
}

void instalar_sensor_setor() {
    string id_sensor;
    string id_setor;

    if (tot_sensores == 0) {
        printf("Nenhum sensor cadastrado!\n");
        return;
    }

    if (total_setores == 0) {
        printf("Nenhum setor cadastrado!\n");
        return;
    }

    printf("\n=== INSTALAR SENSOR EM SETOR ===\n");

    printf("ID do sensor: ");
    fgets(id_sensor, T_STR, stdin);
    retirar_enter(id_sensor);
    formatar_maiuscula(id_sensor);

    int pos_sensor = -1;

    for (int i = 0; i < tot_sensores; i++) {
        if (strcmp(sensores[i].id, id_sensor) == 0) {
            pos_sensor = i;
            break;
        }
    }

    if (pos_sensor == -1) {
        printf("Sensor nao encontrado!\n");
        return;
    }

    printf("ID do setor: ");
    fgets(id_setor, T_STR, stdin);
    retirar_enter(id_setor);

    int pos_setor = -1;

    for (int i = 0; i < total_setores; i++) {
        if (strcmp(setores[i].id, id_setor) ==0) {
            pos_setor = i;
            break;
        }
    }

    if (pos_setor == -1) {
        printf("Setor nao encontrado!\n");
        return;
    }

    if (setores[pos_setor].num_sensores >= MAX_SENS_POR_SETOR) {
        printf("Este setor ja possui o numero maximo de sensores!\n");
        return;
    }

    for (int i = 0; i < setores[pos_setor].num_sensores; i++) {
        if (strcmp(setores[pos_setor].sensores[i].id, id_sensor) == 0) {
            printf("Sensor ja instalado neste setor!\n");
            return;
        }
    }

    int pos = setores[pos_setor].num_sensores;

    strcpy(setores[pos_setor].sensores[pos].id, sensores[pos_sensor].id);
    strcpy(setores[pos_setor].sensores[pos].tipo, sensores[pos_sensor].tipo);

    setores[pos_setor].sensores[pos].leitura1_registrada = 0;
    setores[pos_setor].sensores[pos].leitura2_registrada = 0;

    setores[pos_setor].num_sensores++;

    printf("Sensor instalado com sucesso!\n");
}
