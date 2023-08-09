#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Raphael Leite Diniz a2358549

typedef struct {
  char IdVoo[50];
  char Destino[50];
  char EmpAerea[50];
  char ModAviao[50];
  int NumPas;
} Aviao;

typedef struct no {
  Aviao a;
  struct no *proximo;
} No;

typedef struct {
  No *prim;
  No *fim;
  int tam;
} Fila;

void criar_fila(Fila *fila) {
  fila->prim = NULL;
  fila->fim = NULL;
  fila->tam = 0;
}

void imprimir_aviao(Aviao a) {
  printf("ID do Voo: %s\n", a.IdVoo);
  printf("Destino do Voo: %s\n", a.Destino);
  printf("Empresa Aerea: %s\n", a.EmpAerea);
  printf("Modelo da Aeronave: %s\n", a.ModAviao);
  printf("Numero de passageiros: %d\n", a.NumPas);
}

Aviao ler_Aviao() {
  Aviao a;
  printf("\nID do Voo: ");
  fgets(a.IdVoo, 49, stdin);
  printf("\nDestino do Voo: ");
  fgets(a.Destino, 49, stdin);
  printf("\nEmpresa Aerea:");
  fgets(a.EmpAerea, 49, stdin);
  printf("\nModelo da Aeronave: ");
  fgets(a.ModAviao, 49, stdin);
  printf("\nNumero de passageiros: ");
  scanf("%d", &a.NumPas);
  return a;
}

void inserir_na_fila(Fila *fila, Aviao aviao) {
  No *aux, *novo = malloc(sizeof(No));
  if (novo) {
    novo->a = aviao;
    novo->proximo = NULL;
    if (fila->prim == NULL) {
      fila->prim = novo;
      fila->fim = novo;
    } else {
      fila->fim->proximo = novo;
      fila->fim = novo;
    }
    fila->tam++;
  } else
    printf("\nErro ao alocar memoria.\n");
}

No *remover_da_fila(Fila *fila) {
  No *remover = NULL;

  if (fila->prim) {
    remover = fila->prim;
    fila->prim = remover->proximo;
    fila->tam--;
  } else
    printf("\nFila Vazia.\n");
  return remover;
}

void imprimirFila(Fila *fila) {
  No *aux = fila->prim;
  printf("\t----------Inicio Fila----------\n");
  while (aux) {
    imprimir_aviao(aux->a);
    aux = aux->proximo;
    if (fila)
      printf("------------------\n");
  }
  printf("\t----------Fim da Fila---------\n");
}

void imprimirPrimeiro(Fila *fila) {
  No *aux = fila->prim;
  printf("\t----------Primeiro da Fila----------\n");
  while (aux) {
    imprimir_aviao(aux->a);
    break;
  }
  printf("\t-------------------\n");
}

void imprimirUltimo(Fila *fila) {
  printf("\t----------Ultimo da Fila----------\n");
  No *aux = fila->fim;
  while (aux) {
    imprimir_aviao(aux->a);
    break;
  }
  printf("\t-------------------\n");
}

int main() {
  No *r;
  Fila fila;
  int opcao;
  Aviao a;
  criar_fila(&fila);
  do {
    printf("\t0 - Sair\n\t1 - Adicionar aviao a lista de espera\n\t2 - Liberar aviao para decolagem\n\t3 - "
           "Lista de avioes na fila de espera\n\t4 - Primeiro aviao na fila de espera\n\t5 - Ultimo aviao na "
           "fila de espera\n\t6 - Numero de avioes na fila de espera\n");
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
    case 1:
      a = ler_Aviao();
      inserir_na_fila(&fila, a);
      break;
    case 2:
      r = remover_da_fila(&fila);
      if (r) {
        imprimir_aviao(r->a);
        free(r);
      }
      break;
    case 3:
      imprimirFila(&fila);
      break;
    case 4:
      imprimirPrimeiro(&fila);
      break;
    case 5:
      imprimirUltimo(&fila);
      break;
    case 6:
      printf("\nAvioes na fila de espera: %d\n", fila.tam);
      break;
    default:
      if (opcao != 0)
        printf("\nOpcao Invalida\n");
    }

  } while (opcao != 0);
  return 0;
}
