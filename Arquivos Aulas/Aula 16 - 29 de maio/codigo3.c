#include <stdio.h>

/*
 * Recebe duas matrizes n x m: M1 e M2
 * Determina M1^T (matriz transposta de M1) 
 * e a matriz M1 + M2 (matriz soma das matrizes M1 e M2)
 */

int main(){
	
	int n, m;
	
	printf("Digite o numero de linhas: ");
	scanf("%d", &n);
	printf("Digite o numero de colunas: ");
	scanf("%d", &m);
	
	int M1[n][m];
	int M2[n][m];
	
	int T[m][n];
	int S[n][m];
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			printf("M1[%d][%d] = ", i, j);
			scanf("%d", &M1[i][j]);
		}
	}
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			printf("M2[%d][%d] = ", i, j);
			scanf("%d", &M2[i][j]);
		}
	}
	
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			T[i][j] = M1[j][i];
		}
	}
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			S[i][j] = M1[i][j] + M2[i][j];
		}
	}
	
	printf("Matriz T:\n");
	
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			printf("%d\t", T[i][j]);
		}
		printf("\n");
	}
	
	printf("Matriz Soma:\n");
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			printf("%d\t", S[i][j]);
		}
		printf("\n");
	}
	
	
	
	return 0;
}
