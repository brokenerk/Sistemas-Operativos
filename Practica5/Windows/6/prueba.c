#include <windows.h>
#include <stdio.h>

DWORD WINAPI funcionHilo(LPVOID lpParam);
typedef struct  Informacion info;
struct Informacion
{
	int val_1;
	int val_2;
};

int main(void)
{
	DWORD idHilo; // Identificador del Hilo
	HANDLE manHilo;	// Manejador del Hilo
	info argumentos;
	argumentos.val_1 = 10;
	argumentos.val_2 = 100;
	int *i;

	for(i = 0; i < 5; i++)
	{
		// Creacion del hilo
		manHilo = CreateThread(NULL, 0, funcionHilo, &i, 0, &idHilo);
		// Espera la finalizacion del hilo
		WaitForSingleObject(manHilo, INFINITE);
		//printf("Valores a salir del Hilo: %i %i\n", argumentos.val_1, argumentos.val_2);
	}
	
	// Cierre del manejador del hilo creado
	CloseHandle(manHilo);
	return 0;
}

DWORD WINAPI funcionHilo(LPVOID lpParam)
{
	int *a = (int *)lpParam;
	printf("Valores al entrar al Hilo: %i\n", a);
	return 0;
}