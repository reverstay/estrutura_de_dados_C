#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Raphael Leite Diniz a2358549

typedef struct no{
  int valor;
  struct no *proximo;
} No;

typedef struct {
  No *inicio;
  int tam;
}Lista;

void criar_lista(Lista *lista) {
  lista->inicio = NULL;
  lista->tam = 0;
}

void inserir_no_inicio(Lista *lista,int num){
  No *novo = malloc(sizeof(No));

  if (novo){
    novo->valor = num;
    novo->proximo = lista->inicio;
    lista->inicio = novo;
    lista->tam++;
  }
  else  
    printf("\nErro ao alocar memoria\n");
}

void inserir_no_fim(Lista *lista,int num){
  No *aux, *novo = malloc(sizeof(No));

  if(novo){
    novo->valor = num;
    novo->proximo = NULL;

    if (lista->inicio == NULL){
      lista->inicio = novo;
    }
    else{
      aux = lista->inicio;
      while(aux->proximo)
        aux = aux->proximo;
      aux->proximo = novo;
    } 
    lista->tam++;  
  }
  else
    printf("\nErro ao alocar memoria\n");
    }

void inserir_no_meio(Lista *lista,int num, int ant){
  No *aux, *novo = malloc(sizeof(No));
  
  if(novo){
    novo->valor = num;

    if(lista->inicio == NULL){
      novo->proximo = NULL;
      lista->inicio = novo;  
    }
    else{
      aux = lista->inicio;
      while(aux->valor != ant && aux->proximo)
        aux = aux->proximo;
      novo->proximo = aux->proximo;
      aux->proximo = novo;
    }
    lista->tam++;  
  }
  else
    printf("\nErro ao alocar memoria\n");
}

void imprimir(Lista lista){
  No *no = lista.inicio;
  printf("\n\tLista: tam = %d\n", lista.tam);
  while(no){
    printf("%d\n", no->valor);
    no = no->proximo;
  }
  printf("\n\n");
}

void inserir_ordenado(Lista *lista, int num){
  No *aux, *novo = malloc(sizeof(No));

  if (novo){
    novo->valor = num;
    if(lista->inicio == NULL){
      novo->proximo = NULL;
      lista->inicio = novo;
    }
    else if(novo->valor < lista->inicio->valor){
      novo->proximo = lista->inicio;
      lista->inicio = novo;
    }
    else{
      aux = lista->inicio;
      while(aux->proximo && novo->valor > aux->proximo->valor)
        aux = aux->proximo;
      novo->proximo = aux->proximo;
      aux->proximo = novo;
    }
    lista->tam++;
  }
  else
    printf("\nErro ao alocar memoria\n");
}

int main() {
  int opcao, valor, anterior;
  Lista lista;
  criar_lista(&lista);

  do {
    printf("\n\t 0 - Sair\n\t 1 - Inserir no inicio\n\t 2 - Inserir no final\n\t 3 - Inserir no meio\n\t 4 - Inserir em ordem crescente\n\t 5 - Imprimir lista\n");
    scanf("%d", &opcao);

    switch(opcao){
      case 1:
        printf("Digite um valor: ");
        scanf("%d", &valor);
        inserir_no_inicio(&lista, valor);
        break;
      case 2:
        printf("Digite um valor: ");
        scanf("%d", &valor);
        inserir_no_fim(&lista, valor);
        break;
      case 3:
        printf("Digite um valor: ");
        scanf("%d", &valor);
        printf("Digite um valor de referencia: ");
        scanf("%d", &anterior);
        inserir_no_meio(&lista, valor, anterior);
        break;
      case 4:
        printf("Digite um valor: ");
        scanf("%d", &valor);
        inserir_ordenado(&lista, valor);
        break;
      case 5:
        imprimir(lista);
        break;
      default:
        if (opcao != 0);
          printf("\nOpcao invalida\n");
    }
 }while (opcao != 0);

 return 0;
}
