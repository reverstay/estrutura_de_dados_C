#include <stdio.h>
#include <stdlib.h>

// Raphael Leite Diniz 2358549
// Questão para extra da prova

struct fila{
    int num;
    struct fila *next;
};
typedef struct fila Fila;

Fila *inicio = NULL;
Fila *fim = NULL;

int size(){
    int cont = 0;
    Fila *atual = inicio;
    while(atual != NULL){
        cont++;
        atual = atual->next;
    }
    return cont;
}

void enqueue(int num){
    Fila *novo = (Fila*) malloc(sizeof(Fila));
    novo->num = num;
    novo->next = NULL;
    if(inicio == NULL){
        inicio = novo;
        fim = novo;
    } else {
        fim->next = novo;
        fim = novo;
    }
}

int dequeue(){
    if(inicio == NULL){
        printf("Fila vazia\n");
        return -1;
    }
    Fila *removido = inicio;
    int num = removido->num;
    inicio = inicio->next;
    if(inicio == NULL){
        fim = NULL;
    }
    free(removido);
    return num;
}

int maisDez(){
    if(size() > 10){
        return 1;
    } else {
        return 0;
    }
}

void imprimeFila(){
    Fila *atual = inicio;
    while(atual != NULL){
        printf("%d ", atual->num);
        atual = atual->next;
    }
    printf("\n");
}

int main(){
    int opcao, num;
    do {
        printf("\n");
        printf("Escolha uma opcao:\n");
        printf("1 - Inserir elemento\n");
        printf("2 - Retirar elemento\n");
        printf("3 - Imprimir fila\n");
        printf("4 - Verificar tamanho da fila\n");
        printf("5 - Verificar se a fila tem mais de 10 elementos\n");
        printf("0 - Sair\n");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &num);
                enqueue(num);
                break;
            case 2:
                num = dequeue();
                if(num != -1){
                    printf("Elemento removido: %d\n", num);
                }
                break;
            case 3:
                printf("Fila: ");
                imprimeFila();
                break;
            case 4:
                printf("Tamanho da fila: %d\n", size());
                break;
            case 5:
                if(maisDez()){
                    printf("A fila tem mais de 10 elementos\n");
                } else {
                    printf("A fila nao tem mais de 10 elementos\n");
                }
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida\n");
                break;
        }
    } while(opcao != 0);

    return 0;
}
