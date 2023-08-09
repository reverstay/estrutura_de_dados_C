#include<stdio.h>

/**** ponteiros sao variaveis que armazenam endereços de memoria de outras variaveis,
 *     para armazenar um endereço em um ponteiro:
 *      
 * definir: {tipo} *ponteiro_exemplo;
 * atribuir endereço : ponteiro_exemplo = &variavel;
 *
 * int *ponteiro; // Declaração de um ponteiro para um inteiro
 * float *outroPonteiro; // Declaração de um ponteiro para um float

 *   int variavel = 42;
 *   int *ponteiro;
 *  ponteiro = &variavel; // Atribui o endereço da variável ao ponteiro
 * para acessr a variavel e alterar seu valor agora é simples
 *  *ponteiro = 55;
 * 
 *  printf("%d", varivel);
 * 
 * outpu= 55
 *
 * 
****/



int main(){

    printf("Bem vindo a revisao de ponteiros em C\n");

    int variavel = 42;
    int *ponteiro;
    printf("%d\n", variavel);
    ponteiro = &variavel;
    *ponteiro = 55;
    printf("%d\n", variavel);
    int **novo;
    novo = &ponteiro;
    
    **novo = 66;
    printf("%d\n", variavel);
    return 0;
}