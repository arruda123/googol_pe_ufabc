/****************************************
*     Projeto Googol - PE - 2018        *
*  Gabrielle Arruda  -  11201721761     *
*             Luigi Perillo             *
*           Vinicius Teixeira           *
*****************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1003

int sanitizeNumerao(char numerao[MAX_SIZE]);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 *  Todas as funcoes abaixo somente funcionam se o numerao estiver sanitizado, ou seja, *
 *  tenha passado pela funcao "sanitizeNumerao".                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

void imprimeNumerao(char numerao[MAX_SIZE], int tam);
int soma(char numerao1[MAX_SIZE], int n1, char numerao2[MAX_SIZE], int n2);
int subtracao(char numerao1[MAX_SIZE], int n1, char numerao2[MAX_SIZE], int n2);
void trocasinal(char numerao1[MAX_SIZE], int tam);



int main() {
    char numerao1[MAX_SIZE], numerao2[MAX_SIZE], operador = ' ';
    int tam1 = 0, tam2 = 0, tam3 = 0;
    
    while(operador != '0'){
        /* primeira leitura (numero ou fim) */
        scanf("%s", numerao1);
        /* verifica se numero ou fim para continuar*/
        if(numerao1[0] != 'F' && numerao1[1] != 'I' && numerao1[2] != 'M') {
            scanf("%s", numerao2);
            scanf(" %c", &operador);
        
            tam1 = sanitizeNumerao(numerao1);
            tam2 = sanitizeNumerao(numerao2);        
            switch(operador){
                case '+': tam3 = soma(numerao1, tam1, numerao2, tam2);
                          break;
                case '-': tam3 = subtracao(numerao1, tam1, numerao2, tam2);
                          break;
                default: printf("Operador invalido!");
            }
            
            imprimeNumerao(numerao1, tam3);
            
        } else {
            /* define operador como zero para encerrar aplicacao */
            operador = '0';
        }
    }

    return 0;
}

/* Sanitiza os numeros em ordem no menos significativo para o mais significativo
   >>preserva o sinal de negativo na frente do numerao<< 
   Recebe:
    char numerao: vetor de char corresponde ao numerao
   Retorna: 
    int size: tamanho do numerao sanitizado */
int sanitizeNumerao(char numerao[MAX_SIZE]) {
    char numerao_copy[MAX_SIZE];
    int i = 0, size = -1;
    
    /* encontra o tamanho do numerao */
    while(size == -1 && i < MAX_SIZE) {
        if(numerao[i] == '\0'){
           size = i;
           break;   
        }
        i++;
    }
    
    /* cria um espelho */
    for(i = 0; i < size; i++) {
        numerao_copy[i] = numerao[i];
    }
    
    /* reordena do menos significativo para o mais significativo */
    if(numerao[0] == '-') {
        /* mantem o menos para simbolizar o numero negativo */
        for(i = 1; i < size; i++){
            numerao[i] = numerao_copy[size - i];
        }
    } else {
        for(i = 0; i < size; i++){
            numerao[i] = numerao_copy[(size - 1) - i];
        }
    }
        
    return size;  
}

/* Imprime numerao sanitizado 
   Recebe:
    char numerao: vetor de char corresponde ao numerao a ser impresso
    int tam: inteiro correspondente ao tamanho do numerao
   Retorna: 
    nada    */
void imprimeNumerao(char numerao[MAX_SIZE], int tam) {
    int i;
    /* caso o numero negativo, imprime o sinal antes do numero */
    if(numerao[0] == '-'){
        printf("%c", numerao[0]);
        for(i = 0; i < tam; i++) {
           printf("%c", numerao[tam - i]);
        }
    }else {
        for(i = 0; i < tam; i++) {
            printf("%c", numerao[(tam - i) - 1]);
        }
    }

    printf("\n");
}

/*tranforma em negativo IMPLEMENTAR*/
void sinalnegativo(char numerao1[MAX_SIZE], int tam){
    int i;
    char aux;
    for(i = tam; i < 0; i--){
        aux = numerao1[i];
        numerao1[i+1] = aux;
    }
    numerao1[0] = '-';
}


/*
   Recebe: 
    char numerao1: vetor de char correspondente ao primeiro numero
    int n1: tamanho do vetor numerao1
    char numerao2: vetor de char corresponde ao segundo numero
    int n2: tamanho do vetor numerao2
   Retorna:
    int tam: novo tamanho do numerao1  */
int soma(char numerao1[MAX_SIZE], int tam1, char numerao2[MAX_SIZE], int tam2) {
    int i, tam = 0, calculated = 0, rest = 0;
    char cache;

    /* define o tamanho preliminar do array */
    tam = tam1 > tam2 ? tam1 : tam2;

    /* caso 1: verificar se os numeros são ambos positivos ou ambos negativos */
    if ((numerao1[0] != '-' && numerao2[0] != '-') || (numerao1[0] == '-' && numerao2[0] == '-')) {
        /* verificar se os dois numeros são negativos */
        if (numerao1[0] == '-' && numerao2[0] == '-') {
            i = 1;
        } else {
            i = 0;
        }
        /* percorre ambos os vetores somando e iterando o resto */
        while (i < tam) {
            calculated = rest;
            if (i < tam1) {
                calculated += (numerao1[i] - '0');    
            }
            if (i < tam2) {
                calculated += (numerao2[i] - '0');
            }
            if(calculated > 9) {
                calculated -= 10;
                rest = 1;
            } else {
                rest = 0;
            }
            numerao1[i] = '0' + calculated;
            i++;
        }
            
        /* verifica o resto para incluir na proxima casa */
        if(rest > 0) {
            tam++;
            numerao1[tam - 1] = '1';
        }
    }
    /* caso 2: o primeiro numero positivo e o segundo negativo */
    else if (numerao1[0] != '-' && numerao2[0] == '-') {
        /* Remover o sinal negativo do segundo numero */
        for (i = 0; i < (tam2 - 1); i++) {
            cache = numerao2[i + 1];
            numerao2[i + 1] = numerao2[i];
            numerao2[i] = cache;
        }
        tam2--;
        /* Enviar para a função subtracao */
        tam = subtracao(numerao1, tam1, numerao2, tam2);
    }
    /* caso 3: o primeiro numero negativo e o segundo positivo */
    else{
        /* Remover o sinal negativo do primeiro numero */
        for (i = 0; i < (tam1 - 1); i++) {
            cache = numerao1[i + 1];
            numerao1[i + 1] = numerao1[i];
            numerao1[i] = cache;
        }
        tam1--;
        /* Enviar para a função subtracao */
        tam = subtracao(numerao2, tam2, numerao1, tam1);
    }
    return tam;
}

