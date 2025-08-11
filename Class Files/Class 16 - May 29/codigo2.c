#include <stdio.h>

/*
 * Recebe uma matriz e determina o maior elemento de cada coluna
 */

int main(){
	
	int n, m;
	
	printf("Digite o numero de linhas: ");
	scanf("%d", &n);
	printf("Digite o numero de colunas: ");
	scanf("%d", &m);
	
	int matriz[n][m];
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			printf("m[%d][%d] = ", i, j);
			scanf("%d", &matriz[i][j]);
		}
	}
	
	for(int j = 0; j < m; j++){
		int maior = matriz[0][j];
		for(int i = 1; i < n; i++){
			if(matriz[i][j] > maior){
				maior = matriz[i][j];
			}
		}
		printf("Maior Elemento da coluna %d: %d\n", j, maior);
	}
	
	
	
	return 0;
}
