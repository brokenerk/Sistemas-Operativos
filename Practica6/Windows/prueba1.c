#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "funciones.h"
#define TAM_MEM 27

int main(void)
{
	//Para crear el proceso
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	char *argv[2];
	ZeroMemory(&si,sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	argv[0] = "C:\\Users\\YaKerTaker\\Google Drive\\5to SEMESTRE\\Sistemas-Operativos\\Practica6\\Windows\\prueba2";
	argv[1] = NULL;
	double A[10][10], B[10][10], mandada1[10][10], mandada2[10][10];
	char *HP = "HP";//Padre hijo
	char *PH = "PH";//hijo padre
	char *NP = "NP";//nieto padre
	HANDLE hArchMapeoPH, hArchMapeoHP, hArchMapeoNP;//1, hArchMapeo2;
	int i, j, k;
	int *aPH, *aHP, *aNP;
	int *shmPH, *shmHP, *shmNP;
	
	if(!CreateProcess(NULL,argv[0],NULL,NULL,FALSE,0,NULL,NULL,&si,&pi))
	{
		printf("Fallo al invocar CreateProcess(%i)\n",GetLastError());
		exit(-1);
	}
	srand(GetCurrentProcessId());
	//WaitForSingleObject(pi.hProcess,INFINITE);
	//MANDA 2 MATRICES A HIJO
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
					*aPH = rand()%15;
					mandada1[i][j] = *aPH;
					*aPH++;
				}
			}
			for(i = 0 ; i < 10 ; i++)
			{
				for(j = 0 ; j < 10 ; j++)
				{
					*aPH = rand()%15;
					mandada2[i][j] = *aPH;
					*aPH++;
				}
			}
		*aPH = 101;	
		while(*shmPH != -1)
			Sleep(1);
		printf("2 MATRICES. PADRE -> HIJO. PADRE.\nMatriz 1.\n");
		//imprimir(mandada1, 10);
		printf("Matriz 2\n");
		for(i = 0 ; i < 10 ; i++)
		{
			for(j = 0 ; j < 10 ; j++)
			{
				printf("%.3f\t",mandada2[i][j]);
			}
			printf("\n");
		}
		UnmapViewOfFile(shmPH);
		CloseHandle(hArchMapeoPH);
		
//RECIBE MATRIZ DEL HIJO
	
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
					A[i][j] = *aHP++;
					//aHP++;
				}
			}
		*shmHP = -1;
		printf("PRODUCTO. HIJO -> PADRE. PADRE.\n");
		for(i = 0 ; i < 10 ; i++)
		{
			for(j = 0 ; j < 10 ; j++)
			{
				printf("%.3f\t",A[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		UnmapViewOfFile(shmHP);
		CloseHandle(hArchMapeoHP);
		
	//RECIBE MATRIZ DEL NIETO
		
if((hArchMapeoNP = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,NP)) == NULL)
		{
			printf("No se ario PADRE archivo de mapeo de la memoria: (%i)\n", GetLastError());
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
					B[i][j] = *aNP++;
				}
			}
		*shmNP = -1;
		printf("SUMA. NIETO -> PADRE. PADRE.\n");
		for(i = 0 ; i < 10 ; i++)
		{
			for(j = 0 ; j < 10 ; j++)
			{
				printf("%.3f\t",B[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		UnmapViewOfFile(shmNP);
		CloseHandle(hArchMapeoNP);
		//invMat(A,B);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return 0;
}