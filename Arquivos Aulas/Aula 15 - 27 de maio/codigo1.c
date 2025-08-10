#include <stdio.h>
#include <string.h>

int main(){
	
	char str1[100];
	char str2[100];
	char str3[100];
	char aux[100];
	
	fgets(str1, sizeof(str1), stdin);		
	fgets(str2, sizeof(str2), stdin);		
	fgets(str3, sizeof(str3), stdin);		
		
	str1[strlen(str1) - 1] = '\0';
	str2[strlen(str2) - 1] = '\0';
	str3[strlen(str3) - 1] = '\0';
	
	if(strcmp(str1, str2) > 0){
		strcpy(aux, str1);
		strcpy(str1, str2);
		strcpy(str2, aux);
	}
	
	if(strcmp(str2, str3) > 0){
		strcpy(aux, str2);
		strcpy(str2, str3);
		strcpy(str3, aux);
	}
	
	if(strcmp(str1, str2) > 0){
		strcpy(aux, str1);
		strcpy(str1, str2);
		strcpy(str2, aux);
	}
	
	printf("Ordem: %s %s %s\n", str1, str2, str3);
	
	/*
	if((strcmp(str1, str2) <= 0) && (strcmp(str2, str3) <= 0)){
		printf("Ordem: %s %s %s\n", str1, str2, str3);
	}else if((strcmp(str1, str3) <= 0) && (strcmp(str3, str2) <= 0)){
		printf("Ordem: %s %s %s\n", str1, str3, str2);
	}else if((strcmp(str2, str1) <= 0) && (strcmp(str1, str3) <= 0)){
		printf("Ordem: %s %s %s\n", str2, str1, str3);
	}else if((strcmp(str2, str3) <= 0) && (strcmp(str3, str1) <= 0)){
		printf("Ordem: %s %s %s\n", str2, str3, str1);
	}else if((strcmp(str3, str1) <= 0) && (strcmp(str1, str2) <= 0)){
		printf("Ordem: %s %s %s\n", str3, str1, str2);
	}else if((strcmp(str3, str2) <= 0) && (strcmp(str2, str1) <= 0)){
		printf("Ordem: %s %s %s\n", str3, str2, str1);
	}
	*/
	return 0;
}
