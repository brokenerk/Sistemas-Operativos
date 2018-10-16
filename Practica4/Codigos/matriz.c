#include <stdio.h>
#include <stdlib.h>
#define n 3

// Declaracion de funciones
void Imprimir(int m[][n]);
void sumar(int m1[][n], int m2[][n], int resultado[][n]);
void restar(int m1[][n], int m2[][n], int resultado[][n]);
void multiplicar(int m1[][n], int m2[][n], int resultado[][n]);
void transpuesta(int m[][n], int resultado[][n]);


int main(int argc, char const *argv[])
{
	int i, j, k, aux;
	int suma[n][n], resta[n][n], multiplica[n][n], trans[n][n], inversa[n][n];
	
	int matriz1[n][n] = {{2, 0, 1}, {3, 0, 0}, {5, 1, 1}};
	int matriz2[n][n] = {{1, 0, 1}, {1, 2, 1}, {1, 1, 0}};	

	printf("MATRIZ 1\n");
	Imprimir(matriz1);

	printf("MATRIZ 2\n");
	Imprimir(matriz2);

	sumar(matriz1, matriz2, suma);
	printf("SUMA:\n");
	Imprimir(suma);


	restar(matriz1, matriz2, resta);
	printf("RESTA:\n");
	Imprimir(resta);

	multiplicar(matriz1, matriz2, multiplica);
	printf("MULTIPLICACION\n");
	Imprimir(multiplica);

	transpuesta(matriz1, trans);
	printf("TRANSPUESTA\n");
	Imprimir(trans);

	
	return 0;
}

/****************************************************************
							FUNCIONES
/****************************************************************/
void Imprimir(int m[][n])
{
	int aux;
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			printf(" %d, ", m[i][j]);					
			if(j == 2)
			{
				printf("\n");
			}
		}
	}
	printf("\n");
}

void sumar(int m1[][n], int m2[][n], int resultado[][n])
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			resultado[i][j] = m1[i][j] + m2[i][j]; 			
		}
	}
}


void restar(int m1[][n], int m2[][n], int resultado[][n])
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			resultado[i][j] = m1[i][j] - m2[i][j]; 			
		}
	}
}
void multiplicar(int m1[][n], int m2[][n], int resultado[][n])
{
	int i, j, k, aux;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			aux = 0;
			for(k = 0; k < n; k++)
			{
				aux = m1[i][k] * m2[k][j] + aux;
			}
			resultado[i][j] = aux;
		}
	}
}

void transpuesta(int m[][n], int resultado[][n])
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			resultado[i][j] = m[j][i];
		}
	}
}
