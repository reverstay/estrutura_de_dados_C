#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 30
#define MAX_EMAIL 35
#define MAX_TELEFONE 20
#define MAX_ANIVERSARIO 6

typedef struct Contato {
    char nome[MAX_NOME];
    char email[MAX_EMAIL];
    char telefone[MAX_TELEFONE];
    char aniversario[MAX_ANIVERSARIO];
    struct Contato* proximo;
} Contato;

Contato* criar_contato(const char* nome, const char* email, const char* telefone, const char* aniversario) {
    Contato* novo_contato = (Contato*)malloc(sizeof(Contato));
    if (novo_contato == NULL) {
        printf("Erro ao alocar memoria para o novo contato.\n");
        return NULL;
    }
    strcpy(novo_contato->nome, nome);
    strcpy(novo_contato->email, email);
    strcpy(novo_contato->telefone, telefone);
    strcpy(novo_contato->aniversario, aniversario);
    novo_contato->proximo = NULL;
    return novo_contato;
}

void liberar_contato(Contato* contato) {
    free(contato);
}

typedef struct Agenda {
    Contato* head;
} Agenda;

void inicializar_agenda(Agenda* agenda) {
    agenda->head = NULL;
}

void adicionar_contato(Agenda* agenda, Contato* contato) {
    if (agenda->head == NULL) {
        agenda->head = contato;
    }
    else if (strcmp(contato->nome, agenda->head->nome) < 0) {
        contato->proximo = agenda->head;
        agenda->head = contato;
    }
    else {
        Contato* atual = agenda->head;
        while (atual->proximo && strcmp(contato->nome, atual->proximo->nome) > 0) {
            atual = atual->proximo;
        }
        contato->proximo = atual->proximo;
        atual->proximo = contato;
    }
}

void exibir_contatos(const Agenda* agenda) {
    if (agenda->head == NULL) {
        printf("A agenda esta vazia.\n");
    }
    else {
        Contato* atual = agenda->head;
        printf("Contatos na agenda:\n");
        while (atual) {
            printf("Nome: %s\n", atual->nome);
            printf("E-mail: %s\n", atual->email);
            printf("Telefone: %s\n", atual->telefone);
            printf("Aniversario: %s\n", atual->aniversario);
            printf("--------------------\n");
            atual = atual->proximo;
        }
    }
}

void remover_contato(Agenda* agenda, const char* nome) {
    if (agenda->head == NULL) {
        printf("A agenda esta vazia.\n");
    }
    else if (strcmp(agenda->head->nome, nome) == 0) {
        Contato* removido = agenda->head;
        agenda->head = agenda->head->proximo;
        liberar_contato(removido);
        printf("Contato removido.\n");
    }
    else {
        Contato* atual = agenda->head;
        Contato* anterior = NULL;
        while (atual && strcmp(atual->nome, nome) != 0) {
            anterior = atual;
            atual = atual->proximo;
        }
        if (atual) {
            anterior->proximo = atual->proximo;
            liberar_contato(atual);
            printf("Contato removido.\n");
        }
        else {
            printf("Contato nao encontrado na agenda.\n");
        }
    }
}

void exibir_menu_principal() {
    printf("Menu Principal:\n");
    printf("1. Cadastro\n");
    printf("2. Consulta\n");
    printf("3. Remocao\n");
    printf("4. Sair\n");
}

void exibir_menu_consulta() {
    printf("\nMenu de Consulta:\n");
    printf("1. Buscar por nome (ordem alfabetica)\n");
    printf("2. Buscar por email (formato: nome <email>)\n");
    printf("3. Buscar por mes de aniversário\n");
    printf("4. Voltar ao Menu Principal\n");
}

void consultar_por_nome(const Agenda* agenda, const char* nome_busca) {
    if (agenda->head == NULL) {
        printf("A agenda esta vazia.\n");
        return;
    }

    // Verificar se há contatos com o nome de busca
    int encontrou = 0;
    Contato* atual = agenda->head;
    while (atual) {
        if (strcmp(atual->nome, nome_busca) == 0) {
            encontrou = 1;
            break;
        }
        atual = atual->proximo;
    }

    if (!encontrou) {
        printf("Nenhum contato encontrado com o nome '%s'.\n", nome_busca);
        return;
    }

    // Exibir informações dos contatos com o nome correspondente
    printf("Contatos encontrados com o nome '%s':\n", nome_busca);
    atual = agenda->head;
    while (atual) {
        if (strcmp(atual->nome, nome_busca) == 0) {
            printf("Nome: %s\n", atual->nome);
            printf("Email: %s\n", atual->email);
            printf("Telefone: %s\n", atual->telefone);
            printf("Aniversario: %s\n", atual->aniversario);
            printf("--------------------\n");
        }
        atual = atual->proximo;
    }
}




