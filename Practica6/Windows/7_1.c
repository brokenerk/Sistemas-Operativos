#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "funciones.h"
#define TAM_MEM 27

int main(int argc, char const *dir[])
{
	char *path = (char*)calloc(2000, sizeof(char));
	strcpy(path, dir[1]);
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
	argv[0] = "C:\\Users\\YaKerTaker\\Google Drive\\5to SEMESTRE\\Sistemas-Operativos\\Practica6\\Windows\\hijo";
	argv[1] = NULL;
	double **mul, **suma, **matriz1, **matriz2, **inv1, **inv2;

	mul = (double**)calloc(10,sizeof(double*));
	for (int i = 0; i < 10; i++)
		mul[i] = (double*)calloc(10,sizeof(double));

	suma = (double**)calloc(10,sizeof(double*));
	for (int i = 0; i < 10; i++)
		suma[i] = (double*)calloc(10,sizeof(double));

	matriz1 = (double**)calloc(10,sizeof(double*));
	for (int i = 0; i < 10; i++)
		matriz1[i] = (double*)calloc(10,sizeof(double));

	matriz2 = (double**)calloc(10,sizeof(double*));
	for (int i = 0; i < 10; i++)
		matriz2[i] = (double*)calloc(10,sizeof(double));

	inv1 = (double**)calloc(10,sizeof(double*));
	for (int i = 0; i < 10; i++)
		inv1[i] = (double*)calloc(10,sizeof(double));

	inv2 = (double**)calloc(10,sizeof(double*));
	for (int i = 0; i < 10; i++)
		inv2[i] = (double*)calloc(10,sizeof(double));

	char *HP = "HP";//Padre hijo
	char *PH = "PH";//hijo padre
	char *NP = "NP";//nieto padre
	HANDLE hArchMapeoPH, hArchMapeoHP, hArchMapeoNP;//1, hArchMapeo2;
	int i, j, k;
	int *aPH, *aHP, *aNP;
	int *shmPH, *shmHP, *shmNP;
	
	if(!CreateProcess(NULL,argv[0],NULL,NULL,FALSE,0,NULL,NULL,&si,&pi))
	{
		printf("Fallo al invocar CreateProcess(%d)\n",GetLastError());
		exit(-1);
	}
	srand(GetCurrentProcessId());

	llenar(matriz1, 10);
	printf("\nMatriz 1.\n");
	imprimir(matriz1, 10);

	llenar(matriz2, 10);
	printf("Matriz 2\n");
	imprimir(matriz2, 10);

	//MANDA 2 MATRICES A HIJO
	printf("ENVIA 2 MATRICES. PADRE -> HIJO \n");
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
			*aPH = matriz2[i][j];
			*aPH++;
		}
	}
	*aPH = 101;	
	while(*shmPH != -1)
		Sleep(1);

	UnmapViewOfFile(shmPH);
	CloseHandle(hArchMapeoPH);
	Sleep(8);

	//RECIBE MATRIZ PRODUCTO DEL HIJO
	if((hArchMapeoHP = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,HP)) == NULL)
	{
		printf("No se abrio el archivo de mapeo de la memoria: (%i)\n", GetLastError());
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
		}
	}
	*shmHP = -1;
	printf("\nPRODUCTO matrices 1 y 2. HIJO -> PADRE. PADRE.\n");
	imprimir(mul, 10);
	printf("\n");
	UnmapViewOfFile(shmHP);
	CloseHandle(hArchMapeoHP);

	//RECIBE MATRIZ SUMA DEL NIETO
	if((hArchMapeoNP = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,NP)) == NULL)
	{
		printf("No se abrio PADRE archivo de mapeo de la memoria: (%i)\n", GetLastError());
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
	printf("\nSUMA matrices 3 y 4. NIETO -> PADRE. PADRE.\n");
	imprimir(suma, 10);
	printf("\n");

	UnmapViewOfFile(shmNP);
	CloseHandle(hArchMapeoNP);

	if(inversa(suma, inv2, 10) &&  inversa(mul, inv1, 10)!= 0) {
		crearArchivo(inv2, path, "inv2.txt");
		printf("Archivo inversa suma escrito.....\n");
		printf("Archivo inversa producto escrito.....\n"); 
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return 0;
}