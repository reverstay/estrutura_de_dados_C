#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Estrutura para a árvore binária de passageiros
struct tree {
    char nome[30];
    struct tree *left;
    struct tree *right;
};

// Estrutura para os dados de um voo
struct node {
    struct node *prox;
    char Id[8];
    char Destino[4];
    char Empresa[20];
    char Modelo[20];
    int Np;
    struct tree *lp; // Árvore de passageiros
};

// Estrutura para a fila de voos
struct queue {
    struct node *front;
    struct node *rear;
};

struct queue *voo;

// Função para inicializar a fila de voos
void inicializarFila();

// Função para limpar o buffer de entrada
void clearBuffer();

// Função para verificar se uma string é alfanumérica, incluindo '-'
int isAlphaNumericHyphen(const char *str);

// Função para verificar se uma string contém apenas dígitos
int isNumeric(const char *str);

// Função para verificar se uma string contém apenas caracteres alfanuméricos
int isAlphanumeric(const char *str);

// Função para verificar se uma string contém apenas caracteres alfabéticos
int isAlphabetic(const char *str);

// Função para adicionar voos na fila de espera
void adicionarVoo();

// Função para adicionar passageiros a um voo
void adicionarPassageiros(char idVoo[]);

// Função para listar as características do primeiro avião da fila
void listarPrimeiroAviao();

// Função para autorizar a decolagem do primeiro avião da fila
void autorizarDecolagem();

// Função para listar o número de aviões aguardando na fila de decolagem
void listarNumeroAvioesAguardando();

// Função para listar os dados de todos os aviões na fila de espera
void listarAvioesEspera();

// Função para listar os passageiros de um determinado voo em ordem alfabética
void listarPassageiros(char idVoo[]);

// Função auxiliar para listar os passageiros em ordem alfabética
void listarPassageirosEmOrdem(struct tree *passageiro);

// Função para inicializar a fila de voos
void inicializarFila() {
    voo = (struct queue *)malloc(sizeof(struct queue));
    voo->front = voo->rear = NULL;
}
//funçao para limpar a entrada
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int isAlphaNumericHyphen(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalnum(str[i]) && str[i] != ' ' && str[i] != '-') {
            return 0; // Não é alfanumérico, incluindo '-'
        }
    }
    return 1; // É alfanumérico, incluindo '-'
}


