//Compilar: gcc 7_2.c -o padre

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "funciones.h"
#define TAM_MEM 27

int main(int argc, char *argv[])
{
	Sleep(10);
	STARTUPINFO siH;
	PROCESS_INFORMATION piH;
	char *argvH[2];
	ZeroMemory(&siH,sizeof(siH));
	siH.cb = sizeof(siH);
	ZeroMemory(&piH, sizeof(piH));
	argvH[0] = "C:\\Users\\YaKerTaker\\Google Drive\\5to SEMESTRE\\Sistemas-Operativos\\Practica6\\Windows\\hijo";
	argvH[1] = NULL;
	
	double **matriz1, **matriz2, **matriz3, **matriz4, **producto;
	int aux, suma;
	char *PH = "PH"; //padre hijo
	char *HP = "HP"; //hijo padre
	char *HN = "HN"; //hijo nieto
	HANDLE hArchMapeoPH, hArchMapeoHP, hArchMapeoHN;
	int i, j, k, shmid, n = 10;
	int *aPH, *aHP, *aHN;
	int *shmPH, *shmHP, *shmHN;

	matriz1 = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		matriz1[i] = (double*)calloc(n,sizeof(double));

	matriz2 = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		matriz2[i] = (double*)calloc(n,sizeof(double));

	matriz3 = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		matriz3[i] = (double*)calloc(n,sizeof(double));

	matriz4 = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		matriz4[i] = (double*)calloc(n,sizeof(double));

	producto = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		producto[i] = (double*)calloc(n,sizeof(double));

	if(!CreateProcess(NULL,argvH[0],NULL,NULL,FALSE,0,NULL,NULL,&siH,&piH))
	{
		printf("Fallo al invocar CreateProcess(%.i)\n",GetLastError());
		exit(-1);
	}
	srand(GetCurrentProcessId());
	
	//MANDA MATRIZ A NIETO
	printf("PADRE ENVIA 2 MATRICES. PADRE -> HIJO\n");
	if((hArchMapeoHN = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0, TAM_MEM, HN)) == NULL)
	{
		printf("No se mapeo la memoria compartida: (%i)\n",GetLastError());
		exit(-1);
	}	
	if((shmHN = (int *)MapViewOfFile(hArchMapeoHN,FILE_MAP_ALL_ACCESS,0,0,TAM_MEM)) == NULL)
	{
		printf("No se creo la memoria compartida: (%i)\n",GetLastError());
		CloseHandle(hArchMapeoHN);
		exit(-1);
	}
	aHN = shmHN;
	
	for(i = 0 ; i < 10 ; i++)
	{
		for(j = 0 ; j < 10 ; j++)
		{
			*aHN = rand()%11;
			matriz3[i][j] = *aHN;
			*aHN++;
		}
	}
	for(i = 0 ; i < 10 ; i++)
	{
		for(j = 0 ; j < 10 ; j++)
		{
			*aHN = rand()%11;
			matriz4[i][j] = *aHN;
			*aHN++;
		}
	}
	*aHN = 101;	
	while(*shmHN != -1)
		Sleep(1);

	printf("\nMatriz 3:\n");
	imprimir(matriz3, n);

	printf("\nMatriz 4:\n");
	imprimir(matriz4, n);

	UnmapViewOfFile(shmHN);
	CloseHandle(hArchMapeoHN);
		
	//RECIBE MATRIZ DEL PADRE
	printf("\nPADRE RECIBE 2 MATRICES. PADRE <- ABUELO\n");
	if((hArchMapeoPH = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,PH)) == NULL)
	{
		printf("No se abrio el archivo de mapeo de la memoria: (%i)\n", GetLastError());
		exit(-1);
	}
	if((shmPH = (int *)MapViewOfFile(hArchMapeoPH,FILE_MAP_ALL_ACCESS,0,0,TAM_MEM)) == NULL)
	{
		printf("No se accedio a la memoria compartida: (%i)\n", GetLastError());
		CloseHandle(hArchMapeoPH);
		exit(-1);
	}
	aPH = shmPH;
	for(i = 0 ; i < 10 ; i++)
	{
		for(j = 0 ; j < 10 ; j++)
		{
			matriz1[i][j] = *aPH;
			aPH++;
		}
	}
	for(i = 0 ; i < 10 ; i++)
	{
		for(j = 0 ; j < 10 ; j++)
		{
			matriz2[i][j] = *aPH;
			aPH++;
		}
	}
	*shmPH = -1;
		
	UnmapViewOfFile(shmPH);
	CloseHandle(hArchMapeoPH);

	//HACE EL PRODUCTO
	printf("PADRE REALIZA PRODUCTO DE 1 Y 2.\n");
	multiplicar(matriz1, matriz2, producto, n);


	//MANDA MATRIZ AL ABUELO
	printf("PADRE ENVIA PRODUCTO AL ABUELO. PADRE -> ABUELO. HIJO.\n");
	if((hArchMapeoHP = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0, TAM_MEM,HP)) == NULL)
	{
		printf("No se mapeo la memoria compartida: (%i)\n",GetLastError());
		exit(-1);
	}	
	if((shmHP = (int *)MapViewOfFile(hArchMapeoHP,FILE_MAP_ALL_ACCESS,0,0,TAM_MEM)) == NULL)
	{
		printf("No se creo la memoria compartida: (%i)\n",GetLastError());
		CloseHandle(hArchMapeoHP);
		exit(-1);
	}
	aHP = shmHP;
	for(i = 0 ; i < 10 ; i++)
	{
		for(j = 0 ; j < 10 ; j++)
		{
			*aHP = producto[i][j];
			*aHP++;
		}
	}

	*aHP = 101;	
	while(*shmHP != -1)
		Sleep(1);
	UnmapViewOfFile(shmHP);
	CloseHandle(hArchMapeoHP);
	CloseHandle(piH.hProcess);
	CloseHandle(piH.hThread);
	exit(0);//break;
}