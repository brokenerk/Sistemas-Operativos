// 04 de Octubre 2018
// Para generar muchos procesos HIJO
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int i = 10;
int main(void)
{
	int id_proc;
	for(i = 0; i<100; i++)
	{
		id_proc = fork();
		if(id_proc == 0)
		{
			printf("Soy el proceso hijo %i\n", i);
		} break; //exit(0); // Para que no cree hijos de hijos
		else
		{
			// Para que el padre haga otra cosa, sino se omite
			printf("Soy el proceso padre %i\n", i);
		}	
	}	
}
