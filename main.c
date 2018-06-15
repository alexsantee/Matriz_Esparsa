#include <stdio.h>	//usado na interação com o usuário
#include <stdlib.h>	//usado para fazer um vetor de matrizes
#include "matriz.h" //usado para administrar as matrizes

//void imprime_matriz(T_MAT mat);
int menu();
void clear();


int main(int argc, char *argv[]){
	int opcoes;
	char alt;
	do{
		clear();
		opcoes = menu();

		if(opcoes == 1){

		}
		else if (opcoes == 2){
		}
		else if (opcoes == 3){
		}
		else if(opcoes == 4){
			printf("Certeza que deseja sair?[S/N]\n>> ");
			scanf(" %c", &alt);
			while(alt != 'S' && alt != 's' && alt != 'n' && alt != 'N'){
				printf("Opcao inválida, digite novamente.>> \n");
				scanf(" %c", &alt);
			}
		}
	}while(opcoes != 's' && opcoes != 'S');

	return 0;
}

int menu(){
	char opcao_menu;
	int opcao_menu_int;
	printf("Bem-vindo ao programa de matrizes esparsas!\n\n");
	printf("***** MENU *****\n");
	printf("1.Consultar um valor na matriz\n");
	printf("2.Imprimir a matriz\n");
	printf("3.Alterar um valor na matriz\n");
	printf("4.Criar uma matriz\n");
	printf("0.Sair\n>> ");
	scanf(" %d", &opcao_menu);
	return opcao_menu;
}

void clear(){
	#ifdef WIN32
   		system("CLS");
	#else
    		system("clear");
	#endif
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
