#include <stdlib.h>	//Usado para reservar memória para a matriz

#define ERR_OUT_OF_MATRIX -1
#define ERR_NON_SQR_MAT_DET -2

//structs públicos
typedef struct matriz T_MAT;

//structs privados
typedef struct fila T_FILA;
typedef struct elemento T_ELEM;

//funções públicas
T_MAT *cria_matriz(int m, int n);	//Cria matriz de tamanho mn e dá ponteiro para ela
void apaga_matriz(T_MAT *mat);	//Limpa memória reservada para uma matriz
int n_linhas(T_MAT *mat);	//Retorna o número de linhas de uma matriz
int n_colunas(T_MAT *mat);	//Retorna o número de colunas de uma matriz
double le_elem(int i, int j, T_MAT *mat);	//Dá o valor do elemento na posição ij
void adiciona_elem(int i, int j, double valor, T_MAT *mat);	//Define/substitui valor de ij
void remove_elem(int i, int j, T_MAT *mat);	//Remove elemento da posição ij
double soma_linha(int i,T_MAT*mat);	//Retorna a soma da linha i
double soma_coluna(int j,T_MAT*mat);	//Retorna a soma da coluna j
double determinante(T_MAT *mat);	//Calcula o determinante de uma matriz quadrada


//funções privadas
//Retorna elemento da fila em pos. 'l' procura em linha e 'c' coluna
T_ELEM *acessa_fila(T_FILA fila, int pos, char l_c);
T_ELEM *acessa_linha(T_FILA linha, int j);	//Retorna elemento da fila em j
T_ELEM *acessa_coluna(T_FILA coluna, int i);	//Retorna elemento da fila em i
T_ELEM *encontra_elem(T_MAT *mat, int i, int j);	//Retorna elemento na posição ij
T_MAT *remove_lin_col(int i, int j, T_MAT *mat);	//Dá uma cópia da matriz sem as filas ij

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
de guardar esses ponteiros, essa estrutura guarda seus tamanhos. 

              |
As setas -> e v representam ponteiros para o primeiro elemento daquela linha/
coluna. Porém a estrutura também guarda o número de elementos diferentes de
zero naquela fila.

As estruturas O-> representam cada elemento diferente de zero  da matriz.
              |   A estrutura guarda o valor do elemento, e ponteiros para
              v   os elementos de cima, baixo, esquerda e direita.
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
	T_FILA *linhas;
	T_FILA *colunas;
	int m;
	int n;
};

T_MAT *cria_matriz(int m, int n){
	//Cria uma matriz de tamanho mn e retorna ponteiro para ela
	T_MAT *mat;
	mat = calloc(1,sizeof(T_MAT));
	mat->m = m;
	mat->n = n;
	mat->linhas = calloc(m, sizeof(T_FILA));
	mat->colunas = calloc(n, sizeof(T_FILA));
	return mat;
}

void apaga_matriz(T_MAT *mat)
{
	//Limpa todos os endereços reservados da memória.
	int i;
	T_ELEM *cur;
	T_ELEM *tmp;
	for(i=0; i < mat->m; i++)	//Limpa os elementos
	{
		cur = mat->linhas[i].first;
		while(cur!=NULL)
		{
			tmp = cur->right;
			free(cur);
			cur = tmp;
		}
	}
	//Limpa os vetores de filas
	free(mat->linhas);
	free(mat->colunas);
	//Limpa a matriz
	free(mat);
}

int n_linhas(T_MAT *mat)
{
	//Retorna o número de linhas de uma matriz
	return mat->m;
}

int n_colunas(T_MAT *mat)
{
	//Retorna o número de colunas de uma matriz
	return mat->n;
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
	//Adiciona/modifica o valor do elemento ij

	if(i >= mat->m || j >= mat->n || i<0 || j<0)	//Elemento fora da matriz
	{
		exit(ERR_OUT_OF_MATRIX);
	}

	if(valor==0.0)
	{
		remove_elem(i,j,mat);
		return;
	}

	T_ELEM *elem;
	if( ( elem=encontra_elem(mat,i,j) ) != NULL)	//Já existe elem em i,j
	{
		elem->valor = valor;
		return;
	}

	//Será de fato adicionado um novo elemento
	elem = calloc(1, sizeof(T_ELEM));
	elem->i = i;
	elem->j = j;

	//Adiciona elemento na linha
	if(mat->linhas[i].n_elem == 0)	//A linha está vazia
	{
		mat->linhas[i].first = elem;
	}
	else	//Já existe(m) elemento(s) na linha
	{
		T_ELEM *tmp;
		tmp = mat->linhas[i].first;	//Primeiro elemento
		if (tmp->j > j)	//elem é primeiro elemento
		{
			mat->linhas[i].first = elem;
			elem->right = tmp;
			tmp->left = elem;
		}
		else
		{
			while(tmp->j < j && tmp->right != NULL)
			{
				tmp = tmp->right;
			}
			if (tmp->j > j)	//elem está entre dois outros
			{
				elem->right=tmp;
				elem->left=tmp->left;
				tmp->left->right=elem;
				tmp->left = elem;
			}
			else	//elem é o último elemento
			{
				elem->left = tmp;
				tmp->right = elem;
			}
		}
	}

	//Adiciona elemento na coluna
	if(mat->colunas[j].n_elem == 0)	//A coluna está vazia
	{
		mat->colunas[j].first = elem;
	}
	else	//Já existe(m) elemento(s) na coluna
	{
		T_ELEM *tmp;
		tmp = mat->colunas[j].first;	//Primeiro elemento
		if (tmp->i > i)	//elem é primeiro elemento
		{
			mat->colunas[j].first = elem;
			elem->down = tmp;
			tmp->up = elem;
		}
		else
		{
			while(tmp->i < i && tmp->down != NULL)
			{
				tmp = tmp->down;
			}
			if (tmp->i > i)	//elem está entre dois outros
			{
				elem->down=tmp;
				elem->up=tmp->up;
				tmp->up->down=elem;
				tmp->up = elem;
			}
			else	//elem é o último elemento
			{
				elem->up = tmp;
				tmp->down = elem;
			}
		}
	}

	mat->linhas[i].n_elem++;
	mat->colunas[j].n_elem++;
}

