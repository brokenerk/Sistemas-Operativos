#include <windows.h>
#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

// Declaracion de funciones
int potencia(int base, int pot);
void imprimir(double **m, int n);
void llenar(double **m, int n);
void sumar(double **m1, double **m2, double **resultado, int n);
void restar(double **m1, double **m2, double **resultado, int n);
void multiplicar(double **m1, double **m2, double **resultado, int n);
void transpuesta(double **m, double **resultado, int n);
int inversa(double **matriz, double **resultado, int n);
double determinante(double **matriz, int n);
void crearArchivo(double **res, char* dir, char *nombre);
void imprimirArchivo(char *directorio, char *nombre);

void crearArchivo(double **res, char* dir, char *nombre)
{
    int i,j;
    char num[20];
    char *name = (char *)calloc(200,sizeof(char));
	strcpy(name, nombre);
	char *ruta = (char *)calloc(200,sizeof(char));
	// Contatenamos la ruta original con el nombre del archivo
	strcat(strcat(strcpy(ruta, dir), "\\"), name);

    HANDLE h = CreateFile(ruta,						//ruta del archivo
						GENERIC_WRITE,			//abrir para escribir
						0,						//no compartir
						NULL,						// seguridad por default
						CREATE_ALWAYS,				//crear siempre
						FILE_ATTRIBUTE_TEMPORARY,	//archivo normal
						NULL);					//sin tributos

    if (h == INVALID_HANDLE_VALUE)
    {
    	printf("error1\n");
    	perror(ruta);
        exit(EXIT_FAILURE);
    }
    else
    {
    	DWORD bytesEscritos = 0;

		for(i=0 ; i<10 ; i++) // Escribimos 5 veces el texto en el archivo
		{
			for(j=0 ; j<10 ; j++) // Escribimos 5 veces el texto en el archivo
			{
				sprintf(num, "%.3f\t", res[i][j]);
		        /*Funcion WrifeFile recibe los parametros a continuacion y devuelve un true si no existieron errores*/
				BOOL escribir = WriteFile( 
		                    h,           				// abrir handle del archivo
		                    num,      					// informacion a escribir
		                    (DWORD)strlen(num),  		// tamaño de bytes a escribir
		                    &bytesEscritos, 			// tamaño de bytes escrit
		                    NULL);           			// no overlapped structure

				if(!escribir)
    			{
    				printf("erro2\n");
    				perror(ruta);
        			exit(EXIT_FAILURE);
    			}
    		}
    		BOOL espacio = WriteFile( 
		                    h,           				// abrir handle del archivo
		                    "\n",      					// informacion a escribir
		                    (DWORD)strlen("\n"),  		// tamaño de bytes a escribir
		                    &bytesEscritos, 			// tamaño de bytes escrit
		                    NULL);           			// no overlapped structure
			if(!espacio)
    		{
    			printf("erro2\n");
    			perror(ruta);
        		exit(EXIT_FAILURE);
    		}
    	}
	    //Llamada al sistema CloseHandle recibe un descriptor de archivo y retorna un valor cero si han habido errores
	    if(CloseHandle(h) == 0)
	    {
	    	printf("erro3\n");
	    	perror(ruta);
	    	exit(EXIT_FAILURE);
	    }
	}
}

void imprimirArchivo(char *directorio, char *nombre)
{
	char *name = (char *)calloc(150,sizeof(char));
	strcpy(name, nombre);
	char *dir = (char *)calloc(150,sizeof(char));
	// Contatenamos la ruta original con el nombre del archivo
	strcat(strcat(strcpy(dir, directorio), "\\"), name);

	HANDLE file;
	DWORD BytesEscritos = 0;
	char *contenido = (char*)calloc(1000000,sizeof(char));
	file = CreateFile(
	         dir,
	         GENERIC_WRITE | GENERIC_READ,
	         FILE_SHARE_READ,
	         NULL,
	         OPEN_EXISTING,
	         FILE_ATTRIBUTE_NORMAL,
	         NULL);

	if(file == INVALID_HANDLE_VALUE)
	{
		printf("Error 1\n");
	    perror(dir);
	    exit(EXIT_FAILURE);
	}
	else
	{
		if(ReadFile(file, contenido, 1000000, &BytesEscritos, NULL))
	    {
	      printf("%s", contenido);
	    }
	    free(contenido);

	    if(CloseHandle(file) == 0)
	    {
	      perror(dir);
	      exit(EXIT_FAILURE);
	    }
	  }
	free(name);
	free(dir);
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
    int c, i, j, k, l, x;
    //Si el orden es de 2, multiplica cruzadon directamente
    if(n==2)
        return m[0][0]*m[1][1] - m[1][0]*m[0][1];
    else
	{
		for(j=0; j<n; j++)
		{
			//Crea arreglo dinamico temporal
			double **menor = (double **)malloc(sizeof(double)*(n-1));
			//Redimensiona
            for(i=0; i<(n-1); i++) 
				menor[i] = (double *)malloc(sizeof(double)*(n-1));
            for(k=1; k<n; k++)
			{
                c = 0;
                    for(l=0; l<n; l++)
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
        //Recursividad, repite la funcion
        aux = potencia(-1, 2+j)*m[0][j]*determinante(menor, n-1);
        det += aux;

        for(x = 0; x<(n-1); x++)
            free(menor[x]);//Libera espacio en memoria     
        free(menor);
        }
    return det;//Devuelve resultado
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
	else{
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
