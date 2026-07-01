#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define T_STR       100
#define MAX_SENSORES  10
#define verificacao    20
#define tmhcod      5
#define MAX_SETORES     10
#define MAX_SENS_POR_SETOR 3
#define MAX_LEITURAS 100

typedef char string[T_STR];
typedef char verificar[verificacao];

const char *nome_tipo(int tipo) {
    switch (tipo) {
        case 1: return "Temperatura";
        case 2: return "Umidade";
        case 3: return "Pressao";
        case 4: return "Vibracao";
        case 5: return "Corrente";
        default: return "Desconhecido";
    }
};


struct sensor_t{
    string id;
    int tipo;
    float faixa_leitura_max;
    float faixa_leitura_min;
    struct sensor_t *proximo;
};

struct leitura_t{
    string id;
    verificar local_setor;
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
    verificar nome_local;
    string descricao;
    struct sensor_instalado_t sensores[MAX_SENS_POR_SETOR];
    int num_sensores;
    struct setor_t *proximo;
};

// Variáveis globais
//sensor_t sensores[MAX_SENSORES];
//leitura_t leituras[MAX_LEITURAS];
//setor_t setores[MAX_SETORES];
//media_t medias[MAX_LEITURAS];
//int toal_sensores = 0;
//int total_setores = 0;
//int total_leituras = 0;
//int total_medias = 0;

//funções especiais
void verificacaodelimite_sensor(struct sensor_t *lista);
void verificacaodelimite_setor(struct setor_t *lista);
void verificacaodelimite_leituras(struct leitura_t *lista);
void formatar_maiuscula(char *str);
void retirar_enter(char *str);
void obter_data_hora(char *data, char *horario);

//funções de arquivos
void salvar_relatorio_em_arquivo_binario(struct sensor_t *lista_sensor, struct setor_t *lista_setor,
struct leitura_t *lista_leitura, char *nome_arq);

void exportar_html(struct sensor_t *lista_sensor, struct setor_t *lista_setor, struct leitura_t *lista_leitura, char *nome_arq);
void exportar_csv(struct sensor_t *lista_sensor, struct setor_t *lista_setor, struct leitura_t *lista_leitura, char *nome_arq);

void ler_dados_arquivos_bin(struct sensor_t **lista_sensor, struct setor_t **lista_setor,
struct leitura_t **leitura, char *nome_arq);





// Protótipos

//menus
void menu_principal(void);
void menu_sensores(void);
void menu_relatorios(void);
void menu_consultas(void);
void menu_leituras(void);
void menu_de_sensores(void);
void menu_de_arquivos(void);
void menu_csv(void);
void menu_html(void);
void menu_binario(void);

//registrar, cadastrar, instalar e exibir
void registrar_leitura(struct leitura_t *lista, struct sensor_t *lista_dois, struct setor_t *lista_tres);
void exibir_leituras(struct leitura_t *lista);
struct sensor_t *novo_sensor(struct sensor_t *lista);
//sensor_t *cadastrar_sensor(struct sensor_t **lista, struct sensor_t *novo);
//struct setor_t *novo_setor(struct setor_t **lista, struct setor_t *novo);
struct setor_t *novo_setor(struct setor_t *lista);
void relatorio_sensores_geral(struct sensor_t *lista);
void relatorio_sensores_por_tipo(struct sensor_t *lista);
void relatorio_setores(struct setor_t *lista);
void relatorio_leituras(struct leitura_t *lista);
void relatorio_variacao_leitura(struct leitura_t *lista, struct leitura_t*lista_dois);
void exibir_relatorio_medias(struct sensor_t *lista);
void consultar_sensor_tipo(struct sensor_t *lista);
void consultar_setor_por_descricao(struct setor_t *lista);
void instalar_sensor_setor(struct sensor_t *lista, struct setor_t *lista_dois);

//Listar dados....: 
void listar_sensores_geral(struct sensor_t *lista);
void listar_sensores_por_tipo(struct sensor_t *lista);
void listar_setores(struct setor_t *lista);
void listar_leituras(struct leitura_t *lista);

int main() {
    menu_principal();
    return 0;
}

// Implementações

void formatar_maiuscula(char *str) {
    for (char *p = str; *p != '\0'; p++) {
        *p = toupper(*p);
    }
}