// Função para adicionar voos na fila de espera
void adicionarVoo() {
    char input[20]; // Tamanho arbitrário, ajuste conforme necessário
    struct node *novoVoo = (struct node *)malloc(sizeof(struct node));
    
    if (novoVoo == NULL) {
        printf("Erro: Falha na alocação de memória.\n");
        exit(EXIT_FAILURE);
    }
    // Obtenha o ID do voo
    system("clear");

    do {
        printf("\n--------------------------ADICINANDO VOO-----------------------------\n");
        printf("\nInforme o ID do Voo (exatamente 7 caracteres):\n ");
        scanf("%s", novoVoo->Id);

        // Verifique se a entrada tem exatamente 7 caracteres e é alfanumérica
        if (strlen(novoVoo->Id) != 7 || !isAlphanumeric(novoVoo->Id)) {
            system("clear");
            printf("\n------------------------------ERRO-----------------------------\n");
            printf("\n   ID do Voo deve ter exatamente 7 caracteres alfanuméricos!!!!\n ");
            printf("\n------------------------------ERRO-----------------------------\n");
            sleep(2);
        }

    } while (strlen(novoVoo->Id) != 7 || !isAlphanumeric(novoVoo->Id));

    // Converta para maiúsculas
    for (int i = 0; i < strlen(novoVoo->Id); i++) {
        novoVoo->Id[i] = toupper(novoVoo->Id[i]);
    }

    // Obtenha o Destino
    system("clear");
    do {
        printf("\n--------------------------ADICINANDO VOO-----------------------------\n");
        printf("\nInforme o Destino (exatamente 3 caracteres):\n ");
        scanf("%s", novoVoo->Destino);

        // Verifique se a entrada tem exatamente 3 caracteres e é alfabética
        if (strlen(novoVoo->Destino) != 3 || !isAlphabetic(novoVoo->Destino)) {
            system("clear");
            printf("\n------------------------------ERRO-----------------------------\n");
            printf("\n     Destino deve ter exatamente 3 caracteres alfabéticos!!!\n");
            printf("\n------------------------------ERRO-----------------------------\n");
            sleep(2);
        }

    } while (strlen(novoVoo->Destino) != 3 || !isAlphabetic(novoVoo->Destino));

    // Converta para maiúsculas
    for (int i = 0; i < strlen(novoVoo->Destino); i++) {
        novoVoo->Destino[i] = toupper(novoVoo->Destino[i]);
    }

    // Obtenha a Empresa
    system("clear");
    do {
        printf("\n-----------------------ADICINANDO VOO--------------------------\n");
        printf("\nInforme a Empresa:\n ");
        scanf("%s", novoVoo->Empresa);

        // Verifique se a entrada é alfabética
        if (!isAlphanumeric(novoVoo->Empresa)) {
            system("clear");
            printf("\n------------------------------ERRO-----------------------------\n");
            printf("\n     A Empresa deve conter apenas caracteres alfanumericos\n");
            printf("\n------------------------------ERRO-----------------------------\n");
            sleep(2);
        }

    } while (!isAlphanumeric(novoVoo->Empresa));

    for (int i = 0; i < strlen(novoVoo->Empresa); i++) {
        novoVoo->Empresa[i] = toupper(novoVoo->Empresa[i]);
    }


    // Obtenha o Modelo
    system("clear");
    do {
        printf("\n--------------------------ADICINANDO VOO-----------------------------\n");
        printf("\nInforme o Modelo:\n ");
    
    // Usar scanf para ler uma string
    if (scanf("%[^\n]", novoVoo->Modelo) != 1) {
        // Se a leitura falhar, limpar o buffer de entrada e informar o usuário
        printf("Erro na leitura. Por favor, tente novamente.\n");

        // Limpar o buffer de entrada
        while (getchar() != '\n');
        
        // Solicitar novamente o modelo
        continue;
    }

    // Verificar se a string contém apenas caracteres alfanuméricos, incluindo '-'
    if (!isAlphaNumericHyphen(novoVoo->Modelo)) {
        system("clear");
        printf("\n--------------------------------------ERRO-------------------------------------------\n");
        printf("\nO Modelo deve conter apenas caracteres alfanuméricos, incluindo '-'. Tente novamente: \n");
        printf("\n--------------------------------------------------------------------------------------\n");
        sleep(2);
    } else {
        // Se a entrada for válida, sair do loop
        break;
    }
} while (1);


    // Converta para maiúsculas
    for (int i = 0; i < strlen(novoVoo->Modelo); i++) {
        novoVoo->Modelo[i] = toupper(novoVoo->Modelo[i]);
    }

    // Obtenha o número de Passageiros
    system("clear");
    while (1) {
        printf("\n--------------------------ADICINANDO VOO-----------------------------\n");

        printf("\nInforme o número de Passageiros:\n ");
        if (scanf("%d", &(novoVoo->Np)) == 1) {
            // Se a leitura for bem-sucedida, saia do loop
            break;
        } else {
            // Se a leitura falhar, limpe o buffer de entrada e informe o usuário
            system("clear");
            printf("\n------------------------------ERRO-----------------------------\n");
            printf("\nEntrada inválida. Por favor, insira um número.\n");
            printf("\n------------------------------ERRO-----------------------------\n");
            sleep(1.3);

            // Limpar o buffer de entrada
            while (getchar() != '\n');
            
            // Solicitar novamente o número de Passageiros
        }
    }

    novoVoo->lp = NULL;
    novoVoo->prox = NULL;

    if (voo->rear == NULL) {
        voo->front = voo->rear = novoVoo;
    } else {
        voo->rear->prox = novoVoo;
        voo->rear = novoVoo;
    }
    system("clear");
    printf("---------------------------------------------\n");
    printf("        Voo adicionado com sucesso!\n");
    printf("---------------------------------------------\n");
    sleep(3);
}

int isNumeric(const char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i])) {
            return 0; // Não é numérico
        }
    }
    return 1; // É numérico
}

// Função para adicionar passageiros a um voo
void adicionarPassageiros(char idVoo[]) {
    struct node *vooAtual = voo->front;
    
    if (vooAtual == NULL) {
        system("clear");
        printf("\n---------------------------------------------------\n");
        printf("\n           Nenhum avião na fila de espera.\n");
        printf("\n---------------------------------------------------\n");
        sleep(3);
        return;
    }
     // Verificar se o ID do voo existe na fila
    while (vooAtual != NULL) {
        if (strcmp(vooAtual->Id, idVoo) == 0) {
            struct tree *novoPassageiro = (struct tree *)malloc(sizeof(struct tree));
            printf("Informe o nome do passageiro: ");
            scanf("%s", novoPassageiro->nome);

            if (vooAtual->lp == NULL) {
                vooAtual->lp = novoPassageiro;
            } else {
                struct tree *atual = vooAtual->lp;
                struct tree *anterior = NULL;

                while (atual != NULL) {
                    anterior = atual;
                    if (strcmp(novoPassageiro->nome, atual->nome) < 0) {
                        atual = atual->left;
                    } else {
                        atual = atual->right;
                    }
                }

                if (strcmp(novoPassageiro->nome, anterior->nome) < 0) {
                    anterior->left = novoPassageiro;
                } else {
                    anterior->right = novoPassageiro;
                }
            }
            system("clear");
            printf("\n---------------------------------------------------------\n");
            printf("\n           Passageiro adicionado com sucesso!\n");
            printf("\n---------------------------------------------------------\n");
            sleep(3);
            
            return;
        }

        vooAtual = vooAtual->prox;
    }
    system("clear");
        printf("\n---------------------------------------------------------\n");
        printf("\n               Nenhum avião encontrado.\n");
        printf("\n---------------------------------------------------------\n");
        sleep(3);
}


