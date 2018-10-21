#include<bits/stdc++.h>
#include <windows.h>
#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <fstream>
using namespace std;
int mat1[10][10];
int mat2[10][10];
int res[10][10];
void CrearMatriz(){
	srand(time(NULL));
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			mat1[i][j]=rand()%10;
			mat2[j][i]=rand()%10;
		}
	}
}
void ImprimirTranspuestas(){
	int i,j;
	ofstream myfile;
	myfile.open("salidaT.txt");
	for(i = 0;i < 10;i++){
      	for(j = 0;j < 10;j++){
          	myfile<<mat1[j][i]<<'\t';
       	}
       	myfile<<'\n';
  	}
  	for(i = 0;i < 10;i++){
      	for(j = 0;j < 10;j++){
          	myfile<<mat2[j][i]<<'\t';
       	}
       	myfile<<'\n';
  	}
  	myfile.close();
}
int main(int argc, char *argv[]){
	CrearMatriz();
	ImprimirTranspuestas();
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	int i;
	ZeroMemory(&si, sizeof(si));
	si.cb=sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	if(argc!=2){
		//printf(/*Usar: %s */"Soy el proceso hijo \n"/*, argv[0]*/);
		return 0;
	}
	//Creacion proceso hijo

		if(!CreateProcess(NULL, argv[0],NULL,NULL,FALSE,0,NULL,NULL,&si,&pi)){
			printf("Fallo al invocar CreateProcess(%d)\n",GetLastError());
			return 0;
		}
	//Proceso Padre
	WaitForSingleObject(pi.hProcess, INFINITE);
	
	//Terminacion controlada del proceso e hilo asociado de ejecucion
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}