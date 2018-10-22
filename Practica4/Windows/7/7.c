//Compilar: gcc 7.c -o 7
//Ejecutar: 7 padre
#include <windows.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
	HANDLE hProcess;
	HANDLE hThread;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	DWORD dwProcessId=0;
	DWORD dwThreadId=0;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));

	if(!CreateProcess(NULL, argv[1],NULL,NULL,FALSE,0,NULL,NULL,&si,&pi))
	{
		printf("Fallo al crear el proceso (%d)\n",GetLastError());
	}
	printf("Soy el hijo-padre\n");
	printf("ID del Proceso (%d)\n",pi.dwProcessId);

	WaitForSingleObject(pi.hProcess,INFINITE);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}