void consultar_por_email(const Agenda* agenda) {
    if (agenda->head == NULL) {
        printf("A agenda está vazia.\n");
        return;
    }

    // Contar o número de contatos na agenda
    int numContatos = 0;
    Contato* atual = agenda->head;
    while (atual) {
        numContatos++;
        atual = atual->proximo;
    }

    // Criar um array para armazenar os nomes dos contatos e os emails correspondentes
    char nomes[numContatos][MAX_NOME];
    char emails[numContatos][MAX_EMAIL];

    // Copiar os nomes e emails dos contatos para os arrays
    atual = agenda->head;
    int i = 0;
    while (atual) {
        strcpy(nomes[i], atual->nome);
        strcpy(emails[i], atual->email);
        atual = atual->proximo;
        i++;
    }

    // Ordenar os nomes e emails em ordem alfabética usando o algoritmo Bubble Sort
    for (int j = 0; j < numContatos - 1; j++) {
        for (int k = 0; k < numContatos - j - 1; k++) {
            if (strcmp(nomes[k], nomes[k + 1]) > 0) {
                char tempNome[MAX_NOME];
                char tempEmail[MAX_EMAIL];
                strcpy(tempNome, nomes[k]);
                strcpy(tempEmail, emails[k]);
                strcpy(nomes[k], nomes[k + 1]);
                strcpy(emails[k], emails[k + 1]);
                strcpy(nomes[k + 1], tempNome);
                strcpy(emails[k + 1], tempEmail);
            }
        }
    }

    // Exibir os nomes e emails em ordem alfabética
    printf("Contatos por email:\n");
    for (int j = 0; j < numContatos; j++) {
        printf("%s\t<%s>\n", nomes[j], emails[j]);
    }
}


void consultar_por_mes_aniversario(const Agenda* agenda) {
    char mes[MAX_ANIVERSARIO];
    printf("Digite o mes do aniversario a ser consultado: ");
    scanf(" %[^\n]s", mes);

    Contato* atual = agenda->head;
    int encontrado = 0;

    while (atual) {
        if (strncmp(atual->aniversario + 3, mes, 2) == 0) {
            printf("Contato encontrado:\n");
            printf("Nome: %s\n", atual->nome);
            printf("E-mail: %s\n", atual->email);
            printf("Telefone: %s\n", atual->telefone);
            printf("Aniversario: %s\n", atual->aniversario);
            printf("--------------------\n");
            encontrado = 1;
        }
        atual = atual->proximo;
    }

    if (!encontrado) {
        printf("Nenhum contato encontrado com o mes de aniversario especificado.\n");
    }
}

void formatar_telefone(char* telefone) {
    while (1) {
        // Remover caracteres não numéricos do telefone
        int tamanho = strlen(telefone);
        int i, j = 0;
        char telefone_formatado[MAX_TELEFONE];
        for (i = 0; i < tamanho; i++) {
            if (isdigit(telefone[i])) {
                telefone_formatado[j++] = telefone[i];
            }
        }
        telefone_formatado[j] = '\0';

        // Verificar o tamanho do número de telefone e formatar adequadamente
        tamanho = strlen(telefone_formatado);
        if (tamanho == 11) {
            sprintf(telefone, "(%c%c) %c%c%c%c%c-%c%c%c%c", telefone_formatado[0], telefone_formatado[1],
                    telefone_formatado[2], telefone_formatado[3], telefone_formatado[4], telefone_formatado[5],
                    telefone_formatado[6], telefone_formatado[7], telefone_formatado[8], telefone_formatado[9],
                    telefone_formatado[10]);
            break; // Saia do loop se o telefone for válido
        } else {
            printf("Numero de telefone invalido. Utilize o formato DDD + Numero (11 digitos).\n");
            printf("Digite o telefone novamente: ");
            scanf(" %[^\n]s", telefone);
        }
    }
}



int main() {
    Agenda agenda;
    inicializar_agenda(&agenda);

    char opcao[2];
    while (1) {
        exibir_menu_principal();
        printf("Escolha uma opcao: ");
        scanf("%1s", opcao);

        if (strcmp(opcao, "1") == 0) {
            char nome[MAX_NOME];
            char email[MAX_EMAIL];
            char telefone[MAX_TELEFONE];
            char aniversario[MAX_ANIVERSARIO];
            printf("Nome: ");
            scanf(" %[^\n]s", nome);
            printf("E-mail: ");
            scanf(" %[^\n]s", email);
            printf("Telefone: ");
            scanf(" %[^\n]s", telefone);
            formatar_telefone(telefone);
            printf("Aniversario [dd/mm]: ");
            scanf(" %[^\n]s", aniversario);
            Contato* contato = criar_contato(nome, email, telefone, aniversario);
            if (contato != NULL) {
                adicionar_contato(&agenda, contato);
                printf("Contato adicionado com sucesso.\n");
            }
        }
        else if (strcmp(opcao, "2") == 0) {
            while (1) {
                exibir_menu_consulta();
                printf("Escolha uma opcao: ");
                scanf("%1s", opcao);

                if (strcmp(opcao, "1") == 0) {
                    char nome[MAX_NOME];
                    printf("Nome: ");
                    scanf(" %[^\n]s", nome);
                    consultar_por_nome(&agenda, nome);
                }
                else if (strcmp(opcao, "2") == 0) {
                    consultar_por_email(&agenda);
                }
                else if (strcmp(opcao, "3") == 0) {
                    consultar_por_mes_aniversario(&agenda);
                }
                else if (strcmp(opcao, "4") == 0) {
                    break;
                }
                else {
                    printf("Opcao invalida. Tente novamente.\n");
                }
            }
        }
        else if (strcmp(opcao, "3") == 0) {
            char nome[MAX_NOME];
            printf("Nome do contato a ser removido: ");
            scanf(" %[^\n]s", nome);
            remover_contato(&agenda, nome);
        }
        else if (strcmp(opcao, "4") == 0) {
            printf("Saindo...\n");
            break;
        }
        else {
            printf("Opcao invalida. Tente novamente.\n");
        }
    }

    return 0;
}

