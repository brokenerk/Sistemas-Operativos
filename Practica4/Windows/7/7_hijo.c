//Compilar: gcc 7_hijo.c -o hijo
#include<windows.h>
#include<stdio.h>
int main(int argc, char *argv[])
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	int i;
	ZeroMemory(&si, sizeof(si));
	si.cb=sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	if(argc!=2)
	{
		printf(/*Usar: %s */"Soy el proceso hijo \n"/*, argv[0]*/);
	}
	//Creacion proceso hijo
	printf("Creando nietos \n");
	for(int i=0;i<3;i++)
	{
		if(!CreateProcess(NULL, "C:\\nieto.exe", NULL,NULL,FALSE,0,NULL,NULL,&si,&pi))
		{
			printf("Fallo al invocar CreateProcess(%d)\n",GetLastError());
			return 0;
		}
		printf("ID del Proceso (%d)\n",pi.dwProcessId);
	}
	//Proceso Padre
	WaitForSingleObject(pi.hProcess, INFINITE);
	
	//Terminacion controlada del proceso e hilo asociado de ejecucion
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}
