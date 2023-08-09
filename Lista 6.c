#include <stdio.h>
#include <stdlib.h>

//Raphael Leite Diniz 2358549

typedef struct no{
    int dado;
    struct no *left, *right;
} No;

typedef struct {
    No *raiz;
    int tam;
} ArvB;

No* inserir(No *raiz, int valor){
    if(raiz == NULL){
        No *novo = (No*)malloc(sizeof(No));
        novo->dado = valor;
        novo->left = NULL;
        novo->right = NULL;
        return novo;
    }
    else{
        if(valor < raiz->dado)
            raiz->left = inserir(raiz->left, valor);
        if (valor > raiz->dado)
            raiz->right = inserir(raiz->right, valor);
        return raiz;
    }
}

int tamanho(No *raiz){
    if(raiz == NULL)
        return 0;
    else
        return 1 + tamanho(raiz->left) + tamanho(raiz->right);
}

void printArv(No *raiz){
    if(raiz != NULL){
        printArv(raiz->left);
        printf("%d ", raiz->dado);
        printArv(raiz->right);
    }
}

int encontrarMaiorValor(No *raiz) {
    if (raiz == NULL)
        return -1;  // Árvore vazia

    while (raiz->right != NULL)
        raiz = raiz->right;

    return raiz->dado;
}

int encontrarMenorValor(No *raiz) {
    if (raiz == NULL)
        return -1;  // Árvore vazia

    while (raiz->left != NULL)
        raiz = raiz->left;

    return raiz->dado;
}

int encontrarValorRaiz(No *raiz) {
    if (raiz != NULL)
        return raiz->dado;
    else
        return -1;  // Árvore vazia
}

int main(){
    int op, valor;
    ArvB arv;
    arv.raiz = NULL;
    No *raiz = NULL;
    do{
        printf("\n0 - Sair\n1 - Inserir\n2 - Imprimir\n3 - Tamanho da arvore\n4 - Maior valor da arvore\n5 - Menor valor da arvore\n6 - Valor na raiz da arvore\n");
        scanf("%d", &op);

        switch(op){
        case 0:
            printf("Saindo...\n");
            break;
        case 1:
            printf("Digite um valor: ");
            scanf("%d", &valor);
            raiz = inserir(raiz, valor);
            break;
        case 2:
            printf("\nImpressao da arvore binaria\n");
            printArv(raiz);
            printf("\n");
            break;
        case 3:
             printf("\nTamanho: %d\n", tamanho(raiz));
             break;
        case 4:
            printf("\nMaior valor: %d\n", encontrarMaiorValor(raiz));
            break;
        case 5:
            printf("Menor valor: %d\n", encontrarMenorValor(raiz));
            break;
        case 6:
            printf("Valor da raiz: %d\n", encontrarValorRaiz(raiz));
            break;
        default:
            printf("\nOpcao Invalida\n");
        }
    } while(op != 0);
}
