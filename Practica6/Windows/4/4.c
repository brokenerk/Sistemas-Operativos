#include <windows.h>
#include <stdio.h>
#include <time.h>
#include "funciones.h"
#define n 10

char* leerDirectorio();
HANDLE proceso(char *name, HANDLE hRead, int nivel);
void crearTuberia(HANDLE *hRead, HANDLE *hWrite);
void escribir(double  **A, HANDLE hWrite);
void leer(double **A, HANDLE hRead);

int main(int argc, char *argv[])
{
	int i, j, k, l, m, o, p;	
	srand(time(NULL));
	int nivel = 0; // 0-PADRE, 1-HIJO, 2-NIETO
	HANDLE hRead, hWrite;

	if(argc > 1)
		sscanf(argv[1], "%d", &nivel);
	if(nivel == 0)	// PADRE
	{ 
		crearTuberia(&hRead, &hWrite);				
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

		//-------------------------------------------- ENVIA MATRICES A SU HIJO
		printf(" --> Soy el PADRE y envio la matriz 1 a mi HIJO.\n\n");
		escribir(matriz1, hWrite);
		printf(" --> Soy el PADRE y envio la matriz 2 a mi HIJO.\n\n");
		escribir(matriz2, hWrite);
		WriteFile(hWrite, &hWrite, sizeof(HANDLE), NULL, NULL);
		HANDLE hProc = proceso(argv[0], hRead, 1);
		WaitForSingleObject(hProc, INFINITE);

		// ----------------------------------------- CREAR MATRIZ 
		double **mul;

		// Inicializa las matrices.
		mul = (double**)calloc(n,sizeof(double*));
		for (i = 0; i < n; i++)
			mul[i] = (double*)calloc(n,sizeof(double));

		// IMPRIMO MATRICES
		printf("MATRIZ 1\n"); imprimir(matriz1, n);
		printf("MATRIZ 2\n"); imprimir(matriz2, n);
		
		// ----------------------------------------- RECIBE MATRIZ MULTIPLICACION
		leer(mul, hRead);
		printf(" --> Soy el PADRE y recibi la multiplicacion de mi HIJO.\n");
		printf("RESULTADO DE LA MULTIPLICACION MATRIZ 1 Y MATRIZ 2\n"); imprimir(mul, n);
		
		//--------------------------- CREAR MATRIZ 
		double **suma;

		// Inicializa las matrices.
		suma = (double**)calloc(n,sizeof(double*));
		for (i = 0; i < n; i++)
			suma[i] = (double*)calloc(n,sizeof(double));

		//--------------------------- RECIBE MATRIZ SUMA
		
		printf(" --> Soy el PADRE y recibi la suma de mi NIETO.\n");
		leer(suma, hRead);
		
		// IMPRIME ELEMENTOS DE LA SUMA 
		printf("RESULTADO DE LA SUMA DE LA MATRIZ A Y MATRIZ B\n"); imprimir(suma, n);
		
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
	
		printf(" --> Soy el PADRE y estoy sacando inversa y haciendo archivos\n");
		//Revisamos si la matriz tiene inversa
		if(inversa(mul, invMul, n) != 0) 
			crearArchivo(invMul, path, "inversa_Mul.txt");

		if(inversa(suma, invSuma, n) != 0) 
			crearArchivo(invSuma, path, "inversa_Suma.txt");	

		printf("INVERSA SUMA\n"); imprimir(invSuma, n);
		printf("INVERSA MULTIPLICACION\n"); imprimir(invMul, n);
	}
	else if(nivel == 1)	// HIJO
	{ 
		hRead = GetStdHandle(STD_INPUT_HANDLE);
		
		//--------------------------- CREAR DOS MATRICES
		double **A, **B;
	
		// Inicializa las matrices.
		A = (double**)calloc(n,sizeof(double*));
		for (i = 0; i < n; i++)
			A[i] = (double*)calloc(n,sizeof(double));

		B = (double**)calloc(n,sizeof(double*));
		for (i = 0; i < n; i++)
			B[i] = (double*)calloc(n,sizeof(double));	

		//--------------------------- RECIBIR MATRICES DEL PADRE
		printf(" --> Soy el HIJO y recibi matriz 1 de mi PADRE.\n");
		leer(A, hRead);
		printf(" --> Soy el HIJO y recibi matriz 2 de mi PADRE.\n");
		leer(B, hRead);

		//--------------------------- CREAR MATRIZ 
		double **AB;

		// Inicializa las matrices.
		AB = (double**)calloc(n,sizeof(double*));
		for (i = 0; i < n; i++)
			AB[i] = (double*)calloc(n,sizeof(double));

		//--------------------------- CALCULA MULTIPLICACION
		printf("Soy el HIJO y estoy multiplicando matriz 1 y 2\n");
		multiplicar(A, B, AB, n); 
		imprimir(AB, n);
		ReadFile(hRead, &hWrite, sizeof(HANDLE), NULL, NULL);
		escribir(AB, hWrite);

		// ------------------------- CREA TUBERÍA
		HANDLE hRead2, hWrite2;
		crearTuberia(&hRead2, &hWrite2);

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
		llenar(M2, n);
	
		//--------------------------- ENVIA MATRICES A SU HIJO
		printf(" --> Soy el HIJO y envio matriz A al NIETO.\n\n");
		escribir(M1, hWrite2);
		printf(" --> Soy el HIJO y envio matriz B al NIETO.\n\n");
		escribir(M2, hWrite2);
		printf("MATRIZ A\n"); imprimir(M1, n);
		printf("MATRIZ B\n"); imprimir(M2, n);
		
		WriteFile(hWrite2, &hWrite, sizeof(HANDLE), NULL, NULL);
		HANDLE hProc = proceso(argv[0], hRead2, 2);
		WaitForSingleObject(hProc, INFINITE);
	}
	else if(nivel == 2)	// NIETO
	{
		hRead = GetStdHandle(STD_INPUT_HANDLE);

		//--------------------------- CREAR DOS MATRICES
		double **sumaA, **sumaB;
	
		// Inicializa las matrices.
		sumaA = (double**)calloc(n,sizeof(double*));
		for (i = 0; i < n; i++)
			sumaA[i] = (double*)calloc(n,sizeof(double));

		sumaB = (double**)calloc(n,sizeof(double*));
		for (i = 0; i < n; i++)
			sumaB[i] = (double*)calloc(n,sizeof(double));	

		//--------------------------- RECIBIR MATRICES DEL PADRE
		printf(" --> Soy el NIETO y recibo matriz A del HIJO.\n");
		leer(sumaA, hRead);
		printf(" --> Soy el NIETO y recibo matriz B del HIJO.\n");
		leer(sumaB, hRead);
		ReadFile(hRead, &hWrite, sizeof(HANDLE), NULL, NULL);
		
		//--------------------------- CREAR MATRIZ 
		double **sumaAB;

		// Inicializa las matrices.
		sumaAB = (double**)calloc(n,sizeof(double*));
		for (i = 0; i < n; i++)
			sumaAB[i] = (double*)calloc(n,sizeof(double));

		//--------------------------- CALCULA LA SUMA
		printf(" --> Soy el NIETO y estoy sumando matriz A y B\n");
		sumar(sumaA, sumaB, sumaAB, n);
		escribir(sumaAB, hWrite);
	}
	return 0;
}

