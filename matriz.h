#ifndef MATRIZ_H
#define MATRIZ_H

typedef struct matriz T_MAT;
typedef struct fila T_FILA;
typedef struct elemento T_ELEM;



float le_elem(int i, int j, T_MAT *mat);
void adiciona_elem(int i, int j, double valor, T_MAT *mat);
void remove_elem(int i, int j, T_MAT *mat);

#endif
