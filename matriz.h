#ifndef MATRIZ_H
#define MATRIZ_H

typedef struct matriz T_MAT;

T_MAT *cria_matriz(int m, int n);
void apaga_matriz(T_MAT *mat);
double le_elem(int i, int j, T_MAT *mat);
void adiciona_elem(int i, int j, double valor, T_MAT *mat);//Apenas para teste
void remove_elem(int i, int j, T_MAT *mat);

#endif
