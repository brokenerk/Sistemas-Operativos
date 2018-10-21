#include<windows.h>
#include<stdio.h>

int main(int argc, char *argv[]){
	HANDLE hProcess;
	HANDLE hThread;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	DWORD dwProcessId=0;
	DWORD dwThreadId=0;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));


		if(!CreateProcess(NULL, "C:\\Users\\YaKerTaker\\Google Drive\\5to SEMESTRE\\Sistemas-Operativos\\Practica4\\Windows\\8\\suma.exe",NULL,NULL,FALSE,0,NULL,NULL,&si,&pi)){
		printf("Fallo al crear el proceso (%d)\n",GetLastError());
	}
	printf("\nSuma de Matrices, ID del Proceso (%d)\n",pi.dwProcessId);

	WaitForSingleObject(pi.hProcess,INFINITE);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);


	
	if(!CreateProcess(NULL, "C:\\Users\\YaKerTaker\\Google Drive\\5to SEMESTRE\\Sistemas-Operativos\\Practica4\\Windows\\8\\resta.exe",NULL,NULL,FALSE,0,NULL,NULL,&si,&pi)){
		printf("Fallo al crear el proceso (%d)\n",GetLastError());
	}
	printf("\nResta de Matrices, ID del Proceso (%d)\n",pi.dwProcessId);

	WaitForSingleObject(pi.hProcess,INFINITE);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);



	if(!CreateProcess(NULL, "C:\\Users\\YaKerTaker\\Google Drive\\5to SEMESTRE\\Sistemas-Operativos\\Practica4\\Windows\\8\\multiplicacion.exe",NULL,NULL,FALSE,0,NULL,NULL,&si,&pi)){
		printf("Fallo al crear el proceso (%d)\n",GetLastError());
	}
	printf("\nMultiplicacion de Matrices, ID del Proceso (%d)\n",pi.dwProcessId);

	WaitForSingleObject(pi.hProcess,INFINITE);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	if(!CreateProcess(NULL, "C:\\Users\\YaKerTaker\\Google Drive\\5to SEMESTRE\\Sistemas-Operativos\\Practica4\\Windows\\8\\transpuesta.exe",NULL,NULL,FALSE,0,NULL,NULL,&si,&pi)){
		printf("Fallo al crear el proceso (%d)\n",GetLastError());
	}
	printf("\nTranspuestas de Matrices, ID del Proceso (%d)\n",pi.dwProcessId);

	WaitForSingleObject(pi.hProcess,INFINITE);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	if(!CreateProcess(NULL, "C:\\Users\\YaKerTaker\\Google Drive\\5to SEMESTRE\\Sistemas-Operativos\\Practica4\\Windows\\8\\inversa.exe",NULL,NULL,FALSE,0,NULL,NULL,&si,&pi)){
		printf("Fallo al crear el proceso (%d)\n",GetLastError());
	}
	printf("\nInversas de Matrices, ID del Proceso (%d)\n",pi.dwProcessId);

	WaitForSingleObject(pi.hProcess,INFINITE);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	if(!CreateProcess(NULL, "C:\\Users\\YaKerTaker\\Google Drive\\5to SEMESTRE\\Sistemas-Operativos\\Practica4\\Windows\\8\\leerArchivos.exe",NULL,NULL,FALSE,0,NULL,NULL,&si,&pi)){
		printf("Fallo al crear el proceso (%d)\n",GetLastError());
	}
	printf("\nImpresion de las Matrices, ID del Proceso (%d)\n",pi.dwProcessId);
	//cout<<"Create process Succed"<<'\n';
	//cout<< "process ID"<<pi.dwProcessId<<'\n';
	WaitForSingleObject(pi.hProcess,INFINITE);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	WaitForSingleObject(pi.hProcess,INFINITE);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}
