#include <windows.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
	STARTUPINFO si;			//Estructura de informacion inicial para Windows
	PROCESS_INFORMATION pi;	//Estructura de informacion para el adm. de procesos
	int i;
	ZeroMemory(&si, sizeof(si));
	si.cb=sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	if(argc!=2)
	{
		printf("Usar: %s Nombre_programa_hijo \n", argv[0]);
		return 0;
	}
	//Creacion proceso hijo
	if(!CreateProcess(NULL, argv[1],NULL,NULL,FALSE,0,NULL,NULL,&si,&pi))
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
