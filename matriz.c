#include <stdlib.h>	//Usado para reservar memória para a matriz
#include "matriz.h"	//Protótipos das funções e typedefs das structs

/*
Este programa usa a seguinte estrutura de dados para guardar os elementos de
uma matriz esparsa:

-------------------------------------------------------------------------------
  |
  V
=>  |  |  |  |  |
    v  v  v  v  v
  ->         O->
             |
             v
  ->   O->
       |
       v
  ->      O->
          |
          v
  ->   O->
       |
       v
  ->
-------------------------------------------------------------------------------

              |
As setas => e V representam vetores de ponteiros, sendo que os ponteiros que
elas contém apontam para o primeiro elemento de uma dada linha/coluna. além
de guardar esses ponteiros, essa extrutura guarda seu próprio tamanho. 

              |
As setas -> e v representam ponteiros para o primeiro elemento daquela linha/
coluna. Porém a estrutura também guarda o número de elementos diferentes de
zero naquela fila.

As estruturas O-> representam cada elemento diferente de zero  da matriz.
              |   A estrutura guarda o valor do elemento, e ponteiros para
              v   os próximos elemento tanto em cima quanto em baixo.
*/

struct elemento{
	int i;
	int j;
	double valor;
	struct elemento *right;
	struct elemento *down;
};

struct fila{	//Linha ou coluna da matriz
	int n_elem;	//Número de elementos diferentes de 0 na fila
	T_ELEM *first;
};

struct matriz{
	struct{	//Vetor de filas que guarda seu tamanho
		int len;
		T_FILA *fila;
	} linhas, colunas;

};

T_MAT *cria_matriz(int m, int n){
	T_MAT *mat;
	mat = calloc(1,sizeof(T_MAT));
	mat->linhas.len = m;
	mat->colunas.len = n;
	mat->linhas.fila = calloc(m, sizeof(T_FILA));
	mat->colunas.fila = calloc(n, sizeof(T_FILA));
	return mat;
}

double le_elem(int i, int j, T_MAT *mat){
	//Essa função recebe um número de linha, um de coluna e uma matriz e
	//retorna o valor do elemento naquela poisição da matriz
}

void adiciona_elem(int i, int j, double valor, T_MAT *mat){
	//Essa função recebe um número de linha, um de coluna, um valor e uma
	//matriz e insere valor como elemento daquela posição na matriz
}
void remove_elem(int i, int j, T_MAT *mat){
	//Essa função recebe um número de linha, um de coluna e uma matriz e
	//zera o elemento daquela posição na matriz
}
