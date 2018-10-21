/* hola.c Programa que será invocado */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	char mensaje[100];
	strcpy(mensaje, "Hola Mundo");
	strcat(mensaje, argv[1]);
	printf("%s\n", mensaje);
	exit(0);
}