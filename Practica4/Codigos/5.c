// 04 de Octubre 2018
// Para generar muchos procesos HIJO - HORIZONTALES
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	int i;
	int id_proc;
	for(i = 0; i<5; i++)
	{
		id_proc = fork();
		if(id_proc == 0)
		{
			if(i == 0)
			{
				// PROCESO SUMA
				printf("----------- SUMA");
			}	
			if(i == 1)
			{
				// PROCESO RESTA
				printf("------------ RESTA");
			}
			if(i == 2)
			{
				// PROCESO MULTIPLICACION
				printf("----------- MULTIPLICACION");
			}
			if(i == 3)
			{
				// PROCESO TRANSPUESTA
				printf("--------- TRANSPUESTA");
			}
			if(i == 4)
			{
				// PROCESO INVERSA
				printf("--------- INVERSA");
			}
			break; // Para que no cree hijos de hijos
		} 
		else
		{
			// Para que el padre haga otra cosa, sino se omite
			wait(0); wait(0); wait(0); wait(0); wait(0);
			printf(" ---------- LEEE ARCHIVO E IMPRIME");

		}	
	}	
}
