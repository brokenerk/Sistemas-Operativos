/*Programa 3_hijo.c*/
//Compilar: gcc 3_hijo.c -o hijo
#include <stdio.h>
#include <windows.h>

int main()
{
	char mensaje[20];
	DWORD leidos;
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	SECURITY_ATTRIBUTES pipeSeg = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};

	/*Lectura desde la tuberia sin nombre*/
	ReadFile(hStdIn, mensaje, sizeof(mensaje), &leidos, NULL);
	printf("Mensaje recibido del proceso padre: %s\n", mensaje);
	CloseHandle(hStdIn);
	printf("Termina el proceso hijo, continua el proceso padre\n");
	return 0;
}