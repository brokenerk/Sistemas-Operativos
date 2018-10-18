#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Declaracion de funciones
void imprimir(double **m, int n);
void llenar(double **m, int n);
void sumar(double **m1, double **m2, double **resultado, int n);
void restar(double **m1, double **m2, double **resultado, int n);
void multiplicar(double **m1, double **m2, double **resultado, int n);
void transpuesta(double **m, double **resultado, int n);
void inversa(double **matriz, double **resultado, int n);
int determinante(double **m, int n);
void getCofactor(double **m, double **temp, int p, int q, int n);
int potencia(int base, int pot);

int main(int argc, char const *argv[])
{
	int i, j, k, l, m, n, o, p;
	int det;
	time_t t;
	srand((unsigned) time(&t));
	srand((unsigned)time(&t));
	double **matriz1, **matriz2, **suma, **resta, **mul, **tran, **inv;
	n = 3;

	// Inicializa las matrices.
	matriz1 = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		matriz1[i] = (double*)calloc(n,sizeof(double));

	matriz2 = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		matriz2[i] = (double*)calloc(n,sizeof(double));

	suma = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		suma[i] = (double*)calloc(n,sizeof(double));

	resta = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		resta[i] = (double*)calloc(n,sizeof(double));
	
	mul = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		mul[i] = (double*)calloc(n,sizeof(double));

	tran = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		tran[i] = (double*)calloc(n,sizeof(double));

	inv = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		inv[i] = (double*)calloc(n,sizeof(double));

	// Llena matriz 1 y matriz 2
	llenar(matriz1, n);
	llenar(matriz2,  n);

	printf("MATRIZ 1\n"); imprimir(matriz1, n);
//	printf("MATRIZ 2\n"); imprimir(matriz2, n);

//	printf("SUMA\n"); sumar(matriz1, matriz2, suma, n); imprimir(suma, n);
//	printf("RESTA\n"); restar(matriz1, matriz2, resta, n); imprimir(resta, n);
//	printf("MULTIPLICAR\n"); multiplicar(matriz1, matriz2, mul, n); imprimir(mul, n);
//	printf("TRANSPUESTA\n"); transpuesta(matriz1, tran, n); imprimir(tran, n);
	
	printf("INVERSA\n"); inversa(matriz1, inv, n); imprimir(inv, n);

	return 0;
}

void imprimir(double **m, int n)
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			printf(" %g, ", m[i][j]);					
		}
		printf("\n");
	}
	printf("\n");
}

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
void getCofactor(double **m, double **temp, int p, int q, int n)
{
	int i = 0, j = 0; 
    int row, col;
    // Looping for each element of the matrix 
    for (row = 0; row < n; row++) 
    { 
        for (col = 0; col < n; col++) 
        { 
            //  Copying into temporary matrix only those element 
            //  which are not in given row and column 
            if (row != p && col != q) 
            { 
                temp[i][j++] = m[row][col]; 
  
                // Row is filled, so increase row index and 
                // reset col index 
                if (j == n - 1) 
                { 
                    j = 0; 
                    i++; 
                } 
            } 
        } 
    } 	
}
int potencia(int base, int pot)
{
	int i;
	int resultado = 1;
	for(i = 0; i < pot; i++)
	{
		resultado = base * resultado;
	}
	return resultado;
}
int determinante(double **m, int n)
{
	int i, f;
	int D = 0; // Initialize result 
  
    //  Base case : if matrix contains single element 
    if (n == 1) 
        return m[0][0]; 
  
    double **temp; // To store cofactors 
  	temp = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		temp[i] = (double*)calloc(n,sizeof(double));
	
    int sign = 1;  // To store sign multiplier 
  
     // Iterate for each element of first row 
    for (f = 0; f < n; f++) 
    { 
        // Getting Cofactor of mat[0][f] 
        getCofactor(m, temp, 0, f, n); 
        D += sign * m[0][f] * determinante(temp, n - 1); 
  
        // terms are to be added with alternate sign 
        sign = -sign; 
    } 
  
    return D; 
}
void sumar(double **m1, double **m2, double **resultado, int n)
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

void restar(double **m1, double **m2, double **resultado, int n)
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

void multiplicar(double **m1, double **m2, double **resultado, int n)
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
void transpuesta(double **m, double **resultado, int n)
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

void inversa(double **matriz, double **resultado, int n)
{
	int b, i, j, k, l, m, o, p, q, r, s;
	int det, D, signo;
	double **aux, **matrizDet, **trans;
	double num;
	aux = (double**)calloc(n, sizeof(double*));
	for (i = 0; i < n; i++)
		aux[i] = (double*)calloc(n, sizeof(double));

	matrizDet = (double**)calloc(n, sizeof(double*));
	for (i = 0; i < n; i++)
		matrizDet[i] = (double*)calloc(n, sizeof(double));
	
	trans = (double**)calloc(n, sizeof(double*));
	for (i = 0; i < n; i++)
		trans[i] = (double*)calloc(n, sizeof(double));
		

	D = determinante(matriz, n);
	if(D != 0)
	{
		printf("-------------- SI EXISTE\n");
		for(i = 0; i < n; i++)
		{
			for(j = 0; j < n; j++)
			{
				// ESTOY EN UNA DE LAS POSICIONES m[i][j]
				//printf("\n \n ---> Estoy en la posicion: [%d][%d] con valor: %g\n", i, j, matriz[i][j]);
				for(k = 0, r = 0; k < n; k++)
				{
					for (l = 0, s = 0; l < n; l++) 
					{
						//printf("  Comparo ( %d != %d ) && ( %d != %d ) \n" , k, i, l, j);
						if ((k != i) && (l != j))
						{
							//printf("  Compare ( %d != %d ) && ( %d != %d ) \n" , k, i, l, j);
							//printf(" --------------------- Entra en este caso\n");
							//printf("  *** MATRIZ AUX[%d][%d] tiene %g\n", r, s, aux[r][s]);
							aux[r][s] = matriz[k][l];
							s++;
						}
					}
					if(i != k)
						r++;
				}
				//printf(" MATRIZ DETERMINANTE PARA ESTA POSICION\n");
				//imprimir(aux, n-1);
				num = n - 1;
				det = determinante(aux, num);
				//printf("       ----- Determinante: %d\n", det);
				b = -1;
				p = i + j;
				signo = potencia(b, p);
				//printf("potencia: %d\n", signo );
				matrizDet[i][j] = signo * det;
			}
		}
		printf("MATRIZ DETERMINANTE\n");
		imprimir(matrizDet, n);

		// Se saca la matriz transpuesta
		transpuesta(matrizDet, trans, n);
		imprimir(trans, n);
		// Multiplicar por el determinante de m
		num = 1.0 / (double)D;
		
		printf("multiplicado por: %g\n", num);
		for(i = 0; i < n; i++)
		{
			for(j = 0; j < n; j++)
			{
				resultado[i][j] = num * trans[i][j];
			}
		}
	}
	else
	{
		printf("No existe la matriz inversa\n");
	}
}
