#include <windows.h>
#include <stdio.h>
#include <time.h>
#include "funciones.h"
#define n 10
#define TAM_MEM 400

char* leerDirectorio();
void escribir(double  **A, float *p);
void leer(double  **A, float *p);
float *crearMemoria(char *idMem);
float *leerMemoria(char *idMem);
void proceso(char *name, int nivel);
HANDLE hSem[5];

void repetir(int i)
{
	srand(time(NULL));
	if(i == 0)
	{
		float *p = crearMemoria("mem");
		// ------------------------------------------- CREAR DOS MATRICES
		double **matriz1, **matriz2;

		// Inicializa las matrices.
		matriz1 = (double**)calloc(n,sizeof(double*));
		for (i = 0; i < n; i++)
			matriz1[i] = (double*)calloc(n,sizeof(double));

		matriz2 = (double**)calloc(n,sizeof(double*));
		for (i = 0; i < n; i++)
			matriz2[i] = (double*)calloc(n,sizeof(double));

		// Llena matriz 1 y matriz 2
		llenar(matriz1, n);
		llenar(matriz2, n);
		// IMPRIMO MATRICES
		printf("MATRIZ 1\n"); imprimir(matriz1, n);
		printf("MATRIZ 2\n"); imprimir(matriz2, n);

		//-------------------------------------------- ENVIA MATRICES 
		printf("Envia matriz 1\n\n");
		escribir(matriz1, p);
		ReleaseSemaphore(hSem[0], 1, NULL);
		WaitForSingleObject(hSem[1], INFINITE);
		
		printf("Envia matriz 2\n\n");
		escribir(matriz2, p);
		ReleaseSemaphore(hSem[0], 1, NULL);
		WaitForSingleObject(hSem[1], INFINITE);
		
		// ----------------------------------------- CREAR MATRIZ 
		double **mul;

		// Inicializa las matrices.
		mul = (double**)calloc(n,sizeof(double*));
		for (i = 0; i < n; i++)
			mul[i] = (double*)calloc(n,sizeof(double));

		// ----------------------------------------- RECIBE MATRIZ MULTIPLICACION
		printf("Recibe multiplicacion:\n");
		leer(mul, p);
		printf("RESULTADO DE LA MULTIPLICACION MATRIZ 1 Y MATRIZ 2\n"); 
		imprimir(mul, n);
		ReleaseSemaphore(hSem[0], 1, NULL);
		

		// ----------------------------------------- CREAR MATRIZ 
		double **suma;

		// Inicializa las matrices.
		suma = (double**)calloc(n,sizeof(double*));
		for (i = 0; i < n; i++)
			suma[i] = (double*)calloc(n,sizeof(double));
		
		//--------------------------- RECIBE MATRIZ SUMA
		WaitForSingleObject(hSem[4], INFINITE);
		printf("Recibe suma:\n");
		leer(suma, p);
		ReleaseSemaphore(hSem[0], 1, NULL);
		
		// IMPRIME ELEMENTOS DE LA SUMA 
		printf("RESULTADO DE LA SUMA DE LA MATRIZ A Y MATRIZ B\n"); 
		imprimir(suma, n);
		

		//--------------------------- CREAR DOS MATRICES
		double **invMul, **invSuma;
	
		// Inicializa las matrices.
		invMul = (double**)calloc(n,sizeof(double*));
		for (i = 0; i < n; i++)
			invMul[i] = (double*)calloc(n,sizeof(double));

		invSuma = (double**)calloc(n,sizeof(double*));
		for (i = 0; i < n; i++)
			invSuma[i] = (double*)calloc(n,sizeof(double));	

		//--------------------------- OBTIENE INVERSAS Y GENERA ARCHIVOS
		char* path = leerDirectorio();//Obtenemos el directorio desde la entrada de teclado
		if(!CreateDirectory(path, NULL))
		{
				perror(path);
		        exit(-1);
		}
	
		//Revisamos si la matriz tiene inversa
		if(inversa(mul, invMul, n) != 0) 
			crearArchivo(invMul, path, "inversa_Mul.txt");

		if(inversa(suma, invSuma, n) != 0) 
			crearArchivo(invSuma, path, "inversa_Suma.txt");	

		printf("INVERSA SUMA escrita.... Ok\n"); //imprimir(invSuma, n);
		printf("INVERSA MULTIPLICACION escrita... Ok\n"); //imprimir(invMul, n);

	}
	else if(i == 1)
	{
		float *p = leerMemoria("mem");
		//--------------------------- CREAR DOS MATRICES
		double **A, **B;
	
		// Inicializa las matrices.
		A = (double**)calloc(n,sizeof(double*));
		for (i = 0; i < n; i++)
			A[i] = (double*)calloc(n,sizeof(double));

		B = (double**)calloc(n,sizeof(double*));
		for (i = 0; i < n; i++)
			B[i] = (double*)calloc(n,sizeof(double));	

		//--------------------------- RECIBIR MATRICES 
		WaitForSingleObject(hSem[0], INFINITE);
		printf("Recibe matriz 1\n");
		leer(A, p);
		ReleaseSemaphore(hSem[1], 1, NULL);

		WaitForSingleObject(hSem[0], INFINITE);
		printf("Recibe matriz 2\n");
		leer(B, p);

		//--------------------------- CREAR MATRIZ 
		double **AB;

		// Inicializa las matrices.
		AB = (double**)calloc(n,sizeof(double*));
		for (i = 0; i < n; i++)
			AB[i] = (double*)calloc(n,sizeof(double));

		//--------------------------- CALCULA MULTIPLICACION
		printf("Multiplica matriz 1 y matriz 2\n");
		multiplicar(A, B, AB, n); 

		printf("Envia multiplicacion de matriz 1 y matriz 2\n\n");
		escribir(AB, p);
		ReleaseSemaphore(hSem[1], 1, NULL);
		WaitForSingleObject(hSem[0], INFINITE);

		//--------------------------- CREAR DOS MATRICES
		double **M1, **M2;
	
		// Inicializa las matrices.
		M1 = (double**)calloc(n,sizeof(double*));
		for (i = 0; i < n; i++)
			M1[i] = (double*)calloc(n,sizeof(double));

		M2 = (double**)calloc(n,sizeof(double*));
		for (i = 0; i < n; i++)
			M2[i] = (double*)calloc(n,sizeof(double));	

		// Llena matriz 1 y matriz 2
		llenar(M1, n);
		printf("MATRIZ A\n"); imprimir(M1, n);
		llenar(M2, n);
		printf("MATRIZ B\n"); imprimir(M2, n);

		//--------------------------- ENVIA MATRICES A SU HIJO
		printf("Envia matriz A\n\n");
		escribir(M1, p);
		ReleaseSemaphore(hSem[2], 1, NULL);
		WaitForSingleObject(hSem[3], INFINITE);
		
		printf("Envia matriz B\n\n");
		escribir(M2, p);
		ReleaseSemaphore(hSem[2], 1, NULL);
		WaitForSingleObject(hSem[3], INFINITE);
		
	}
	else if(i == 2)
	{
		float *p = leerMemoria("mem");
		//--------------------------- CREAR DOS MATRICES
		double **sumaA, **sumaB;
	
		// Inicializa las matrices.
		sumaA = (double**)calloc(n,sizeof(double*));
		for (i = 0; i < n; i++)
			sumaA[i] = (double*)calloc(n,sizeof(double));

		sumaB = (double**)calloc(n,sizeof(double*));
		for (i = 0; i < n; i++)
			sumaB[i] = (double*)calloc(n,sizeof(double));	

		//--------------------------- RECIBIR MATRICES 
		WaitForSingleObject(hSem[2], INFINITE);
		printf("Recibe matriz A\n");
		leer(sumaA, p);
		ReleaseSemaphore(hSem[3], 1, NULL);

		WaitForSingleObject(hSem[2], INFINITE);
		printf("Recibe matriz B\n");
		leer(sumaB, p);

		//--------------------------- CREAR MATRIZ 
		double **sumaAB;

		// Inicializa las matrices.
		sumaAB = (double**)calloc(n,sizeof(double*));
		for (i = 0; i < n; i++)
			sumaAB[i] = (double*)calloc(n,sizeof(double));

		//--------------------------- CALCULA LA SUMA
		sumar(sumaA, sumaB, sumaAB, n);

		printf("Envia suma C+D\n\n");
		escribir(sumaAB, p);
		ReleaseSemaphore(hSem[4], 1, NULL);
		WaitForSingleObject(hSem[0], INFINITE);
		ReleaseSemaphore(hSem[3], 1, NULL);
	}
}

