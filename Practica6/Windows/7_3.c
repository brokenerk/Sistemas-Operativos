//Compilar: gcc 7_3.c -o hijo

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "funciones.h"
#define TAM_MEM 27

int main(int argc, char *argv[])
{
	int i, j, k, shmid, n = 10;
	double **matriz3, **matriz4, **suma;
	matriz3 = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		matriz3[i] = (double*)calloc(n,sizeof(double));

	matriz4 = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		matriz4[i] = (double*)calloc(n,sizeof(double));

	suma = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		suma[i] = (double*)calloc(n,sizeof(double));

	char *NP = "NP";
	char *HN = "HN";
	HANDLE hArchMapeoNP, hArchMapeoHN;
	
	int *aHN, *aNP;
	int *shmNP, *shmHN;
	//RECIBE MATRIZ DEL PADRE
	printf("\nHIJO RECIBE 2 MATRICES. HIJO <- PADRE\n");
	if((hArchMapeoHN = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,HN)) == NULL)
	{
		printf("No se abrio el archivo de mapeo de la memoria: (%i)\n", GetLastError());
		exit(-1);
	}
	if((shmHN = (int *)MapViewOfFile(hArchMapeoHN,FILE_MAP_ALL_ACCESS,0,0,TAM_MEM)) == NULL)
	{
		printf("No se accedio a la memoria compartida: (%i)\n", GetLastError());
		CloseHandle(hArchMapeoHN);
		exit(-1);
	}
	aHN = shmHN;
	for(i = 0 ; i < 10 ; i++)
	{
		for(j = 0 ; j < 10 ; j++)
		{
			matriz3[i][j] = *aHN;
			aHN++;
		}
	}
	for(i = 0 ; i < 10 ; i++)
	{
		for(j = 0 ; j < 10 ; j++)
		{
			matriz4[i][j] = *aHN;
			aHN++;
		}
	}
	*shmHN = -1;
	UnmapViewOfFile(shmHN);
	CloseHandle(hArchMapeoHN);
	printf("HIJO REALIZA LA SUMA DE 3 Y 4.\n");
	sumar(matriz3, matriz4, suma, n);

	//MANDA MATRIZ AL ABUELO
	printf("HIJO ENVIA SUMA AL ABUELO. HIJO -> ABUELO\n");
	if((hArchMapeoNP = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0, TAM_MEM, NP)) == NULL)
	{
		printf("No se mapeo la memoria compartida: (%i)\n",GetLastError());
		exit(-1);
	}	
	if((shmNP = (int *)MapViewOfFile(hArchMapeoNP,FILE_MAP_ALL_ACCESS,0,0,TAM_MEM)) == NULL)
	{
		printf("No se creo la memoria compartida: (%i)\n",GetLastError());
		CloseHandle(hArchMapeoNP);
		exit(-1);
	}
	aNP = shmNP;
	for(i = 0 ; i < 10 ; i++)
	{
		for(j = 0 ; j < 10 ; j++)
		{
			*aNP = suma[i][j];
			*aNP++;
		}
	}

	*aNP = 101;	
	while(*shmNP != -1)
		Sleep(1);
	UnmapViewOfFile(shmNP);
	CloseHandle(hArchMapeoNP);
		
	exit(0);
}