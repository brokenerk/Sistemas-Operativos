// 04 de Octubre 2018
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int i = 10;
int main(void)
{
	int id_proc = fork();
	if(id_proc == 0)
	{
		i += 10;
		printf("Soy el proceso hijo %i\n", i);
		// Para generar un proceso del hijo
	}
	else
	{
		i += 100;
		printf("Soy el proceso padre %i\n", i);
		// Para generar un proceso del hijo Padre
	}
	i += 20;
	printf("Valor de i= %i\n", i);
	// Delimita hasta donde el proceso padre o hijo ejecutan
	exit(0);
}

/*
	POSIBLES SALIDAS - Diferente orden 
	SOY EL PROCESO HIJO 20
	VALOR DE i = 40
	SOY EL PROCESO PADRE 110
	VALOR DE i = 130


*/	