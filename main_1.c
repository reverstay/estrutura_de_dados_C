#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 30
#define MAX_EMAIL 35
#define MAX_TELEFONE 20
#define MAX_ANIVERSARIO 6

//Raphael Leite Diniz 2358549
//Mauricio Tuyuty Lopes de Carvalho 1987291
//Arthur Bernardes Schmidt 2129760

typedef struct Contato {
    char nome[MAX_NOME];
    char email[MAX_EMAIL];
    char telefone[MAX_TELEFONE];
    char aniversario[MAX_ANIVERSARIO];
    struct Contato* esquerda;
    struct Contato* direita;
} Contato;

typedef struct Agenda {
    Contato* raiz;
} Agenda;

void inicializar_agenda(Agenda* agenda) {
    agenda->raiz = NULL;
}

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
    novo_contato->esquerda = NULL;
    novo_contato->direita = NULL;
    return novo_contato;
}

void liberar_contatos_recursivo(Contato* contato) {
    if (contato != NULL) {
        liberar_contatos_recursivo(contato->esquerda);
        liberar_contatos_recursivo(contato->direita);
        free(contato);
    }
}

void liberar_agenda(Agenda* agenda) {
    liberar_contatos_recursivo(agenda->raiz);
    agenda->raiz = NULL;
}

Contato* adicionar_contato(Contato* raiz, Contato* novo_contato) {
    if (raiz == NULL) {
        return novo_contato;
    }
    if (strcmp(novo_contato->nome, raiz->nome) < 0) {
        raiz->esquerda = adicionar_contato(raiz->esquerda, novo_contato);
    } else {
        raiz->direita = adicionar_contato(raiz->direita, novo_contato);
    }
    return raiz;
}

void exibir_contatos(const Contato* raiz) {
    if (raiz == NULL) {
        printf("A agenda esta vazia.\n");
    } else {
        printf("Contatos na agenda:\n");
        exibir_contatos_recursivo(raiz);
    }
}

void exibir_contatos_recursivo(const Contato* contato) {
    if (contato != NULL) {
        exibir_contatos_recursivo(contato->esquerda);
        printf("Nome: %s\n", contato->nome);
        printf("E-mail: %s\n", contato->email);
        printf("Telefone: %s\n", contato->telefone);
        printf("Aniversario: %s\n", contato->aniversario);
        printf("--------------------\n");
        exibir_contatos_recursivo(contato->direita);
    }
}

Contato* buscar_contato_nome(const Contato* raiz, const char* nome) {
    if (raiz == NULL || strcmp(raiz->nome, nome) == 0) {
        return raiz;
    }
    if (strcmp(nome, raiz->nome) < 0) {
        return buscar_contato_nome(raiz->esquerda, nome);
    } else {
        return buscar_contato_nome(raiz->direita, nome);
    }
}

void exibir_contatos_email(const Contato* raiz) {
    if (raiz != NULL) {
        exibir_contatos_email(raiz->esquerda);
        printf("%s\t\t<%s>\n", raiz->nome, raiz->email);
        exibir_contatos_email(raiz->direita);
    }
}

void buscar_contato_mes_aniversario(const Contato* raiz, const char* mes) {
    if (raiz != NULL) {
        buscar_contato_mes_aniversario(raiz->esquerda, mes);
        int mes_aniversario = atoi(raiz->aniversario + 3);
        if (mes_aniversario == atoi(mes)) {
            printf("Nome: %s\n", raiz->nome);
            printf("E-mail: %s\n", raiz->email);
            printf("Telefone: %s\n", raiz->telefone);
            printf("Aniversario: %s\n", raiz->aniversario);
            printf("--------------------\n");
        }
        buscar_contato_mes_aniversario(raiz->direita, mes);
    }
}

Contato* buscar_menor_contato(Contato* raiz) {
    Contato* atual = raiz;
    while (atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

Contato* remover_contato(Contato* raiz, const char* nome) {
    if (raiz == NULL) {
        return raiz;
    }
    if (strcmp(nome, raiz->nome) < 0) {
        raiz->esquerda = remover_contato(raiz->esquerda, nome);
    } else if (strcmp(nome, raiz->nome) > 0) {
        raiz->direita = remover_contato(raiz->direita, nome);
    } else {
        if (raiz->esquerda == NULL) {
            Contato* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            Contato* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        Contato* menor_contato = buscar_menor_contato(raiz->direita);
        strcpy(raiz->nome, menor_contato->nome);
        strcpy(raiz->email, menor_contato->email);
        strcpy(raiz->telefone, menor_contato->telefone);
        strcpy(raiz->aniversario, menor_contato->aniversario);
        raiz->direita = remover_contato(raiz->direita, menor_contato->nome);
    }
    return raiz;
}

void exibir_menu_principal() {
    printf("\nMenu Principal\n");
    printf("1. Adicionar Contato\n");
    printf("2. Consultar Contatos\n");
    printf("3. Remover Contato\n");
    printf("4. Sair\n");
}

void exibir_menu_consulta() {
    printf("\nMenu de Consulta\n");
    printf("1. Consultar por Nome\n");
    printf("2. Consultar por Email\n");
    printf("3. Consultar por Mês de Aniversário\n");
    printf("4. Voltar ao Menu Principal\n");
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
                agenda.raiz = adicionar_contato(agenda.raiz, contato);
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
                    Contato* contato = buscar_contato_nome(agenda.raiz, nome);
                    if (contato != NULL) {
                        printf("Contato encontrado:\n");
                        printf("Nome: %s\n", contato->nome);
                        printf("E-mail: %s\n", contato->email);
                        printf("Telefone: %s\n", contato->telefone);
                        printf("Aniversario: %s\n", contato->aniversario);
                    } else {
                        printf("Contato nao encontrado.\n");
                    }
                }
                else if (strcmp(opcao, "2") == 0) {
                        printf("Contatos em ordem alfabetica:\n");
                        exibir_contatos_email(agenda.raiz);
                }

                else if (strcmp(opcao, "3") == 0) {
                    char mes[3];
                    printf("Mês de aniversario [mm]: ");
                    scanf(" %[^\n]s", mes);
                    printf("Contatos encontrados:\n");
                    buscar_contato_mes_aniversario(agenda.raiz, mes);
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
            agenda.raiz = remover_contato(agenda.raiz, nome);
        }
        else if (strcmp(opcao, "4") == 0) {
            printf("Saindo...\n");
            liberar_agenda(&agenda);
            break;
        }
        else {
            printf("Opcao invalida. Tente novamente.\n");
        }
    }

    return 0;
}