void retirar_enter(char *str) {

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
        printf("5. Menu de arquivos(csv, html e bin)\n");
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
            case 5: menu_de_arquivos();break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

void menu_sensores() {
    int opcao;
    struct sensor_t *sensor;
    struct setor_t *setor;
    sensor = (struct sensor_t*) malloc(sizeof(struct sensor_t));
    setor = (struct setor_t*)  malloc(sizeof(struct setor_t));
    do {
        printf("\n||      MENU SENSORES     ||\n");
        printf("------------------------------\n");
        printf("1. Novo sensor\n");
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
                novo_sensor(sensor);
                break;

            case 2:
                listar_sensores_geral(sensor);
                break;

            case 3:
                novo_setor(setor);
                break;
            case 4:
                instalar_sensor_setor(sensor, setor);
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
    struct sensor_t *sensor;
    struct setor_t *setor;
    struct leitura_t *leituras, *leituras_dois;
    sensor = (struct sensor_t*) malloc(sizeof(struct sensor_t*));

    setor = (struct setor_t*) malloc(sizeof(struct setor_t*));
    leituras = (struct leitura_t*) malloc(sizeof(struct leitura_t*));
    leituras_dois = (struct leitura_t*) malloc(sizeof(struct leitura_t*)); 
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
            case 1: relatorio_sensores_geral(sensor); break;
            case 2: relatorio_sensores_por_tipo(sensor); break;
            case 3: relatorio_setores(setor); break;
            case 4: relatorio_leituras(leituras); break;
            case 5: relatorio_variacao_leitura(leituras, leituras_dois); break;
            case 6: exibir_relatorio_medias(sensor); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

void menu_consultas() {
    int opcao;
    struct sensor_t *sensor;
    struct setor_t *setor;
    
    sensor = (struct sensor_t*) malloc(sizeof(struct sensor_t));
    setor = (struct setor_t*) malloc(sizeof(struct setor_t));

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
            case 1: consultar_sensor_tipo(sensor); break;
            case 2: consultar_setor_por_descricao(setor); break;
            case 0: break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

void menu_de_arquivos(){
    int opcao;
    do {
        printf("1. Menu csv\n");
        printf("2. Menu html\n");
        printf("3. Menu binário\n");
        printf("0. Voltar\n");
        printf(":::: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: menu_csv(); break;
            case 2: menu_html(); break;
            case 3: menu_binario(); break;
            case 0: break;
            default: printf("Opção inválida\n");
        }

    } while(opcao != 0);
}




void menu_leituras() {
    struct leitura_t *leituras;
    struct sensor_t *sensores;
    struct setor_t *setores;

    leituras = (struct leitura_t*) malloc(sizeof(struct leitura_t));
    sensores = (struct sensor_t*)  malloc(sizeof(struct sensor_t));
    setores  = (struct setor_t*)   malloc(sizeof(struct setor_t));
    
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
            case 1: registrar_leitura(leituras, sensores, setores); break;
            case 2: exibir_leituras(leituras); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

struct sensor_t *novo_sensor(struct sensor_t *lista) {
    struct sensor_t *novo;
    struct sensor_t *atual = lista;
    
    novo = (struct sensor_t *) malloc(sizeof(struct sensor_t));
    int tipo_int;
    int id_exist;
    printf("\n=== NOVO SENSOR ===\n");

    do {
    printf("ID do sensor (ex: EX00): ");
    fgets(novo->id, T_STR, stdin);
    retirar_enter(novo->id);
    formatar_maiuscula(novo->id);

    id_exist = 0;
    for (atual; atual != NULL; atual = atual->proximo) {
        if (strcmp(atual->id, novo->id) == 0){
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
        scanf("%i", &tipo_int);
        getchar();

        if (tipo_int < 1 || tipo_int > 5) {
            printf("Tipo invalido! Digite um valor entre 1 e 5.\n");
        }

    } while (tipo_int < 1 || tipo_int > 5);

    novo->tipo = tipo_int;

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
    novo->proximo = lista;
    lista = novo;
    return novo;
}

struct setor_t *novo_setor(struct setor_t *lista){

}

void listar_sensores_geral(struct sensor_t *lista) {
    for(lista; lista != NULL; lista = lista->proximo) {
        relatorio_sensores_geral(lista);
    }
  
}

void registrar_leitura(struct leitura_t *lista, struct sensor_t *lista_dois, struct setor_t *lista_tres) {
    verificacaodelimite_setor(lista_tres);
    struct leitura_t *aux = lista;
    int total = 0;
    for(aux; aux != NULL; aux = aux->proximo){
        total++;
    }
    if(total >= MAX_LEITURAS){
        printf("Limite de leituras atingido!");
        return;
    
    }

    struct setor_t *comp_set = lista_tres;
    struct sensor_t *comp_sen = lista_dois;
    struct leitura_t *nova_leitura;
    nova_leitura = (struct leitura_t*) malloc(sizeof(struct leitura_t));


    printf("\n=== REGISTRAR LEITURA ===\n");

    printf("ID do sensor (EX00): ");
    fgets(nova_leitura->id, T_STR, stdin);
    retirar_enter(nova_leitura->id);
    formatar_maiuscula(nova_leitura->id);

    int sensor_existe = 0;

    for (comp_sen; comp_sen != NULL; comp_sen = comp_sen->proximo) {
        if (strcmp(comp_sen->id, nova_leitura->id) == 0) {
            sensor_existe = 1;
            break;
        }
    }

    if (!sensor_existe) {
        printf("Sensor nao cadastrado!\n");
        return;
    }

    printf("ID do setor: ");
    fgets(nova_leitura->local_setor, verificacao, stdin);
    retirar_enter(nova_leitura->local_setor);
    formatar_maiuscula(nova_leitura->local_setor);  

    struct setor_t *setor_existe = NULL;

    for (comp_set; comp_set != NULL; comp_set = comp_set->proximo) {
        if (strcmp(comp_set->id, nova_leitura->local_setor) == 0) {
            setor_existe = comp_set;
            break;
        }
    }

    if (setor_existe == NULL) {
        printf("Setor nao encontrado!\n");
        return;
    }
    
    struct setor_t *s = setor_existe;

    int instalado = 0;
    for(s; s!=NULL; s= s->proximo){
        if(strcmp(s->id, nova_leitura->id) == 0){
         instalado =1;
         break;   
        }
    }
    

    
    if (!instalado) {
        printf("Sensor nao esta instalado neste setor!\n");
        return;
    }

    do {
        printf("Qual leitura (1-primeira, 2-segunda): ");
        scanf("%d", &nova_leitura->opc_leitura);
        getchar();

        if (nova_leitura->opc_leitura != 1 && nova_leitura->opc_leitura != 2) {
            printf("Digite apenas 1 ou 2!!!!\n");
        }

    } while (nova_leitura->opc_leitura != 1 && nova_leitura->opc_leitura != 2);

    printf("Valor lido: ");
    scanf("%f", &nova_leitura->valor);
    getchar();

    obter_data_hora(nova_leitura->data, nova_leitura->horario);

    nova_leitura->proximo = lista;
    lista = nova_leitura;

    

    printf("\nLeitura registrada com sucesso!\n");
    printf("Sensor: %s\n", nova_leitura->id);
    printf("Local: %s\n", nova_leitura->local_setor);
    printf("Data: %s\n", nova_leitura->data);
    printf("Horario: %s\n", nova_leitura->horario);
    printf("Valor: %.2f\n", nova_leitura->valor);
    printf("Leitura numero: %d\n", nova_leitura->opc_leitura);
}


void exibir_leituras(struct leitura_t *lista){
    verificacaodelimite_leituras(lista);
    
    struct leitura_t *atual = lista;

    printf("\n=== HISTORICO DE LEITURAS ===\n");
    for (atual; atual != NULL; atual = atual->proximo) {
        printf("Sensor: %s | Local: %s | Data: %s | Horario: %s | Valor: %.2f | Leitura: %d\n",
               atual->id,
               atual->local_setor,
               atual->data,
               atual->horario,
               atual->valor,
               atual->opc_leitura);
    }
}

void relatorio_sensores_geral(struct sensor_t *lista) {
         printf("ID: %s\n", lista->id);
         printf("Tipo: %i\n", lista->tipo);
         printf("1⁰ Leitura: %.2f\n", lista->faixa_leitura_max);
         printf("2⁰ Leitura: %.2f\n", lista->faixa_leitura_max);
}

void relatorio_sensores_por_tipo(struct sensor_t *lista) {
    int tipo_int;
    printf("Tipo (1-Temperatura 2-Umidade 3-Pressão 4-Vibração 5-Corrente): ");
    scanf("%d", &tipo_int);
    getchar();

    const char *tipo_ = nome_tipo(tipo_int);

    int encontrou = 0;
    
    struct sensor_t *atual = lista;

    printf("\n--- SENSORES DO TIPO %s ---\n", tipo_);
    
    while(atual != NULL){
        if(atual->tipo == tipo_int){
            printf("ID: %s | Faixa: %.2f-%.2f\n",
            atual->id, 
            atual->faixa_leitura_min, 
            atual->faixa_leitura_max);
            encontrou = 1;
        }
        atual = atual->proximo;
   
    }
     

    /*for (int i = 0; i < tot_sensores; i++) {
        if (strcmp(sensores[i].tipo, nome_tipo(tipo_int)) == 0) {
            printf("ID: %s | Faixa: %.2f-%.2f\n",
                   sensores[i].id, sensores[i].faixa_leitura_min, sensores[i].faixa_leitura_max);
            encontrou = 1;
        }
    }*/
    
    if (!encontrou) {
        printf("Nenhum sensor deste tipo.\n"); 
    }
        
}

void relatorio_setores(struct setor_t *lista) {
    if (lista == NULL) {
        printf("Nenhum setor cadastrado!\n");
        return;
    }

    struct setor_t *atual = lista;

    printf("\n=== RELATORIO DE SETORES ===\n");
    for (atual; atual != NULL; atual = atual->proximo) {
        printf("\nSetor ID: %s\n", atual->id);  
        printf("Nome: %s\n", atual->nome_local);
        printf("Descricao: %s\n", atual->descricao);
        printf("Sensores instalados: %d\n", atual->num_sensores);
       
       for (int i = 0; i < atual->num_sensores; i++) {
       printf("  Sensor: %s  Tipo: %s\n", 
           atual->sensores[i].id,
           atual->sensores[i].tipo);
      }
    }
}

void relatorio_leituras(struct leitura_t *lista) {
    verificacaodelimite_leituras(lista);
    int opc;
    printf("1- Por local\n2- Todos os locais: ");
    scanf("%d", &opc);
    getchar();
    struct leitura_t *atual = lista;

    if (opc == 1) {
        verificar local;
        printf("Nome do local: ");
        fgets(local, verificacao, stdin);
        retirar_enter(local);

        printf("\n=== LEITURAS DO LOCAL: %s ===\n", local);
        int encontrou = 0;
        for (atual; atual != NULL; atual = atual->proximo) {
            if (strcmp(atual->local_setor, local) == 0) {
                printf("Sensor: %s | Data: %s | Horario: %s | Valor: %.2f | Leitura: %d\n",
                       atual->id,
                       atual->data,
                       atual->horario,
                       atual->valor,
                       atual->opc_leitura);
                encontrou = 1;
            }
        }
        if (!encontrou) printf("Nenhuma leitura para este local.\n");
    } else {
        exibir_leituras(lista);
        }   
}


void relatorio_variacao_leitura(struct leitura_t *lista, struct leitura_t *lista_dois){
/* if (total_leituras < 2) {
        printf("Leituras insuficientes para calcular variacao.\n");
        return;
    }
*/
    struct leitura_t *atual = lista;
    struct leitura_t *atual_dois = lista_dois;
    printf("\n=== RELATORIO DE VARIACAO ===\n");

    int opc;
    verificar filtro;
    int encontrou = 0;
    
    printf("1 - Por setor  2 - Por sensor: ");
    scanf("%d", &opc);
    getchar();

    if (opc == 1) {
        printf("Nome do setor: ");
    } else {
        printf("ID do sensor: ");
    }
    fgets(filtro, verificacao, stdin);
    retirar_enter(filtro);
    formatar_maiuscula(filtro);

    for (atual; atual != NULL; atual = atual->proximo) {
        for (atual_dois = atual->proximo; atual_dois != NULL; atual_dois = atual_dois->proximo) {
            if (strcmp(atual->id, atual_dois->id) == 0 &&
                strcmp(atual->local_setor, atual_dois->local_setor) == 0 &&
                atual->opc_leitura == 1 && atual_dois->opc_leitura == 2) {

                verificar local_upper;
                strcpy(local_upper, atual->local_setor);
                formatar_maiuscula(local_upper);

                verificar sensor_upper;
                strcpy(sensor_upper, atual->id);
                formatar_maiuscula(sensor_upper);

                int bate = (opc == 1 && strcmp(local_upper,  filtro) == 0) ||
                           (opc == 2 && strcmp(sensor_upper, filtro) == 0);

                if (bate) {
                    float variacao = atual_dois->valor - atual->valor;
                    printf("\nSensor: %s | Local: %s\n", atual->id, atual_dois->local_setor);
                    printf("1a leitura: %.2f (%s %s)\n", atual->valor, atual->data, atual->horario);
                    printf("2a leitura: %.2f (%s %s)\n", atual_dois->valor, atual_dois->data, atual_dois->horario);
                    printf("Variacao: %.2f\n", variacao);
                    encontrou = 1;
                }
            }
        }
    }
    if (!encontrou) {
    printf("Nenhuma variação encontrada.\n");
    }
}

void exibir_relatorio_medias(struct sensor_t *lista){
    verificacaodelimite_sensor(lista);

    printf("\n=== RELATORIO DE MEDIAS POR SENSOR ===\n");
    struct sensor_t *atual = lista;
    int total_sensores = 0;
    float soma_geral = 0;
    
    for (atual; atual != NULL; atual =atual->proximo) {
        float media = (atual->faixa_leitura_min + atual->faixa_leitura_max)/2.0;
        printf("Sensor: %s | Faixa média: %.2f (min: %.2f, max: %.2f)\n",
        atual->id, media, atual->faixa_leitura_min, atual->faixa_leitura_max);
        
        soma_geral += media;
        total_sensores++;
}
    if(total_sensores > 0){
        printf("\nMédia geral das faixas: %.2f\n", soma_geral / total_sensores);
    }
}

void consultar_sensor_tipo(struct sensor_t *lista) {
   verificacaodelimite_sensor(lista);

    struct sensor_t *atual = lista;

    int tipo = menu_sensoresensor();

    int encontrou = 0;
    printf("\n--- SENSORES DO TIPO %s ---\n", nome_tipo(tipo));

    for (atual; atual!= NULL; atual = atual->proximo) {
        if (atual->tipo == tipo) { {
            printf("ID: %s | Faixa: %.2f-%.2f\n",
                   atual->id,
                   atual->faixa_leitura_min,
                   atual->faixa_leitura_max);
            encontrou = 1;
        }
    }

    if (!encontrou)
        printf("Nenhum sensor deste tipo.\n");
}

}

void consultar_setor_por_descricao(struct setor_t *lista) {
    verificacaodelimite_setor(lista);
    string busca;
    printf("Digite parte da descricao: ");
    fgets(busca, 100, stdin);
    retirar_enter(busca);

    struct setor_t *atual = lista;
    
    printf("\n--- SETORES ENCONTRADOS ---\n");
    int achou = 0;
    for (atual; atual != NULL; atual = atual->proximo) {
        if (strstr(atual->descricao, busca) != NULL) { 
            printf("ID: %s | Nome: %s | Descricao: %s\n", 
                   atual->id, atual->nome_local, atual->descricao);
            achou = 1;
        }
    }
    if (!achou) printf("Nenhum setor encontrado.\n");
}

/*void cadastrar_setor() {
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
}*/

void instalar_sensor_setor(struct sensor_t *lista, struct setor_t *lista_dois) {
    string id_sensor;
    string id_setor;
    struct sensor_t *atual = lista;
    struct setor_t *atual_dois = lista_dois;
    verificacaodelimite_sensor(atual);
    verificacaodelimite_setor(atual_dois);


    printf("\n=== INSTALAR SENSOR EM SETOR ===\n");

    printf("ID do sensor: ");
    fgets(id_sensor, T_STR, stdin);
    retirar_enter(id_sensor);
    formatar_maiuscula(id_sensor);

    struct sensor_t *encontrado_sensor = NULL;

    for (atual; atual != NULL; atual = atual->proximo) {
        if (strcmp(atual->id, id_sensor) == 0) {
            encontrado_sensor = atual;
            break;
        }
    }

    if (encontrado_sensor == NULL) {
        printf("Sensor nao encontrado!\n");
        return;
    }

    printf("ID do setor: ");
    fgets(id_setor, T_STR, stdin);
    retirar_enter(id_setor);
    formatar_maiuscula(id_setor);

    struct setor_t *encontrado_setor = NULL;

    for (atual_dois; atual_dois != NULL; atual_dois = atual_dois->proximo) {
        if (strcmp(atual_dois->id, id_setor) ==0) {
            encontrado_setor = atual_dois;
            break;
        }
    }

    if (encontrado_setor == NULL) {
        printf("Setor nao encontrado!\n");
        return;
    }

    if (encontrado_setor->num_sensores >= MAX_SENS_POR_SETOR) {
        printf("Este setor ja possui o numero maximo de sensores!\n");
        return;
    }

    for (int i = 0; i < encontrado_setor->num_sensores; i++) {
        if (strcmp(encontrado_setor->sensores[i].id, id_sensor) == 0) {
            printf("Sensor ja instalado neste setor!\n");
            return;
        }
    }
    int pos = encontrado_setor->num_sensores;
    strcpy(encontrado_setor->sensores[pos].id, encontrado_sensor->id);
    strcpy(encontrado_setor->sensores[pos].tipo, nome_tipo(encontrado_sensor->tipo));
    encontrado_setor->sensores[pos].leitura1_registrada = 0;
    encontrado_setor->sensores[pos].leitura2_registrada = 0;
    encontrado_setor->num_sensores++;
    
    printf("Sensor instalado com sucesso!\n");
    printf("Setor de instalação: %s \n", encontrado_setor->nome_local);
}

void verificacaodelimite_sensor(struct sensor_t *lista){
    if(lista == NULL){
        printf("Nenhum sensor cadastrado!\n");
        return;
     }
}
void verificacaodelimite_setor(struct setor_t *lista){
    if(lista == NULL){
        printf("Nenhum setor cadastrado!\n");
        return;
    }

}
void verificacaodelimite_leituras(struct leitura_t *lista){
    if(lista == NULL){
        printf("Nenhuma leitura realizada!\n");
        return;
    } 
}

void salvar_relatorio_em_arquivo_binario(struct sensor_t *lista_sensor, struct setor_t *lista_setor,
struct leitura_t *lista_leitura, char *nome_arq){
    FILE *fp = NULL, *fq = NULL, *fr = NULL;
    //sensor
    fp = fopen(nome_arq, "wb");
    while(lista_sensor){
        fwrite(lista_sensor, sizeof(struct sensor_t), 1, fp);
        lista_sensor = lista_sensor->proximo;
    }
    fclose(fp);

    //setor
    fq = fopen(nome_arq, "wb");
    while(lista_setor){
        fwrite(lista_setor, sizeof(struct sensor_t), 1, fq);
        lista_setor = lista_setor->proximo;
    }
    fclose(fq);

    //Leitura
    fr = fopen(nome_arq, "wb");
    while(lista_leitura){
        fwrite(lista_leitura, sizeof(struct sensor_t), 1, fr);
        lista_leitura = lista_leitura->proximo;
    }
    fclose(fr);
}

void exportar_html(struct sensor_t *lista_sensor, struct setor_t *lista_setor, struct leitura_t *lista_leitura, char *nome_arq){
    FILE *fp = NULL, *fq = NULL, *fr = NULL;
    //Sensor
    fp = fopen(nome_arq, "w");
    fprintf(fp, "<html><body>\n");
    fprintf(fp, "<table>\n");
    fprintf(fp, "<thead>\n");
    fprintf(fp, "<tr><th>ID</th><th>Tipo</th><th>Faixa de leitura Mínima</th><th>Faixa de leitura Máxima</th></tr>\n");
    fprintf(fp, "</thead>\n");
    fprintf(fp, "<tbody>\n");

    while(lista_sensor) {
        fprintf(fp, "<tr>\n");
        fprintf(fp, "<td>%s</td>", lista_sensor->id);
        fprintf(fp, "<td>%i</td>", lista_sensor->tipo);
        fprintf(fp, "<td>%.2f</td>", lista_sensor->faixa_leitura_min);
        fprintf(fp, "<td>%.2f</td>\n", lista_sensor->faixa_leitura_max);
        fprintf(fp, "</tr>\n");
        lista_sensor = lista_sensor->proximo;
    }

    fprintf(fp, "</tbody>\n");
    fprintf(fp, "</table>\n");
    fprintf(fp, "</body></html>\n");
    fclose(fp);

    //Setor
    fq = fopen(nome_arq, "w");
    fprintf(fq, "<html><body>\n");
    fprintf(fq, "<table>\n");
    fprintf(fq, "<thead>\n");
    fprintf(fq, "<tr><th>ID</th><th>Nome do local</th><th>Descrição</th><th>Número de sensores</th></tr>\n");
    fprintf(fq, "</thead>\n");
    fprintf(fq, "<tbody>\n");

    while(lista_setor) {
        fprintf(fq, "<tr>\n");
        fprintf(fq, "<td>%s</td>", lista_setor->id);
        fprintf(fq, "<td>%s</td>", lista_setor->nome_local);
        fprintf(fq, "<td>%s</td>", lista_setor->descricao);
        fprintf(fq, "<td>%i</td>", lista_setor->num_sensores);
        fprintf(fq, "</tr>\n");
        lista_setor = lista_setor->proximo;
    }

    fprintf(fq, "</tbody>\n");
    fprintf(fq, "</table>\n");
    fprintf(fq, "</body></html>\n");
    fclose(fq);

    fr = fopen(nome_arq, "w");
    fprintf(fr, "<html><body>\n");
    fprintf(fr, "<table>\n");
    fprintf(fr, "<thead>\n");
    fprintf(fr, "<tr><th>ID</th><th>tipo</th><th>Data e horário</th><th>Valor</th></tr>");
    fprintf(fr, "</thead>\n");
    fprintf(fr, "<tbody>\n");

    while(lista_leitura){
        fprintf(fr, "<tr>\n");
        fprintf(fr, "<td>%s</td>", lista_leitura->id);
        fprintf(fr, "<td>%s</td>", lista_leitura->local_setor);
        fprintf(fr, "<td>%s</td>", lista_leitura->data);
        fprintf(fr, "<td>%s</td>", lista_leitura->horario);
        fprintf(fr, "<td>%.2f</td>", lista_leitura->valor);
        fprintf(fr, "</tr>\n");
        lista_leitura= lista_leitura->proximo;

    }
    fprintf(fr, "</tbody>\n");
    fprintf(fr, "</table>\n");
    fprintf(fr, "</body></html>\n");
    fclose(fr);
}

void exportar_csv(struct sensor_t *lista_sensor, struct setor_t *lista_setor, struct leitura_t *lista_leitura, char *nome_arq) {
    FILE *fp = NULL, *fq = NULL, *fr = NULL;
    fp = fopen(nome_arq, "w");    

    while(lista_sensor){
    fprintf(fp, "%s;", lista_sensor->id);
    fprintf(fp, "%i;", lista_sensor->tipo); 
    fprintf(fp, "%.2f;", lista_sensor->faixa_leitura_max);
    fprintf(fp, "%.2f;", lista_sensor->faixa_leitura_min);
    lista_sensor = lista_sensor->proximo;
   }
   fclose(fp);

   fq = fopen(nome_arq, "w");
   while(lista_setor){
    fprintf(fq, "%s;", lista_setor->id);
    fprintf(fq, "%s;", lista_setor->nome_local);
    fprintf(fq, "%s;", lista_setor->descricao);
    fprintf(fq, "%i;", lista_setor->num_sensores);
    lista_setor = lista_setor->proximo;
   }
   fclose(fq);

   fr = fopen(nome_arq, "w");

   while(lista_leitura){
    fprintf(fr, "%s;", lista_leitura->id);
    fprintf(fr, "%s;", lista_leitura->local_setor);
    fprintf(fr, "%s;", lista_leitura->data);
    fprintf(fr, "%s;", lista_leitura->horario);
    fprintf(fr, "%.2f;", lista_leitura->valor);
    lista_leitura = lista_leitura->proximo;
   }
     
   fclose(fr);
}