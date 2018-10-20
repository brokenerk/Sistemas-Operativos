#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

// Declaracion de funciones
void imprimir(double **m, int n);
void llenar(double **m, int n);
void restar(double **m1, double **m2, double **resultado, int n);
void crearArchivo(double **matriz, int n, char *directorio);

int main(int argc, char const *argv[])
{
	int i, n;
	double **matriz1, **matriz2, **resta;
	time_t t;
	srand((unsigned) time(&t));
	n = 10;

	// Inicializa las matrices.
	matriz1 = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		matriz1[i] = (double*)calloc(n,sizeof(double));

	matriz2 = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		matriz2[i] = (double*)calloc(n,sizeof(double));
	
	resta = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		resta[i] = (double*)calloc(n,sizeof(double));

	// CREAR DIRECTORIO
	char* path = (char*)calloc(2000,sizeof(char));
	path = "/home/enrike/Escritorio/P4-SO/8/Resultados/resta.txt";

	// Llena matriz 1 y matriz 2
	llenar(matriz1, n);
	llenar(matriz2, n);

	printf("MATRIZ 1\n"); imprimir(matriz1, n);
	printf("MATRIZ 2\n"); imprimir(matriz2, n);

	 
	restar(matriz1, matriz2, resta, n); 
	crearArchivo(resta, n, path);
	
	printf("ARCHIVO RESTA ESCRITO\n");
	printf("%s", path);
	printf("\n");

	return 0;
}

void crearArchivo(double **matriz, int n, char *directorio)
{
    int i,j;
    char num[15];

    if(creat(directorio, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1)
    {
        perror(directorio);
        exit(EXIT_FAILURE);
    }
    else
    {
    	int a = open(directorio, O_WRONLY | O_APPEND);
    	if(a == -1)
    	{
    		perror(directorio);
        	exit(EXIT_FAILURE);
    	}
    	else
    	{
    		for (i = 0; i < n; i++)
        	{
            	for(j = 0; j< n; j++)
            	{
            		sprintf(num, "%.3f\t", matriz[i][j]);
                	if(!write(a, num, strlen(num)) == strlen (num))
                	{
                		perror(directorio);
        				exit(EXIT_FAILURE);
                	}
            	}
            	if(!write(a, "\n", strlen("\n")) == strlen ("\n"))
                	{
                		perror(directorio);
        				exit(EXIT_FAILURE);
                	}
        	}
    	}
    	close(a);
    }
}

void imprimir(double **m, int n)
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
			printf("%.3f\t", m[i][j]);					
		printf("\n");
	}
	printf("\n");
}

// Llena con numeros random 
void llenar(double **m, int n)
{
	int i, j;
	for (i = 0; i < n; i++) 
	{
		for (j = 0; j < n; j++)
		 {
			m[i][j] = (rand()%11);
		}
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