/*
   Recebe: 
    char numerao1: vetor de char correspondente ao primeiro numero
    int n1: tamanho do vetor numerao1
    char numerao2: vetor de char corresponde ao segundo numero
    int n2: tamanho do vetor numerao2
   Retorna:
    int tam: novo tamanho do numerao1  */
int subtracao(char numerao1[MAX_SIZE], int tam1, char numerao2[MAX_SIZE], int tam2) {
    int i, j, tam = 0, maior = 1, calculated = 0;
    char cache;

    /* define o tamanho preliminar do array e indicar qual é o maior numero (em módulo) */
    if (tam1 > tam2) {
        tam = tam1;
        maior = 1;
    } else if (tam2 > tam1) {
        tam = tam2;
        maior = 2;
    } else {
        tam = tam1;
        /* Definir o maior entre os dois numeros comparando seus algarismos */
        for (i = (tam - 1); i >= 0; i--) {
            if (numerao1[i] > numerao2[i]) {
                maior = 1;
                break;
            } else if (numerao2[i] > numerao1[i]) {
                maior = 2;
                break;
            }
        }
    }

    /* caso 1: verificar se os numeros são ambos positivos */
    if (numerao1[0] != '-' && numerao2[0] != '-') {
        /* se o maior numero em modulo for o numerao1 */
        if (maior == 1) {
            /* percorre ambos os vetores subtraindo seus algarismos */
            for (i = 0; i < tam; i++) {
                calculated = (numerao1[i] - '0');
                if (i < tam2) {
                    calculated -= (numerao2[i] - '0');
                }
                /* caso o numero precise pegar uma unidade emprestada do casa vizinha */
                if (calculated < 0) {
                    j = i + 1;
                    while (j < tam) {
                        /* verificar se o algarismo é diferente de zero */
                        if (numerao1[j] != '0') {
                            numerao1[j] -= 1;
                            break;
                        /* se algarismo igual a zero procurar na casa seguinte*/
                        } else {
                            numerao1[j] += 10;
                            j++;
                        }
                    }
                    numerao1[i] += 10;
                    calculated = (numerao1[i] - '0');
                    calculated -= (numerao2[i] - '0');
                }
                numerao1[i] = '0' + calculated;
            }
        } /* se o maior numero em modulo for o numerao2 */
        else {
        /* percorre ambos os vetores subtraindo seus algarismos */
            for (i = 0; i < tam; i++) {
                calculated = (numerao2[i] - '0');
                if (i < tam1) {
                    calculated -= (numerao1[i] - '0');
                }
                /* caso o numero precise pegar uma unidade emprestada do casa vizinha */
                if (calculated < 0) {
                    j = i + 1;
                    while (j < tam) {
                        /* verificar se o algarismo é diferente de zero */
                        if (numerao2[j] != '0') {
                            numerao2[j] -= 1;
                            break;
                        /* se algarismo igual a zero procurar na casa seguinte*/
                        } else {
                            numerao2[j] += 10;
                            j++;
                        }
                    }
                    numerao2[i] += 10;
                    calculated = (numerao2[i] - '0');
                    calculated -= (numerao1[i] - '0');
                }
                numerao1[i] = '0' + calculated;
            }
            //sinalnegativo(numerao1, tam);
            //tam++;
        }
    /* caso 2: se o segundo número é negativo, ele se transforma em positivo e é enviado para soma */
    } else if (numerao1[0] != '-' && numerao2[0] == '-') {
        /* Remover o sinal negativo do segundo numero */
        for (i = 0; i < (tam2 - 1); i++) {
            cache = numerao2[i + 1];
            numerao2[i + 1] = numerao2[i];
            numerao2[i] = cache;
        }
        tam2--;
        /* Enviar para a função soma */
        tam = soma(numerao1, tam1, numerao2, tam2);
        return tam;
    }
    /* procurar e elimimnar zeros a esquerda da contagem do tamanho */
    for (i = (tam - 1); i >= 0; i--) {
        /* terminar laço caso encontre um numero diferente de zero */
        if (numerao1[i] != '0') {
            break;
        /* se o ultimo numero é igual a zero */
        } else if (i == 0) {
            numerao1[0] = '0';
        /* se extorem zeros a esquerda remover uma unidade do tamanho */
        } else {
            tam--;
        }
    }
    /* caso 3: primeiro número é negativo, segundo positivo */
    /*else if (numerao1[0] == '-' && numerao2[0] != '-') {
        
        
    }*/

    /* caso 4: Ambos negativos */
    /*else{
        
    }*/

    
    

    return tam;
}
