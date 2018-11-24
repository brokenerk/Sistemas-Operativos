#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "funciones.h"
#define TAM_MEM 27

int main(int argc, char *argv[])
{
	double A[10][10], B[10][10],b[10][10], suma[10][10];
	char *NP = "NP";
	char *HN = "HN";
	HANDLE hArchMapeoNP, hArchMapeoHN;
	int i, j, k, shmid;
	int *aHN, *aNP;
	int *shmNP, *shmHN;
	//RECIBE MATRIZ DEL HIJO
	if((hArchMapeoHN = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,HN)) == NULL)
		{
			printf("No se ario archivode mapeo de la memoria: (%i)\n", GetLastError());
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
					A[i][j] = *aHN;
					aHN++;
				}
			}
			for(i = 0 ; i < 10 ; i++)
			{
				for(j = 0 ; j < 10 ; j++)
				{
					B[i][j] = *aHN;
					aHN++;
				}
			}
		*shmHN = -1;
		printf("2 MATRICES. HIJO -> NIETO. NIETO.\nMatriz 1\n");
		
		printf("Matriz 2\n");
		

		UnmapViewOfFile(shmHN);
		CloseHandle(hArchMapeoHN);
//HACE LA SUMA
		for(i=0;i<10;i++)  
	{
		for(j=0;j<10;j++) 
		{
			suma[i][j]=A[i][j]+B[i][j];
		}
	}



//MANDA MATRIZ AL PADRE
		
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
		printf("SUMA. NIETO -> PADRE. NIETO.\n");
		
		*aNP = 101;	
		while(*shmNP != -1)
			Sleep(1);
		UnmapViewOfFile(shmNP);
		CloseHandle(hArchMapeoNP);
		
	exit(0);
}