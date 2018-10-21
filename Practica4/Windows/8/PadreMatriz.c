#include<windows.h>
#include<stdio.h>
#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;
int main(int argc, char *argv[]){
	HANDLE hProcess;
	HANDLE hThread;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	DWORD dwProcessId=0;
	DWORD dwThreadId=0;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	if(!CreateProcess("C:\\Users\\sergi\\OneDrive\\Documentos\\ESCOM\\Tercer Semestre\\Sistemas Operativos\\Practica 4\\Punto 8\\SumaDeMatrices.exe",NULL,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi)){
		printf("Fallo al crear el proceso (%d)\n",GetLastError());
	}
	WaitForSingleObject(pi.hProcess,INFINITE);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	printf("Suma de Matrices, ID del Proceso (%d)\n",pi.dwProcessId);
	if(!CreateProcess("C:\\Users\\sergi\\OneDrive\\Documentos\\ESCOM\\Tercer Semestre\\Sistemas Operativos\\Practica 4\\Punto 8\\RestaDeMatrices.exe",NULL,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi)){
		printf("Fallo al crear el proceso (%d)\n",GetLastError());
	}
	printf("Resta de Matrices, ID del Proceso (%d)\n",pi.dwProcessId);
	WaitForSingleObject(pi.hProcess,INFINITE);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	if(!CreateProcess("C:\\Users\\sergi\\OneDrive\\Documentos\\ESCOM\\Tercer Semestre\\Sistemas Operativos\\Practica 4\\Punto 8\\Multiplicacion.exe",NULL,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi)){
		printf("Fallo al crear el proceso (%d)\n",GetLastError());
	}
	printf("Multiplicacion de Matrices, ID del Proceso (%d)\n",pi.dwProcessId);
	WaitForSingleObject(pi.hProcess,INFINITE);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	if(!CreateProcess("C:\\Users\\sergi\\OneDrive\\Documentos\\ESCOM\\Tercer Semestre\\Sistemas Operativos\\Practica 4\\Punto 8\\Transpuesta.exe",NULL,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi)){
		printf("Fallo al crear el proceso (%d)\n",GetLastError());
	}
	printf("Transpuesta de Matrices, ID del Proceso (%d)\n",pi.dwProcessId);
	WaitForSingleObject(pi.hProcess,INFINITE);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	if(!CreateProcess("C:\\Users\\sergi\\OneDrive\\Documentos\\ESCOM\\Tercer Semestre\\Sistemas Operativos\\Practica 4\\Punto 8\\Impresion.exe",NULL,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi)){
		printf("Fallo al crear el proceso (%d)\n",GetLastError());
	}
	printf("Impresion de las Matrices, ID del Proceso (%d)\n",pi.dwProcessId);
	//cout<<"Create process Succed"<<'\n';
	//cout<< "process ID"<<pi.dwProcessId<<'\n';
	WaitForSingleObject(pi.hProcess,INFINITE);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}
