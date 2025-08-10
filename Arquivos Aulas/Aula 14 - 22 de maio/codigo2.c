/*
 * Receber um vetor e retornar a soma e o produto dos elementos
 * Ex: 
 * Entrada:
 * 4
 * 2 3 1 7
 * Saída:
 * Soma: 13
 * Produto: 42
 * */

#include <stdio.h>

int main(){
	
	int tamanho;
	
	scanf("%d", &tamanho);
	
	float vetor[tamanho];
	
	for(int i = 0; i < tamanho; i++){
		scanf("%f", &vetor[i]);
	}
	
	float soma = 0, produto = 1;
	
	for(int i = 0; i < tamanho; i++){
		soma = soma + vetor[i];
		produto = produto * vetor[i];
	}
	
	printf("Soma: %f\n", soma);
	printf("Produto: %f\n", produto);
	
	return 0;
}
