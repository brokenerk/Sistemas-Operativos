//	Compilación:
//	gcc tiempo.c -c
//	gcc 5.c tiempo.o -o 5

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
#include "tiempo.h"

// Declaracion de funciones
void imprimir(double **m, int n);
void llenar(double **m, int n);
void sumar(double **m1, double **m2, double **resultado, int n);
void restar(double **m1, double **m2, double **resultado, int n);
void multiplicar(double **m1, double **m2, double **resultado, int n);
void transpuesta(double **m, double **resultado, int n);
int inversa(double **matriz, double **resultado, int n);
double determinante(double **matriz, int n);
void crearArchivo(double **matriz, int n, char *nombre, char *directorio);
int potencia(int base, int pot);
void imprimirArchivo(char *directorio, char *nombre);


void crearArchivo(double **matriz, int n, char *nombre, char *directorio)
{
    int i,j;
    char* dir = (char *)calloc(2000, sizeof(char));
    char* aux = (char *)calloc(2000, sizeof(char));
    char num[15];
    strcpy(aux, directorio);
    strcat(directorio, nombre);
    strcpy(dir, directorio);

    // LLamada al sistema cret, recibe la ruta del archivo a crear y los permisos
    // Retorna -1 si hay errores
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
    strcpy(directorio, aux);
    free(aux); free(dir); 
}

void imprimirArchivo(char *directorio, char *nombre)
{
	char* dir = (char *)calloc(2000, sizeof(char));
    char* aux = (char *)calloc(2000, sizeof(char));
   	strcpy(aux, directorio);
    strcpy(dir, directorio);
    strcat(dir, nombre);

    int archivo = open(dir, O_RDONLY);
    if(archivo == -1)
    {
    	perror(dir);
    	exit(EXIT_FAILURE);
    }
    struct stat sb;
    if(stat(dir, &sb) == -1)
    {
    	perror(dir);
    	exit(EXIT_FAILURE);
    }
   	long long longitud = (long long) sb.st_size;
   	char *contenido = (char *)calloc(longitud, sizeof(char));
   
   	if(read(archivo, contenido, longitud) == longitud)
   	{
   		printf("%s", contenido);
   	}
   	if(close(archivo) == -1)
   	{
   		perror(dir);
   		exit(EXIT_FAILURE);
   	}
   	free(contenido);
    strcpy(directorio, aux); 
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

double determinante(double **m, int n)
{  
	double det = 0, aux = 0;
    int c;
    // Si el orden es de 2, multiplica cruzadon directamente
    if(n==2)
        return m[0][0]*m[1][1] - m[1][0]*m[0][1];
    else
	{
		for(int j=0; j<n; j++)
		{
			// Crea arreglo dinamico temporal
			double **menor = (double **)malloc(sizeof(double)*(n-1));
			// Redimensiona
            for(int i=0; i<(n-1); i++) 
				menor[i] = (double *)malloc(sizeof(double)*(n-1));
            for(int k=1; k<n; k++)
			{
                c = 0;
                    for(int l=0; l<n; l++)
					{
                        if(l!=j)
						{
							/*Parte matriz principal en matrices de 3 
							y multiplica cruzado*/
                			menor[k-1][c] = m[k][l];
                            c++;
                        }
                    }
            }
        // Recursividad, repite la funcion
        aux = potencia(-1, 2+j)*m[0][j]*determinante(menor, n-1);
        det += aux;

        for(int x = 0; x<(n-1); x++)
            free(menor[x]); // Libera espacio en memoria     
        free(menor);
        }
    return det; // Devuelve resultado
    }
}

// Usando definicion de la adjunta
int inversa(double **A, double **resultado, int n)
{
	int tieneInversa;
	if(determinante(A, n) == 0)
	{
		tieneInversa=0;
		printf("La matriz no tiene inversa. Determinante = 0\n\n");
	}
	else
	{
		tieneInversa=1;
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
	return tieneInversa;
}

int potencia(int base, int pot)
{
	int i, resultado = 1;
	for(i = 0; i < pot; i++)
		resultado = base * resultado;

	return resultado;
}
