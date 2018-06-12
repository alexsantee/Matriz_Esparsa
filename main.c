#include <stdio.h>	//usado na interação com o usuário
#include <stdlib.h>	//usado para fazer um vetor de matrizes
#include "matriz.h" //usado para administrar as matrizes

//void imprime_matriz(T_MAT mat);

int main(int argc, char *argv[]){

	return 0;
}

/*
Reescrever sem usar diretamente as variáveis da matriza, mas usando apenas
comandos de "matriz.h"
void imprime_matriz(T_MAT mat){
	int i;
	int j;
	for (i=0; i<mat.m; i++){
		for (j=0; j<mat.n; j++){
			printf("%.1f ", le_elem(i,j,mat.first));
		}
		printf("\b\n");
	}	
}
*/