// ------------------------------------------------------------------------------
//									FUNCIONES
// ------------------------------------------------------------------------------

char* leerDirectorio()
{
	char* directorio = (char*)calloc(2000,sizeof(char));
	printf("Ingrese el nuevo directorio: ");
	scanf("%s", directorio);
	return directorio;
}

HANDLE proceso(char *name, HANDLE hRead, int nivel)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(pi));
	ZeroMemory(&si, sizeof(si));
	GetStartupInfo(&si);
	si.hStdInput = hRead;
	si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
	si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	si.dwFlags = STARTF_USESTDHANDLES;
	si.cb = sizeof(si);
	char args[100];
	sprintf(args, "%s %d", name, nivel);
	CreateProcess(NULL, args, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
	return pi.hProcess;
}

void crearTuberia(HANDLE *hRead, HANDLE *hWrite)
{
	SECURITY_ATTRIBUTES pipeSeg = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};
	CreatePipe(hRead, hWrite, &pipeSeg, 0);
}

void escribir(double  **A, HANDLE hWrite)
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
			WriteFile(hWrite, &A[i][j], sizeof(double), NULL, NULL);
	}
}

void leer(double **A, HANDLE hRead)
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
			ReadFile(hRead, &A[i][j], sizeof(double), NULL, NULL);
	}
}
