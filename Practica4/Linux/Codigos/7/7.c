#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <math.h>

int main(){
	pid_t pid;
	char *argv[4];
	argv[0] = "/home/enrike/Escritorio/P4-SO/7/expresion";
	argv[1] = "/home/enrike/Escritorio/P4-SO/7/permisos";
	argv[2] = "/home/enrike/Escritorio/P4-SO/7/inversa";
	argv[3] = NULL;

	if(pid = fork() == 0)//Proceso Hijo 1: Expresion
	{
		if(pid = fork() == 0){
			printf("Soy el hijo 1 ejecutando: %s\n", argv[0]);
			int e = execv(argv[0], argv);
			if(e == -1){
				perror(argv[0]);
    			exit(EXIT_FAILURE);
			}
		}
		//Evitar concurrencias entre procesos
		wait(0);
		wait(0);

		if(pid = fork() == 0)//Proceso Hijo 2: Permisos
		{
			printf("---------------------------------------------------\n\n");
			printf("Soy el hijo 2 ejecutando: %s\n", argv[1]);
			int e = execv(argv[1], argv);
			if(e == -1){
				perror(argv[1]);
    			exit(EXIT_FAILURE);
			}
		}

		wait(0);
		wait(0);

		if(pid = fork() == 0)//Proceso Hijo 3: Inversa Matriz
		{
			printf("---------------------------------------------------\n\n");
			printf("Soy el hijo 3 ejecutando: %s\n", argv[2]);
			int e = execv(argv[2], argv);
			if(e == -1){
				perror(argv[2]);
    			exit(EXIT_FAILURE);
			}
		}
		else //Primero proceso hijo, padre de los hijos de arriba
		{
			wait(0);
			printf("Soy el padre de los hijitos\n");
			exit(0);
		}	

	}
	else //Proceso padre
	{
		wait(0);
		printf("Soy el primer padre del hijo\n");
		exit(0);
	}

}
