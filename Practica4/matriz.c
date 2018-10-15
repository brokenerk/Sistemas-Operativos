#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int i, j, n = 3;
	int matriz1[n][n], matriz2[n][n], ;
	int suma[n][n], resta[n][n], multiplica[n][n], trans[n][n], inversa[n][n];
	
	matriz1 = {{2, 0, 1}, {3, 0, 0}, {5, 1, 1}};
	matriz2 = {{1, 0, 1}, {1, 2, 1}, {1, 1, 0}};	

	// Imprimir matriz
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			printf("Matriz 1: %d",matriz1[i][j]);					
		}
	}

	// Suma
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			suma[i][j] = matriz1[i][j] + matriz2[i][j]; 			
		}
	}

	// Imprimir matriz
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			printf("Matriz 1: %d",suma[i][j]);					
		}
	}

	// Resta
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			suma[i][j] = matriz1[i][j] + matriz2[i][j]; 			
		}
	}



		return 0;
}
