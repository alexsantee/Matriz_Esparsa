#include<stdio.h>
#include<stdlib.h>

/*
Este programa trabalha com uma matriz esparça através de uma lista encadeada.
Os elementos são guardados em ordem de linha e depois coluna, como mostra a figura:
|-a-b->|
|-c--->|
|-d-e->|
A numeração tem índice 0
*/

typedef struct elemento{
	int i;
	int j;
	float valor;
	struct elemento *next;
} T_ELEM;

typedef struct matriz{
	int m;
	int n;
	T_ELEM *first;
} T_MAT;

float le_elem(int i, int j, T_ELEM *first){
	//Essa função recebe uma posição (i,j) na matriz e retorna o seu valor
	//A numeração tem índice 0
	T_ELEM *e;
	e = first;
	while( (e->i != i || e->j != j) && e->next != NULL ){
		e = e->next;
	}
	if ( e->i == i && e->j == j ){return e->valor;}
	else {return 0.0;}
}

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

void adiciona_elem(T_ELEM *first, T_ELEM *new){
	//INCOMPLETA
	//Essa função adiciona um elemento na matriz na sua devida posição
	//Caso a posição esteja ocupada ela deve sobreescrever seu valor
	if( (first->i < new->i) || (first->i == new->i && first->j < new->j) ) {
		new->next = first;
		first = new;
		return;
	}
}

// void remove_elem(int i, int j){}

int main(int argc, char *argv[]){
	int m, n;
	printf("Digite o número de linhas e colunas (m,n) da matriz: ");
	scanf(" %d %d", &m, &n);

	T_MAT mat;
	mat.m = m;
	mat.n = n;

	T_ELEM f;
	f.i=0;
	f.j=0;
	f.valor = 1.0;
	f.next = NULL;

	T_ELEM a;
	a.i = 2;
	a.j = 1;
	a.valor = 7.0;
	a.next = NULL;
	f.next = &a;

	mat.first = &f;	

	imprime_matriz(mat);
	return 0;
}
