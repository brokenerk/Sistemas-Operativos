//	Compilación:
//	gcc tiempo.c -c
//	gcc operacionesMatrices.c tiempo.o -o o
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

int main(int argc, char const *argv[])
{
	clock_t tiempo_inicio, tiempo_final;
	double segundos;

	tiempo_inicio = clock();
	int i, n;
	double **matriz1, **matriz2, **suma, **resta, **mul, **tran1, **tran2, **inv1, **inv2;
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
	
	suma = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		suma[i] = (double*)calloc(n,sizeof(double));

	resta = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		resta[i] = (double*)calloc(n,sizeof(double));

	mul = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		mul[i] = (double*)calloc(n,sizeof(double));

	tran1 = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		tran1[i] = (double*)calloc(n,sizeof(double));

	tran2 = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		tran2[i] = (double*)calloc(n,sizeof(double));
	
	inv1 = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		inv1[i] = (double*)calloc(n,sizeof(double));

	inv2 = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		inv2[i] = (double*)calloc(n,sizeof(double));

	char* path = (char*)calloc(2000,sizeof(char));
	strcpy(path, "C:\\Users\\YaKerTaker\\Google Drive\\5to SEMESTRE\\Sistemas-Operativos\\Practica4\\Windows\\8\\Resultados0");

	// Llena matriz 1 y matriz 2
	llenar(matriz1, n);
	llenar(matriz2, n);

	printf("MATRIZ 1\n"); imprimir(matriz1, n);
	printf("MATRIZ 2\n"); imprimir(matriz2, n);

	//LOS ARCHIVOS NO DEBEN EXISTIR, SINO ARROJARA ERROR Y NO ESCRIBIRA NADA

	printf("SUMA\n"); sumar(matriz1, matriz2, suma, n); 
	crearArchivo(suma, path, "suma.txt");

	printf("RESTA\n"); restar(matriz1, matriz2, resta, n); 
	crearArchivo(resta, path, "resta.txt");

	printf("MULTIPLICAR\n"); multiplicar(matriz1, matriz2, mul, n); 
	crearArchivo(mul, path, "multiplicacion.txt");
	
	printf("TRANSPUESTA MATRIZ 1\n"); transpuesta(matriz1, tran1, n); 
	crearArchivo(tran1, path, "transpuesta_1.txt");

	printf("TRANSPUESTA MATRIZ 2\n"); transpuesta(matriz2, tran2, n); 
	crearArchivo(tran2, path, "transpuesta_2.txt");

	printf("INVERSA MATRIZ 1\n"); 
	//Revisamos si la maztriz tiene inversa
	if(inversa(matriz1, inv1, n) != 0) 
		crearArchivo(inv1, path, "inversa_1.txt");

	printf("INVERSA MATRIZ 2\n"); 
	if(inversa(matriz2, inv2, n) != 0) 
		crearArchivo(inv2, path, "inversa_2.txt");

	printf(" ----------------------------------\n");
    printf(" ----------- RESULTADOS -----------\n");
    printf(" ----------------------------------\n");
    
    printf("SUMA\n"); imprimirArchivo(path, "suma.txt");
    printf("\nRESTA\n"); imprimirArchivo(path, "resta.txt");
    printf("\nMULTIPLICAR\n"); imprimirArchivo(path, "multiplicacion.txt");
    printf("\nTRANSPUESTA MATRIZ 1\n"); imprimirArchivo(path, "transpuesta_1.txt");
    printf("\nTRANSPUESTA MATRIZ 2\n"); imprimirArchivo(path, "transpuesta_2.txt");
    printf("\nINVERSA MATRIZ 1\n"); imprimirArchivo(path, "inversa_1.txt");
    printf("\nINVERSA MATRIZ 2\n"); imprimirArchivo(path, "inversa_2.txt");


	clock_t end = clock();
	float seconds = (float)(end - start) / CLOCKS_PER_SEC;;
	printf("Tiempo de ejecucion: %f\n", seconds);
	

    tiempo_final = clock();
    segundos = (double)(tiempo_final - tiempo_inicio) / CLOCKS_PER_SEC;
    //Cálculo del tiempo de ejecución del programa
	printf("\n\nTiempo ejecucion:  %.4f s\n",  segundos);

	return 0;
}

void crearArchivo(double **res, char* dir, char *nombre)
{
    int i,j;
    char num[15];
    char *name = (char *)calloc(150,sizeof(char));
	strcpy(name, nombre);
	char *ruta = (char *)calloc(150,sizeof(char));
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
    			perror(ruta);
        		exit(EXIT_FAILURE);
    		}
    	}
	    //Llamada al sistema CloseHandle recibe un descriptor de archivo y retorna un valor cero si han habido errores
	    if(CloseHandle(h) == 0)
	    {
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
