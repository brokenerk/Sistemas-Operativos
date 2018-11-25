//Compilar: gcc 7_1.c -o 7
//Ejecutar: 7

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "funciones.h"
#define TAM_MEM 27

char* leerDirectorio()
{
	char* directorio = (char*)calloc(2000,sizeof(char));
	printf("Ingrese el nuevo directorio: ");
	scanf("%s", directorio);
	return directorio;
}

int main(void)
{
	// CREAR DIRECTORIO
	char* path = leerDirectorio();//Obtenemos el directorio desde la entrada de teclado
	if(!CreateDirectory(path, NULL))
	{
			perror(path);
	        exit(-1);
	}
	//Para crear el proceso
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	char *argv[2];
	ZeroMemory(&si,sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	argv[0] = "C:\\Users\\YaKerTaker\\Google Drive\\5to SEMESTRE\\Sistemas-Operativos\\Practica6\\Windows\\padre";
	argv[1] = NULL;
	double **mul, **suma, **matriz1, **matriz2, **inv1, **inv2;
	char *HP = "HP";//Padre hijo
	char *PH = "PH";//hijo padre
	char *NP = "NP";//nieto padre
	HANDLE hArchMapeoPH, hArchMapeoHP, hArchMapeoNP;//1, hArchMapeo2;
	int i, j, k, n = 10;
	int *aPH, *aHP, *aNP;
	int *shmPH, *shmHP, *shmNP;

	matriz1 = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		matriz1[i] = (double*)calloc(n,sizeof(double));

	matriz2 = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		matriz2[i] = (double*)calloc(n,sizeof(double));

	mul = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		mul[i] = (double*)calloc(n,sizeof(double));

	suma = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		suma[i] = (double*)calloc(n,sizeof(double));

	inv1 = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		inv1[i] = (double*)calloc(n,sizeof(double));

	inv2 = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		inv2[i] = (double*)calloc(n,sizeof(double));

	if(!CreateProcess(NULL,argv[0],NULL,NULL,FALSE,0,NULL,NULL,&si,&pi))
	{
		printf("Fallo al invocar CreateProcess(%i)\n",GetLastError());
		exit(-1);
	}
	srand(GetCurrentProcessId());
	//WaitForSingleObject(pi.hProcess,INFINITE);

	//MANDA 2 MATRICES A PADRE
	printf("ABUELO ENVIA 2 MATRICES. ABUELO -> PADRE\n");
	printf("Matriz 1:\n");
	llenar(matriz1, n);
	imprimir(matriz1, n);

	printf("\nMatriz 2:\n");
	llenar(matriz2, n);
	imprimir(matriz2, n);

	if((hArchMapeoPH = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0, TAM_MEM, PH)) == NULL)
	{
		printf("No se mapeo la memoria compartida: (%i)\n",GetLastError());
		exit(-1);
	}	
	if((shmPH = (int *)MapViewOfFile(hArchMapeoPH,FILE_MAP_ALL_ACCESS,0,0,TAM_MEM)) == NULL)
	{
		printf("No se creo la memoria compartida: (%i)\n",GetLastError());
		CloseHandle(hArchMapeoPH);
		exit(-1);
	}
	aPH = shmPH;
	
	for(i = 0 ; i < 10 ; i++)
	{
		for(j = 0 ; j < 10 ; j++)
		{
			*aPH = matriz1[i][j];
			*aPH++;
		}
	}
	for(i = 0 ; i < 10 ; i++)
	{
		for(j = 0 ; j < 10 ; j++)
		{
			*aPH = *aPH = matriz2[i][j];
			*aPH++;
		}
	}
	*aPH = 101;	
	while(*shmPH != -1)
		Sleep(1);
	UnmapViewOfFile(shmPH);
	CloseHandle(hArchMapeoPH);
		
	//RECIBE MATRIZ DEL HIJO
	printf("ABUELO RECIBE PRODUCTO. ABUELO <- PADRE\n\nProducto de 1 y 2:\n");
	if((hArchMapeoHP = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,HP)) == NULL)
	{
		printf("No se ario archsadfadsfdfdfdivo de mapeo de la memoria: (%i)\n", GetLastError());
		exit(-1);
	}
	if((shmHP = (int *)MapViewOfFile(hArchMapeoHP,FILE_MAP_ALL_ACCESS,0,0,TAM_MEM)) == NULL)
	{
		printf("No se accedio a la memoria compartida: (%i)\n", GetLastError());
		CloseHandle(hArchMapeoHP);
		exit(-1);
	}
	aHP = shmHP;
	for(i = 0 ; i < 10 ; i++)
	{
		for(j = 0 ; j < 10 ; j++)
		{
			mul[i][j] = *aHP++;
			//aHP++;
		}
	}
	*shmHP = -1;
	
	imprimir(mul, n);
	printf("\n");
	UnmapViewOfFile(shmHP);
	CloseHandle(hArchMapeoHP);
		
	//RECIBE MATRIZ DEL HIJO
	printf("ABUELO RECIBE SUMA. ABUELO <- HIJO\n\nSuma de 3 y 4:\n");
	if((hArchMapeoNP = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,NP)) == NULL)
	{
		printf("No se abrio el archivo de mapeo de la memoria: (%i)\n", GetLastError());
		exit(-1);
	}
	if((shmNP = (int *)MapViewOfFile(hArchMapeoNP,FILE_MAP_ALL_ACCESS,0,0,TAM_MEM)) == NULL)
	{
		printf("No se accedio a la memoria compartida: (%i)\n", GetLastError());
		CloseHandle(hArchMapeoNP);
		exit(-1);
	}
	aNP = shmNP;
	for(i = 0 ; i < 10 ; i++)
	{
		for(j = 0 ; j < 10 ; j++)
		{
			suma[i][j] = *aNP++;
		}
	}
	*shmNP = -1;

	imprimir(suma, n);
	printf("\n");

	UnmapViewOfFile(shmNP);
	CloseHandle(hArchMapeoNP);
		
	if(inversa(mul, inv1, n) != 0){
		crearArchivo(inv1, path, "inv_mul.txt");
		printf("Archivo de la inversa del producto escrito.... inv_mul.txt\n");
	}

	if(inversa(suma, inv2, n) != 0){
		crearArchivo(inv2, path, "inv_suma.txt");
		printf("Archivo de la inversa de la suma escrito.... inv_suma.txt\n");
	}
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return 0;
}