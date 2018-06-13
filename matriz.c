#include <stdlib.h>	//Usado para reservar memória para a matriz

//structs públicos
typedef struct matriz T_MAT;

//structs privados
typedef struct fila T_FILA;
typedef struct elemento T_ELEM;

//funções públicas
T_MAT *cria_matriz(int m, int n);
void apaga_matriz(T_MAT *mat);
double le_elem(int i, int j, T_MAT *mat);
void adiciona_elem(int i, int j, double valor, T_MAT *mat);
void remove_elem(int i, int j, T_MAT *mat);

//funções privadas
T_ELEM *acessa_fila(T_FILA fila, int pos, char l_c);
T_ELEM *acessa_linha(T_FILA linha, int j);
T_ELEM *acessa_coluna(T_FILA coluna, int i);
T_ELEM *encontra_elem(T_MAT *mat, int i, int j);

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
	struct elemento *up;
	struct elemento *down;
	struct elemento *right;
	struct elemento *left;
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

void apaga_matriz(T_MAT *mat)
{
	//Limpa todos os endereços reservados da memória.
}

double le_elem(int i, int j, T_MAT *mat){
	//Essa função recebe um número de linha, um de coluna e uma matriz e
	//retorna o valor do elemento naquela poisição da matriz
	T_ELEM *elem;
	elem = encontra_elem(mat, i, j);
	if(elem != NULL){return elem->valor;}
	return 0.0;
}

void adiciona_elem(int i, int j, double valor, T_MAT *mat){
//-----------------------APENAS PARA TESTAR--------------------------------//
	//Essa função recebe um número de linha, um de coluna, um valor e uma
	//matriz e insere valor como elemento daquela posição na matriz
	T_ELEM *elem;
	elem = calloc(1, sizeof(T_ELEM));
	elem->valor = valor;
	mat->linhas.fila[i].first = elem;
	mat->colunas.fila[j].first = elem;
}
//-------------------------------------------------------------------------//
void remove_elem(int i, int j, T_MAT *mat){
	//Essa função recebe um número de linha, um de coluna e uma matriz e
	//zera o elemento daquela posição na matriz
}

T_ELEM *acessa_fila(T_FILA fila, int pos, char l_c){//l_c ascessa linha ou coluna
	//Essa função acessa o item na posição pos (índice 0) de uma fila
	//(linha caso l_c == 'l' e coluna caso l_c == 'c') e retorna ponteiro
	//para o elemento daquela posição. Retorna NULL caso seja 0.
	T_ELEM *elem;
	elem = fila.first;
	while (elem != NULL)
	{
		if (l_c == 'l')
		{
			if (elem->j < pos){elem = elem->right;}
			else if(elem->j == pos){return elem;}
			else {return NULL;}
		}

		else if (l_c == 'c')
		{
			if (elem->i < pos){elem = elem->down;}
			else if(elem->i == pos){return elem;}
			else {return NULL;}
		}
	}
	return NULL;
}

T_ELEM *acessa_linha(T_FILA linha, int j)
{
	//Essa função recebe uma linha e o número da coluna em que está o
	//elemento e retorna um ponteiro para ele. retorna NULL caso ele
	//seja igual a 0
	return acessa_fila(linha, j, 'l');
}

T_ELEM *acessa_coluna(T_FILA coluna, int i)
{
	//Essa função recebe uma coluna e o número da linha em que está o
	//elemento e retorna um ponteiro para ele. retorna NULL caso o elemento
	//seja igual a 0
	return acessa_fila(coluna, i, 'c');
}

T_ELEM *encontra_elem(T_MAT *mat, int i, int j)
{
	//Essa função recebe uma matriz e as posições i e j de um elemento e
	//retorna um ponteiro para esse elemento. retorna NULL caso ele seja
	//igual a zero
	T_ELEM *elem;
	if(mat->linhas.fila[i].n_elem < mat->colunas.fila[j].n_elem)
	{
		elem = acessa_linha(mat->linhas.fila[i], j);
	}
	else
	{
		elem = acessa_coluna(mat->colunas.fila[j], i);
	}
	return elem;

}
