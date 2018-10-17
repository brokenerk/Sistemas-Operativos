#include <stdio.h>
#include <stdlib.h>
#define n 3

// Declaracion de funciones
void Imprimir(int m[][n]);
void sumar(int m1[][n], int m2[][n], int resultado[][n]);
void restar(int m1[][n], int m2[][n], int resultado[][n]);
void multiplicar(int m1[][n], int m2[][n], int resultado[][n]);
void transpuesta(int m[][n], int resultado[][n]);
int determinante(int m[][n-1]);
void inversa(int m[][n], int resultado[][n]);


int main(int argc, char const *argv[])
{
	int i, j, k, aux;
	int suma[n][n], resta[n][n], multiplica[n][n], trans[n][n], inv[n][n];
	
	int matriz1[n][n] = {{2, 0, 1}, {3, 0, 0}, {5, 1, 1}};
	int matriz2[n][n] = {{1, 0, 1}, {1, 2, 1}, {1, 1, 0}};	

	printf("MATRIZ 1\n");
	Imprimir(matriz1);

	/*printf("MATRIZ 2\n");
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

	int deter = determinante(matriz1);
	printf("DETERMINANTE = %d\n", deter);
*/
	inversa(matriz1, inv);

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

int determinante(int m[][n-1])
{
	int i, j, producto1, producto2, col, fil, sumapos, sumaneg, suma;
	sumapos = 0;
	sumaneg = 0;
	suma = 0;
	for(i = 0; i < n-1; i++)
	{
		producto1 = 1;
		producto2 = 1;
		for(j = 0; j < n-1; j++)
		{
			col = j + i;
			if( col >= n-1 )
				col = col - n-1;

			producto1 = producto1 * m[j][col];
			producto2 = producto2 * m[n-(j+1)][col];
		}
		sumapos = sumapos + producto1;
		sumaneg = sumaneg + producto2;
	}
	suma = sumapos - sumaneg;
	return suma;
}

void inversa(int m[][n], int resultado[][n])
{
	int i, j, k, l, o, r, s;
	int det;
	int matrizDeterminante[n - 1][n - 1], aux[n][n];

	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			// ESTOY EN UNA DE LAS POSICIONES m[i][j]
			for(k = 0, r = 0; k < n; k++)
			{
				for (l = 0, s = 0; l < n; l++) 
				{
					if ((k != i) && (l != j))
					{
						matrizDeterminante[r][s] = m[k][l];
						r++;
						s++;
					}
				}
			}
			det = determinante(matrizDeterminante);
			aux[i][j] = det;
		}
	}
	Imprimir(aux);
}
