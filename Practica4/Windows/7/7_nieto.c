//Compilar: gcc 7_nieto.c -o nieto
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
		printf(/*Usar: %s */"Soy el proceso nieto \n"/*, argv[0]*/);
		return 0;
	}
	//Creacion proceso hijo
		if(!CreateProcess(NULL, argv[0],NULL,NULL,FALSE,0,NULL,NULL,&si,&pi))
		{
			printf("Fallo al invocar CreateProcess(%d)\n",GetLastError());
			return 0;
		}
	//Proceso Padre
	printf("Soy el proceso padre\n");
	WaitForSingleObject(pi.hProcess, INFINITE);
	
	//Terminacion controlada del proceso e hilo asociado de ejecucion
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}
