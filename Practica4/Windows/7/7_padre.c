//Compilar: gcc 7_padre.c -o padre
#include <windows.h>
#include<stdio.h>
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
	for(int i=0;i<5;i++)
	{
		if(!CreateProcess(NULL, 
			"C:\\Users\\YaKerTaker\\Google Drive\\5to SEMESTRE\\Sistemas-Operativos\\Practica4\\Windows\\7\\hijo.exe",
			NULL,NULL,FALSE,0,NULL,NULL,&si,&pi))
		{
			printf("Fallo al crear el proceso (%d)\n",GetLastError());
		}
		printf("ID del Proceso (%d)\n",pi.dwProcessId);
	}
	WaitForSingleObject(pi.hProcess,INFINITE);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}