void remove_elem(int i, int j, T_MAT *mat){
	//Essa função recebe um número de linha, um de coluna e uma matriz e
	//zera o elemento daquela posição na matriz
	T_ELEM *elem;
	if( (elem=encontra_elem(mat,i,j)) == NULL ){return;}
	else
	{
		elem->right->left=elem->left;
		elem->left->right=elem->right;
		elem->down->up=elem->up;
		elem->up->down=elem->down;
		free(elem);
		mat->linhas[i].n_elem--;
		mat->colunas[j].n_elem--;
	}
}

double soma_linha(int i,T_MAT*mat)//i:numero da linha
{
double soma=0;

if(mat->linhas[i].n_elem!=0)
    {
    T_ELEM *aux;
    aux=mat->linhas[i].first;
    
    while(aux!=NULL){
        soma+=aux->valor;
        aux=aux->right;
        }
    }
return (soma);
}

double soma_coluna(int j,T_MAT*mat)//j:numero da coluna
{
double soma=0;

if(mat->colunas[j].n_elem!=0)
    {
    T_ELEM *aux;
    aux=mat->colunas[j].first;
    
    while(aux!=NULL){
        soma+=aux->valor;
        aux=aux->down;
        }
    }
return (soma);
}

double determinante(T_MAT *mat)
{
	//Calcula o determinante de uma matriz quadrada
	if (mat->m != mat->n)	//Caso matriz não quadrada
	{
		exit(ERR_NON_SQR_MAT_DET);
	}
	if (mat->m == 1)	//BASE: matriz de ordem 1
	{
		return mat->linhas[0].first->valor;
	}

	//Teorema de Laplace
	//Encontra menor fila

	int min;	//número de elementos da menor fila
	min = mat->linhas[0].n_elem;
	char l_c = 'l';	//'l'==linha, 'c'==coluna
	int n_fila;	//posição da menor fila

	int i;
	for (i=0; i < mat->m; i++)
	{
		if(mat->linhas[i].n_elem < min)
			{
				min = mat->linhas[i].n_elem;
				l_c = 'l';
				n_fila=i;
			}
		if(mat->colunas[i].n_elem < min)
			{
				min = mat->colunas[i].n_elem;
				l_c = 'c';
				n_fila=i;
			}
	}
	if (min==0){return 0.0;}	//Caso fila de 0s, det==0

	//Aplica a regra
	double det = 0.0;
	char neg;	//Sinal que alterna
	if(n_fila%2==0){neg = 1;}
	else {neg = -1;}
	T_MAT *new;
	for (i=0; i < mat->m; i++, neg*=-1)
	{
		if(l_c=='l')
		{
			new = remove_lin_col(n_fila,i,mat);
			det += neg*determinante(new);
			apaga_matriz(new);
		}
		if(l_c=='c')
		{
			new = remove_lin_col(i,n_fila,mat);
			det += neg*determinante(new);
			apaga_matriz(new);
		}

	}
	return det;
}

T_ELEM *acessa_fila(T_FILA fila, int pos, char l_c){//l_c acessa linha ou coluna
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
	if( i>=mat->m || j>=mat->n || i<0 || j<0)	//Elemento fora da matriz
	{
		exit(ERR_OUT_OF_MATRIX);
	}

	T_ELEM *elem;
	if(mat->linhas[i].n_elem < mat->colunas[j].n_elem)
	{
		elem = acessa_linha(mat->linhas[i], j);
	}
	else
	{
		elem = acessa_coluna(mat->colunas[j], i);
	}
	return elem;

}

T_MAT *remove_lin_col(int i, int j, T_MAT *mat)
{
	//Cria uma matriz e copia os elementos da primeira matriz de forma que
	//a nova seja a primeira removida das linha e coluna i e j.
	//Retorna ponteiro para essa nova matriz.
	T_MAT *new;
	new = cria_matriz(mat->m -1, mat->n -1);
	int iii;
	double valor;
	T_ELEM *tmp;
	for(iii=0; iii < i; iii++)	//Linhas antes do corte
	{
		tmp = mat->linhas[iii].first;
		while(tmp!=NULL)
		{
			if(tmp->j < j)	//Colunas antes do corte
			{
				valor = tmp->valor;
				adiciona_elem(i,j,valor,new);
			}
			else	//colunas depois do corte
			{
				valor = tmp->valor;
				adiciona_elem(i,j-1,valor,new);
			}
		}
	}
	for(iii=i+1; iii > i && iii < mat->m; iii++)	//Linhas depois do corte
	{
		tmp = mat->linhas[iii].first;
		while(tmp!=NULL)
		{
			if(tmp->j < j)	//Colunas antes do corte
			{
				valor = tmp->valor;
				adiciona_elem(i-1,j,valor,new);
			}
			else	//colunas depois do corte
			{
				valor = tmp->valor;
				adiciona_elem(i-1,j-1,valor,new);
			}
		}
	}

	return new;
}
