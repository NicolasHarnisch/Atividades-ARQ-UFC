/*
 * Somar duas listas de valores
 * Ex: 
 * Entrada:
 * 5
 * 1 2 3 4 5
 * 6 7 8 9 10
 * Saída:
 * 7 9 11 13 15
 * */

#include <stdio.h>

int main(){
	
	int n;
	
	scanf("%d", &n);
	
	int vetor1[n];
	int vetor2[n];
	
	for(int i = 0; i < n; i++){
		scanf("%d", &vetor1[i]);
	}
	
	for(int i = 0; i < n; i++){
		scanf("%d", &vetor2[i]);
	}
	
	int vetor3[n];
	
	for(int i = 0; i < n; i++){
		vetor3[i] = vetor1[i] + vetor2[i];
	}
	
	for(int i = 0; i < n; i++){
		printf("%d ", vetor3[i]);
	}
	printf("\n");
	
	return 0;
}
