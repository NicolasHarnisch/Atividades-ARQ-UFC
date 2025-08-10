/*
 * Receber um vetor e um elemento a ser buscado
 * Retorna Sim se o elemento pertence ao vetor e Nao caso contrario
 * 
 * Ex1: 
 * Entrada:
 * 5
 * 3 5 2 4 1
 * 8
 * Nao
 * 
 * Ex2:
 * 6
 * 1 3 5 4 2 9
 * 2
 * Sim
 * */
 
#include <stdio.h>

int main(){
	
	int tamanho;
	
	scanf("%d", &tamanho);
	
	int vetor[tamanho];
	
	for(int i = 0; i < tamanho; i++){
		scanf("%d", &vetor[i]);
	}
	
	int elemento;
	scanf("%d", &elemento);
	
	int encontrei = 0;
	
	for(int i = 0; i < tamanho; i++){
		if(vetor[i] == elemento){
			encontrei = 1;
			break;
		}
	}
	
	if(encontrei == 1){
		printf("Sim\n");
	}else{
		printf("Nao\n");
	}
	
	return 0;
}




