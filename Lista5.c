#include <stdio.h>
#include <stdlib.h>

// Raphael Leite Diniz 2358549

struct clista {
    int info;
    struct clista *ant;
    struct clista *prox;
};

typedef struct clista CLista;

CLista *inserir(CLista *l, int v) {
    CLista *novo = (CLista*) malloc(sizeof(CLista));
    novo->info = v;
    if (l == NULL) {
        novo->ant = novo;
        novo->prox = novo;
        l = novo;
    } else {
        novo->ant = l->ant;
        novo->prox = l;
        l->ant->prox = novo;
        l->ant = novo;
        l = novo;
    }
    return l;
}

int imprimir(CLista *l) {
    if (l == NULL) {
        printf("Lista vazia!\n");
        return 0;
    } else {
        return l->info;
    }
}

CLista *remover(CLista *l) {
    if (l == NULL) {
        printf("Lista vazia!\n");
        return NULL;
    } else if (l->ant == l) {
        free(l);
        return NULL;
    } else {
        CLista *removido = l;
        l->ant->prox = l->prox;
        l->prox->ant = l->ant;
        l = l->prox;
        free(removido);
        return l;
    }
}

int main() {
    CLista *lista = NULL;
    int opcao, valor;

    do {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Inserir elemento na lista\n");
        printf("2 - Imprimir valor na cabeca da lista\n");
        printf("3 - Remover elemento da lista\n");
        printf("0 - Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor);
                lista = inserir(lista, valor);
                printf("Valor inserido com sucesso!\n");
                break;

            case 2:
                valor = imprimir(lista);
                if (valor != 0) {
                    printf("Valor na cabeca da lista: %d\n", valor);
                }
                break;

            case 3:
                lista = remover(lista);
                printf("Elemento removido com sucesso!\n");
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