void crearSems(int nivel)
{
	int i;
	for(i = 0; i < 5; ++i){
		char name[100];
		sprintf(name, "sem%d", i);
		if(nivel == 0) hSem[i] = CreateSemaphore(NULL, 0, 1, name);
		else hSem[i] = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, name);
	}
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	int nivel = 0; //0-padre, 1-hijo, 2-nieto
	if(argc > 1) sscanf(argv[1], "%d", &nivel);
	crearSems(nivel);
	if(nivel < 2) proceso(argv[0], nivel + 1);
	repetir(nivel);
	return 0;
}


char* leerDirectorio()
{
	char* directorio = (char*)calloc(2000,sizeof(char));
	printf("Ingrese el nuevo directorio: ");
	scanf("%s", directorio);
	return directorio;
}

void escribir(double  **A, float *p)
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
			*p++ = A[i][j];
	}
}

void leer(double  **A, float *p)
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
			A[i][j] = *p++;
	}
}

float *crearMemoria(char *idMem)
{
	HANDLE hMem = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, TAM_MEM, idMem);
	return MapViewOfFile(hMem, FILE_MAP_ALL_ACCESS, 0, 0, TAM_MEM);
}

float *leerMemoria(char *idMem)
{
	HANDLE hMem = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, idMem);
	return MapViewOfFile(hMem, FILE_MAP_ALL_ACCESS, 0, 0, TAM_MEM);
}

void proceso(char *name, int nivel)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	char args[100];
	sprintf(args, "%s %d", name, nivel);
	CreateProcess(NULL, args, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
}
