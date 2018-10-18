#include <stdio.h>
#include <stdlib.h>

// Declaracion de funciones
void imprimir(double **m, int tam);

int main(int argc, char const *argv[])
{
	int j, k , l, m, n, o, p, q, r, s;
	double **matriz1, **matriz2;
	n = 3;
	matriz1 = (double**)calloc(n, sizeof(double*));
	for(j = 0; j < n; j++)
	{
		matriz1[j] = (double*)calloc(n, sizeof(double));
	}

	matriz2 = (double**)calloc(n, sizeof(double*));
	for(j = 0; j < n; j++)
	{
		matriz2[j] = (double*)calloc(n, sizeof(double));
	}

	matriz1[n][n] = {{2, 0, 1}, {3, 0, 0}, {5, 1, 1}};
	imprimir(matriz1, n);

	return 0;
}


void imprimir(double **m, int n)
{
	int aux;
	int i, j;
	m = (double**)calloc(n, sizeof(double*));
	for(j = 0; j < n; j++)
	{
		m[j] = (double*)calloc(n, sizeof(double));
	}
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