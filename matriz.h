#ifndef MATRIZ_H
#define MATRIZ_H

typedef struct matriz T_MAT;

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

#endif