// Função para listar as características do primeiro avião da fila
void listarPrimeiroAviao() {

    system("clear");
    printf("---------------------------------------------\n");
    if (voo->front == NULL) {
        system("clear");
        printf("\n---------------------------------------------------\n");
        printf("\n           Nenhum avião na fila de espera.\n");
        printf("\n---------------------------------------------------\n");
        sleep(3);
        return;
    }

    struct node *primeiroVoo = voo->front;
    printf("ID do Voo: %s\n", primeiroVoo->Id);
    printf("Destino: %s\n", primeiroVoo->Destino);
    printf("Empresa: %s\n", primeiroVoo->Empresa);
    printf("Modelo: %s\n", primeiroVoo->Modelo);
    printf("Numero de Passageiros: %d\n", primeiroVoo->Np);
    printf("---------------------------------------------\n");
    sleep(3);
}

// Função para autorizar a decolagem do primeiro avião da fila
void autorizarDecolagem() {
    system("clear");
    if (voo->front == NULL) {
        system("clear");
        printf("\n---------------------------------------------------\n");
        printf("\n           Nenhum avião na fila de espera.\n");
        printf("\n---------------------------------------------------\n");
        sleep(3);
        return;
    }

    struct node *aviaoDecolagem = voo->front;
    voo->front = aviaoDecolagem->prox;
    free(aviaoDecolagem);
    printf("\n-------------------------------------------------\n");
    printf("\n             Decolagem autorizada!\n");
    printf("\n-------------------------------------------------\n");
    sleep(2);
    system("clear");
}

// Função para listar o número de aviões aguardando na fila de decolagem
void listarNumeroAvioesAguardando() {
    int count = 0;
    struct node *aviao = voo->front;

    while (aviao != NULL) {
        count++;
        aviao = aviao->prox;
    }
    system("clear");
    printf("\n---------------------------------------------------------\n");
    printf("\n   Numero de avioes aguardando na fila de decolagem: %d\n", count);
    printf("\n---------------------------------------------------------\n");
}

// Função para listar os dados de todos os aviões na fila de espera
void listarAvioesEspera() {
    system("clear");
    printf("------------------ INFORMAÇÕES DOS AVIÕES -------------------\n");
    printf("-------------------------------------------------------------\n");
    struct node *aviao = voo->front;

    if (aviao == NULL) {
        system("clear");
        printf("\n---------------------------------------------------------\n");
        printf("\n               Nenhum avião na fila de espera.\n");
        printf("\n---------------------------------------------------------\n");
        return;
    }

    while (aviao != NULL) {
        
        printf("ID do Voo: %s\n", aviao->Id);
        printf("Destino: %s\n", aviao->Destino);
        printf("Empresa: %s\n", aviao->Empresa);
        printf("Modelo: %s\n", aviao->Modelo);
        printf("Numero de Passageiros: %d\n", aviao->Np);
        printf("-------------------------------------------------------------\n");
        aviao = aviao->prox;
    }
    sleep(2);
}

// Função para listar os passageiros de um determinado voo em ordem alfabética
void listarPassageiros(char idVoo[]) {
    struct node *vooAtual = voo->front;
    system("clear");
    while (vooAtual != NULL) {
        if (strcmp(vooAtual->Id, idVoo) == 0) {
            struct tree *passageiro = vooAtual->lp;
            if (passageiro == NULL) {
                printf("----------------- LISTA DE PASSAGEIROS ------------------\n");
                printf("             Nenhum passageiro neste voo.\n");
                printf("---------------------------------------------------------\n");
                return;
            }
            printf("------------------LISTA DE PASSAGEIROS----------------\n");
            printf("\nPassageiros do Voo %s em ordem alfabetica:\n", idVoo);
            listarPassageirosEmOrdem(passageiro);
            return;
        }

        vooAtual = vooAtual->prox;
    }
    system("clear");
    printf("\n---------------------------------------------------------\n");
    printf("\n               Nenhum avião encontrado.\n");
    printf("\n---------------------------------------------------------\n");
    sleep(2);

}

