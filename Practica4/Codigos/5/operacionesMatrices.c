#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

// Declaracion de funciones
void imprimir(double **m, int n);
void llenar(double **m, int n);
void sumar(double **m1, double **m2, double **resultado, int n);
void restar(double **m1, double **m2, double **resultado, int n);
void multiplicar(double **m1, double **m2, double **resultado, int n);
void transpuesta(double **m, double **resultado, int n);
void inversa(double **matriz, double **resultado, int n);
void iniciar(double **m, int n);
int main(int argc, char const *argv[])
{
	int i, j, k, l, m, n, o, p;
	int det;
	double **matriz1, **matriz2, **suma, **resta, **mul, **tran, **inv;
	time_t t;
	srand((unsigned) time(&t));
	srand((unsigned)time(&t));
	n = 3;

	// Inicializa las matrices.
	iniciar(matriz1, n); iniciar(matriz2, n);
	iniciar(suma, n); iniciar(resta, n);
	iniciar(mul, n); iniciar(tran, n);
	iniciar(inv, n);

	// Llena matriz 1 y matriz 2
	llenar(matriz1, n);
	llenar(matriz2,  n);

	printf("MATRIZ 1\n"); imprimir(matriz1, n);
	printf("MATRIZ 2\n"); imprimir(matriz2, n);

//	printf("SUMA\n"); sumar(matriz1, matriz2, suma, n); imprimir(suma, n);
//	printf("RESTA\n"); restar(matriz1, matriz2, resta, n); imprimir(resta, n);
//	printf("MULTIPLICAR\n"); multiplicar(matriz1, matriz2, mul, n); imprimir(mul, n);
//	printf("TRANSPUESTA\n"); transpuesta(matriz1, tran, n); imprimir(tran, n);
	printf("INVERSA\n"); inversa(matriz1, inv, n); imprimir(inv, n);
	return 0;
}
void iniciar(double **m, int n)
{
	int i;
	m = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		m[i] = (double*)calloc(n,sizeof(double));	
}
void imprimir(double **m, int n)
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
			printf(" %g, ", m[i][j]);					
		printf("\n");
	}
	printf("\n");
}

// Llena con numeros random 
void llenar(double **m, int n)
{
	int i, j, l = 1;
	for (i = 0; i < n; i++) 
	{
		for (j = 0; j < n; j++)
		 {
			m[i][j] = (rand()%10);
			//m[i][j] = l++;
		}
	}
}
void sumar(double **m1, double **m2, double **resultado, int n)
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
			resultado[i][j] = m1[i][j] + m2[i][j];
	}
}

void restar(double **m1, double **m2, double **resultado, int n)
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
			resultado[i][j] = m1[i][j] - m2[i][j];
	}	
}

void multiplicar(double **m1, double **m2, double **resultado, int n)
{
	int i, j, k, aux;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			aux = 0;
			for(k = 0; k < n; k++)
				aux = m1[i][k] * m2[k][j] + aux;
			resultado[i][j] = aux;
		}
	}
}
void transpuesta(double **m, double **resultado, int n)
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
			resultado[i][j] = m[j][i];
	}
}
bool esCero(double x)
{
	return fabs(x) < 1e-8;
}
// Usando definicion de la adjunta
void inversa(double **A, double **resultado, int n)
{
	int i, j, k, l; 
	double *tmp;
	tmp = (double*)malloc(sizeof(double)*n);

	for(i = 0; i < n; ++i)
		resultado[i][i] = 1;
	i = 0; j = 0;
	while(i < n && j < n)
	{
		if(esCero(A[i][j]))
		{
			for(k = i + 1; k < n; ++k)
			{
				if(!esCero(A[k][j]))
				{
					tmp = A[i];
					A[i] = A[k];
					A[k] = tmp;
					tmp = resultado[i];
					resultado[i] = resultado[k];
					resultado[k] = tmp;
					break;
				}
			}
		}
		if(!esCero(A[i][j]))
		{
			for(l = 0; l < n; ++l)
				resultado[i][l] /= A[i][j];
			for(l = n - 1; l >= j; --l)
				A[i][l] /= A[i][j];
			for(k = 0; k < n; ++k)
			{
				if(i == k) continue;
				for(l = 0; l < n; ++l)
					resultado[k][l] -= resultado[i][l] * A[k][j];
				for(l = n; l >= j; --l)
					A[k][l] -= A[i][l] * A[k][j];
			}
			++i;
		}
		++j;
	}
}
