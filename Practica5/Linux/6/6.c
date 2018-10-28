//	Compilación:
//	gcc tiempo.c -c
//	gcc 6.c tiempo.o -lpthread -o 6

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
#include <pthread.h>
#include "funciones.h"
#define n 10

void *hilo(void *arg);
char* leerDirectorio();

// CREAR DIRECTORIO
// Obtenemos el directorio desde la entrada de teclado
char* path; 
double **matriz1, **matriz2, **suma, **resta, **mul, **tran1, **tran2, **inv1, **inv2;

int main(int argc, char const *argv[])
{	
	//Variables para medición de tiempos
	double utime0, stime0, wtime0,utime1, stime1, wtime1; 
	uswtime(&utime0, &stime0, &wtime0);

	int i;
	time_t t;
	srand((unsigned) time(&t));
	//n = 10; // Tam de la matriz cuadrada
	path = leerDirectorio();
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

	
	// Llamda al sistema mkdir recibe la ruta del directorio a crear, 
	// y los permisos de escritura, lectura y ejecucion para cada tipo de usuario
	// Retorna -1 si ocurrieron errores
	if(mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) ==-1)
	{
		perror(path);
        exit(EXIT_FAILURE);
    }
    else
    {
    	pthread_t id_hilos[7];

    	// Llena matriz 1 y matriz 2
		llenar(matriz1, n); llenar(matriz2, n);

		printf("MATRIZ 1\n"); imprimir(matriz1, n);
		printf("MATRIZ 2\n"); imprimir(matriz2, n);

		for(i = 0; i<5; i++)
		{
			int *opcion = malloc(sizeof(int));
			*opcion = i;
			pthread_create (&id_hilos[i], NULL, hilo, (void*)opcion);
		}
		for(i = 0; i<5; i++)
		{
			pthread_join (id_hilos[i], NULL);
		}

		int *opc = malloc(sizeof(int));
		*opc = 5;
		pthread_create (&id_hilos[5], NULL, hilo, (void*)opc);
		pthread_join (id_hilos[5], NULL);
			
    }  
    uswtime(&utime1, &stime1, &wtime1);

	//Cálculo del tiempo de ejecución del programa
	printf("\n\nTiempo ejecucion:  %.4f s\n",  wtime1 - wtime0);

	return 0;
}
void *hilo(void *arg)
{
	int i = *((int*)arg);
	if(i == 0)
	{
		// HILO SUMA
		printf("----------- Soy el hilo calculando la SUMA\n");
		sumar(matriz1, matriz2, suma, n);
		crearArchivo(suma, n, "/suma.txt", path);
	}	
	if(i == 1)
	{
		// HILO RESTA
		printf("------------ Soy el hilo calculando la RESTA\n");
		restar(matriz1, matriz2, resta, n);
		crearArchivo(resta, n, "/resta.txt", path);
	}
	if(i == 2)
	{
		// HILO MULTIPLICACION
		printf("----------- Soy el hilo calculando la MULTIPLICACION\n");
		multiplicar(matriz1, matriz2, mul, n);
		crearArchivo(mul, n, "/mul.txt", path);
	}
	if(i == 3)
	{
		// HILO TRANSPUESTA
		printf("--------- Soy el hilo calculando la TRANSPUESTA\n");
		transpuesta(matriz1, tran1, n);
		crearArchivo(tran1, n, "/tran1.txt", path);
		
		transpuesta(matriz2, tran2, n);
		crearArchivo(tran2, n, "/tran2.txt", path);
	}
	if(i == 4)
	{
		// HILO INVERSA
		printf("--------- Soy el hilo calculando la INVERSA\n");
		
		//Revisamos si la maztriz tiene inversa
		if(inversa(matriz1, inv1, n) != 0) 
			crearArchivo(inv1, n, "/inversa_1.txt", path);

		if(inversa(matriz2, inv2, n) != 0) 
			crearArchivo(inv2, n, "/inversa_2.txt", path);
	}
	if(i == 5)
	{
		printf(" -------------------------------------\n");
		printf(" -- Soy el hilo leeyendo RESULTADOS --\n");
		printf(" -------------------------------------\n");
			
		printf("SUMA\n"); imprimirArchivo(path, "/suma.txt");
		printf("\nRESTA\n"); imprimirArchivo(path, "/resta.txt");
		printf("\nMULTIPLICAR\n"); imprimirArchivo(path, "/mul.txt");
		printf("\nTRANSPUESTA MATRIZ 1\n"); imprimirArchivo(path, "/tran1.txt");
		printf("\nTRANSPUESTA MATRIZ 2\n"); imprimirArchivo(path, "/tran2.txt");
		printf("\nINVERSA MATRIZ 1\n"); imprimirArchivo(path, "/inversa_1.txt");
		printf("\nINVERSA MATRIZ 2\n"); imprimirArchivo(path, "/inversa_2.txt");
	}
}


char* leerDirectorio()
{
	char* directorio = (char*)calloc(2000,sizeof(char));
	printf("Ingrese el nuevo directorio: ");
	scanf("%s", directorio);
	return directorio;
}