// Função auxiliar para listar os passageiros em ordem alfabética
void listarPassageirosEmOrdem(struct tree *passageiro) {
    if (passageiro != NULL) {
        listarPassageirosEmOrdem(passageiro->left);
        printf("%s\n", passageiro->nome);
        listarPassageirosEmOrdem(passageiro->right);
    }
}

int isAlphanumeric(const char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (!isalnum(str[i])) {
            return 0; // Não é alfanumérico
        }
    }
    return 1; // É alfanumérico
}

int isAlphabetic(const char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (!isalpha(str[i])) {
            return 0; // Não é alfabético
        }
    }
    return 1; // É alfabético
}


int main() {
    system("clear");
    inicializarFila();
    char opcao[10];
    char idVoo[8];

    do {
        system("clear");
        system("clear");
        printf("---------------------------------------------------------\n");
        printf("           Menu de Controle de Pista de Decolagem\n");
        printf("---------------------------------------------------------\n");
        printf("1. Adicionar voo na fila de espera\n");
        printf("2. Adicionar passageiros a um voo\n");
        printf("3. Listar caracteristicas do primeiro avião na fila\n");
        printf("4. Autorizar decolagem do primeiro avião na fila\n");
        printf("5. Listar numero de avioes aguardando na fila\n");
        printf("6. Listar dados de todos os avioes na fila\n");
        printf("7. Listar passageiros de um voo\n");
        printf("8. Sair\n");
        printf("---------------------------------------------------------\n");
        printf("               Estrutura de Dados - UTFPR\n");
        printf("---------------------------------------------------------\n");
        printf("Escolha uma opcao: \n");

        // Leitura da opção como string
        fgets(opcao, sizeof(opcao), stdin);

        // Remover a quebra de linha
        opcao[strcspn(opcao, "\n")] = '\0';

        // Convertendo a string para inteiro
        long escolha = strtol(opcao, NULL, 10);

        switch (escolha) {
            case 1:
                adicionarVoo();
                system("clear");
                break;
            case 2:
                system("clear");
                do {
                    printf("\n--------------- ADICIONAR PASSAGEIROS A UM VOO ----------------\n");
                    printf("\nInforme o ID do voo:\n ");
                    scanf("%s", idVoo);
                    // Verificar se o ID do voo contém apenas caracteres alfanuméricos
                    if (!isAlphanumeric(idVoo)) {
                        // Se a entrada não for válida, limpar o buffer de entrada e informar o usuário
                        system("clear");
                        printf("\n------------------------------ ERRO --------------------------\n");
                        printf("\n  O ID do voo deve conter apenas caracteres alfanuméricos\n");
                        printf("\n-------------------------------------------------------------\n");
                        sleep(1.3);
                        // Limpar o buffer de entrada
                        while (getchar() != '\n');
                    }
            
                } while (!isAlphanumeric(idVoo));
            
                // Converter o ID do voo para maiúsculas
                for (int i = 0; idVoo[i] != '\0'; i++) {
                    idVoo[i] = toupper(idVoo[i]);
                }
                adicionarPassageiros(idVoo);
                system("clear");
                break;
            case 3:
                listarPrimeiroAviao();
                system("clear");
                break;
            case 4:
                autorizarDecolagem();
                system("clear");
                break;
            case 5:
                listarNumeroAvioesAguardando();
                sleep(3);
                system("clear");
                break;
            case 6:
                listarAvioesEspera();
                sleep(3);
                system("clear");
                break;
            case 7:
                system("clear");
                do {
                    printf("\n-----------------------LISTAR PASSAGEIROS---------------------------\n");
                    printf("\nInforme o ID do voo: \n");
                    scanf("%s", idVoo);
                    // Verificar se o ID do voo contém apenas caracteres alfanuméricos
                    if (!isAlphanumeric(idVoo)) {
                        // Se a entrada não for válida, limpar o buffer de entrada e informar o usuário
                        system("clear");
                        printf("\n------------------------------ERRO-------------------------\n");
                        printf("\n  O ID do voo deve conter apenas caracteres alfanuméricos\n");
                        printf("\n-----------------------------------------------------------\n");
                        sleep(1.3);
                        // Limpar o buffer de entrada
                        while (getchar() != '\n');
                    }
            
                } while (!isAlphanumeric(idVoo));
            
                // Converter o ID do voo para maiúsculas
                for (int i = 0; idVoo[i] != '\0'; i++) {
                    idVoo[i] = toupper(idVoo[i]);
                }

                // Agora você pode chamar a função listarPassageiros com o idVoo processado
                listarPassageiros(idVoo);
                sleep(3);
                break;
            case 8:
                system("clear");    
                printf("\n-----------------------------------------------\n");
                printf("\n           Encerrando o programa.\n");
                printf("\n-----------------------------------------------\n");
                sleep(3);
                break;
            case 0:
            system("clear"); 
                continue;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (atoi(opcao) != 8);

    return 0;
}
