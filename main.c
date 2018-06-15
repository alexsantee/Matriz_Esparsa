#include <stdio.h>	//usado na interação com o usuário
#include <locale.h> //usado para colocar a escrida em português

#include "matriz.h" //usado para administrar as matrizes

int menu();
void clear();
void pause();

int main(int argc, char *argv[]){
	char resp_user;
	int m,n;
	double valor;
	int existe_matriz=0;
    T_MAT *mat;
	
	do  {
		clear();
		resp_user = menu();
		if(resp_user == '1')
            {
            printf("***** Setor de crição de matriz *****\n");
            printf("Insira o valor m(numero de linhas da matriz:");
            scanf(" %d",&m);
            printf("Insira o valor n(numero de calonas da matriz:");
            scanf(" %d",&n);
            mat = cria_matriz(m,n);	//Cria matriz de tamanho mn e dá ponteiro para ela
            puts("Matriz criada.\n");
            existe_matriz=1;
            pause();
            }
		if(resp_user == '2')
            {
            printf("***** Setor de exclusão de matriz *****\n");
            apaga_matriz(T_MAT *mat);
            puts("Matriz excluida.")
            existe_matriz=0;
            pause();
            }
		if(resp_user == '3')
            {
                if(existe_matriz==1)
                {
                printf("***** Setor de valor de uma posição *****\n");
                printf("Insira o valor da posição j:\n");
                scanf(" %d",&i);
                printf("Insira o valor da posição i:\n");
                scanf(" %d",&j);
                valor = le_elem(i,j, T_MAT *mat);
                printf("Na posição %d,%d o valor do elmento é %0.2ld.\n",valor);
                pause();
                }else{puts("Você não defeniu matriz.");}
            }
        if(resp_user == '4')
            {
                if(existe_matriz==1)
                {
                printf("***** Setor de soma dos valores de uma linha *****\n");
                printf("Qual linha:\n");
                scanf(" %d",&i);
                valor = soma_linha( i,T_MAT*mat);
                printf("O valor da  soma dos valores da linha %d é %0.2ld.\n",i,valor);
                pause();
                }else{puts("Você não defeniu matriz.");}
            }
		if(resp_user == '5')
            {
                if(existe_matriz==1)
                {
                printf("***** Setor de soma dos valores de uma coluna *****\n");
                printf("Qual coluna:\n");
                scanf(" %d",&i);
                valor = soma_coluna(j,T_MAT*mat);
                printf("O valor da  soma dos valores da coluna %d é %0.2ld.\n",j,valor);
                pause();
                }else{puts("Você não defeniu matriz.");}
            }
        if(resp_user == '6')
            {
                if(existe_matriz==1)
                {
                printf("***** Atribuição de  valor em uma posição *****\n");
                printf("Insira o valor da posição i:\n");
                scanf(" %d",&i);
                printf("Insira o valor da posição j:\n");
                scanf(" %d",&j);
                printf("Qual valor:\n");
                scanf(" ld",&valor);
                adiciona_elem(i,j, double valor, T_MAT *mat);
                printf("Na posição %d,%d o valor colocado foi %ld.\n",i,j,valor);
                pause();
                }else{puts("Você não defeniu matriz.");}
            }
		if(resp_user == '7')
            {
                if(existe_matriz==1)
                {
                    i = n_linhas(T_MAT *mat);
                    j = n_colunas(T_MAT *mat);
                    if(i==j)
                    {
                    printf("***** Setor do determinante *****\n");
                    valor = determinante(T_MAT *mat);
                    printf("O valor do determinante é : 0.2ld \n",valor;
                    pause();
                    }
                }else{puts("Você não defeniu matriz.");}
            }
        
        }while(resp_user !='0');

	return 0;
}

char menu()
{
    char resp;
    do  {
        printf("Bem-vindo ao programa de matrizes esparsas!\n\n");
        printf("***** MENU *****\n");
        printf("1.Criação da matriz m por n.\n");
        printf("2.Exclusão da matriz.\n");
        printf("3.Consulta dos valores de uma posição (i, j) da matriz.\n");
        printf("4.Consulta da soma dos valores de cada linha da matriz.\n");
        printf("5.Consulta da soma dos valores de cada coluna da matriz\n");
        printf("6. Atribuição de um valor na posição (i, j) da matriz\n");
        printf("7. Calcular o determinante da matriz (2.0)\n");
        printf("0.Sair\n");
        scanf(" %c", &resp);
        }while(resp<'0'||resp>'7');
        return resp;
}

void clear()
{
	#ifdef WIN32
   		system("CLS");
	#else
    		system("clear");
	#endif
}

void pause()
{
    char pausa;
    puts("Aperte enter")
    while( ( pause=getchar() ) != '\n' && pause != '\0');   //Pula caracteres lixo
}
