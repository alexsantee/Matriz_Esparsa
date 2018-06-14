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
double soma_linha(int i,T_MAT*mat);
double soma_coluna(int j,T_MAT*mat);

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
	//matriz e insere valor como elemento daquela posição na matriz

	if(i >= mat->m || j >= mat->n)	//Elemento fora da matriz
	{
		return;// SAIR COM ERRO
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
			if (tmp->j < j)	//elem está entre dois outros
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
	if(mat->colunas[j].n_elem == 0)	//A linha está vazia
	{
		mat->colunas[j].first = elem;
	}
	else	//Já existe(m) elemento(s) na linha
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
			if (tmp->i < i)	//elem está entre dois outros
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

double soma_linha(int i,T_MAT*mat)//i:numero da linha
{
double soma=0;

if(mat->linhas[i].n_elem!=0)
    {
    T_ELEM *aux;
    aux=mat->linhas[i].first;
    
    while(aux!=NULL){
        soma+=aux->valor;
        aux=aux.right;
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
        aux=aux.down;
        }
    }
return (soma);
}
