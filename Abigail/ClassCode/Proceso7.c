// 04 de Octubre 2018
// Para generar muchos procesos seguidos
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int i = 10;
int main(void)
{
	¨/*
		Mantiene vivos los procesos hijos que se van convirtiendo en padres
		si usamos exit vamos matando los procesos padre y eso no queremos.
	*/
	int id_proc;
	for(i = 0; i<100; i++)
	{
		id_proc = fork();
		// Cuando es hijo el fork siempre devuelve 0.
		if(id_proc == 0)
		{
			printf("Soy el proceso hijo %i\n", i);
		} 
		else
		{
			break; // Sale del ciclo 
			// Para que el padre haga otra cosa, sino se omite
			printf("Soy el proceso padre %i\n", i);
		}	
	}	
}
