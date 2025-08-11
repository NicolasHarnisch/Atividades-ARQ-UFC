#include <stdio.h>

/*
 * Recebe uma matriz e apresenta os elementos da mesma
 */

int main(){
	
	int matriz[3][4];
	
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 4; j++){
			printf("Posicao(%d, %d): ", i, j);
			scanf("%d", &matriz[i][j]);
		}
	}
	
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 4; j++){
			printf("%d\t", matriz[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}
