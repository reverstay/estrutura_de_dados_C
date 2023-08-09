#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Raphael Leite Diniz 2358549

struct lista {
    char nome[40];
    struct lista *prev;
    struct lista *next;
};
typedef struct lista Lista;

void inserir(Lista **inicio, char *nome) {
    Lista *novo = (Lista*) malloc(sizeof(Lista));
    if(novo == NULL) {
        printf("Erro: nao foi possivel alocar memoria\n");
        return;
    }
    strcpy(novo->nome, nome);
    novo->prev = NULL;
    novo->next = *inicio;
    if(*inicio != NULL) {
        (*inicio)->prev = novo;
    }
    *inicio = novo;
    printf("Nome %s inserido com sucesso\n", nome);
}

void retirar(Lista **inicio, char *nome) {
    Lista *atual = *inicio;
    while(atual != NULL) {
        if(strcmp(atual->nome, nome) == 0) {
            if(atual->prev == NULL) {
                *inicio = atual->next;
            } else {
                atual->prev->next = atual->next;
            }
            if(atual->next != NULL) {
                atual->next->prev = atual->prev;
            }
            free(atual);
            printf("Nome %s retirado com sucesso\n", nome);
            return;
        }
        atual = atual->next;
    }
    printf("Nome %s nao encontrado\n", nome);
}

void imprimir(Lista *inicio) {
    Lista *atual = inicio;
    while(atual != NULL) {
        printf("%s\n", atual->nome);
        atual = atual->next;
    }
}

void buscar(Lista *inicio, char *nome) {
    Lista *atual = inicio;
    while(atual != NULL) {
        if(strcmp(atual->nome, nome) == 0) {
            printf("Nome %s encontrado\n", nome);
            return;
        }
        atual = atual->next;
    }
    printf("Nome %s nao encontrado\n", nome);
}

void navegar(Lista *ptr) {
    Lista *atual = ptr;
    char opcao;
    do {
        printf("Nome atual: %s\n", atual->nome);
        printf("Escolha uma opcao:\n");
        printf("< - nome anterior\n");
        printf("> - nome seguinte\n");
        printf("q - sair\n");
        scanf(" %c", &opcao);
        switch(tolower(opcao)) {
            case '<':
                if(atual->prev == NULL) {
                    printf("Inicio da lista\n");
                } else {
                    atual = atual->prev;
                }
                break;
            case '>':
                if(atual->next == NULL) {
                    printf("Fim da lista\n");
                } else {
                    atual = atual->next;
                }
                break;
            case 'q':
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida\n");
                break;
        }
    } while(tolower(opcao) != 'q');
}

void menu() {
    Lista *inicio = NULL;
    char opcao, nome[40];
    do {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Inserir nome\n");
        printf("2 - Retirar nome\n");
        printf("3 - Imprimir nomes\n");
        printf("4 - Buscar nome\n");
        printf("5 - Navegar na lista\n");
        printf("6 - Sair\n");
        scanf(" %c", &opcao);
        switch(opcao) {
          case '1':
            printf("Digite o nome:\n ");
            scanf("%s", nome);
            inserir(&inicio, nome);
            break;
          case '2':
            printf("Digite o nome:\n ");
            scanf("%s", nome);
            retirar(&inicio, nome);
            break;
          case '3':
            printf("Lista de nomes:\n");
            imprimir(inicio);
            break;
          case '4':
            printf("Digite o nome:\n ");
            scanf("%s", nome);
            buscar(inicio, nome);
            break;
          case '5':
            if(inicio == NULL) {
            printf("Lista vazia\n");
            } else {
            navegar(inicio);
            }
            break;
          case '6':
            printf("Saindo...\n");
            break;
          default:
            printf("Opcao invalida\n");
            break;
          }
        } while(opcao != '6');
}

int main() {
  menu();
  return 0;
}
