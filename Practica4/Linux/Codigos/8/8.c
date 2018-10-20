#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <math.h>

int main(){
	pid_t pid;
	char *argv[7];
	argv[0] = "/home/enrike/Escritorio/P4-SO/8/suma";
	argv[1] = "/home/enrike/Escritorio/P4-SO/8/resta";
	argv[2] = "/home/enrike/Escritorio/P4-SO/8/multiplicacion";
	argv[3] = "/home/enrike/Escritorio/P4-SO/8/transpuesta";
	argv[4] = "/home/enrike/Escritorio/P4-SO/8/inversa";
	argv[5] = "/home/enrike/Escritorio/P4-SO/8/leerArchivos";
	argv[6] = NULL;

		if(pid = fork() == 0){//Proceso Hijo1: Suma
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

		if(pid = fork() == 0)//Proceso Hijo 2: Resta
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

		if(pid = fork() == 0)//Proceso Hijo 3: Multiplicacion
		{
			printf("---------------------------------------------------\n\n");
			printf("Soy el hijo 3 ejecutando: %s\n", argv[2]);
			int e = execv(argv[2], argv);
			if(e == -1){
				perror(argv[2]);
    			exit(EXIT_FAILURE);
			}
		}

		wait(0);
		wait(0);

		if(pid = fork() == 0)//Proceso Hijo 4: Transpuesta
		{
			printf("---------------------------------------------------\n\n");
			printf("Soy el hijo 4 ejecutando: %s\n", argv[3]);
			int e = execv(argv[3], argv);
			if(e == -1){
				perror(argv[3]);
    			exit(EXIT_FAILURE);
			}
		}

		wait(0);
		wait(0);

		if(pid = fork() == 0)//Proceso Hijo 5: Inversa
		{
			printf("---------------------------------------------------\n\n");
			printf("Soy el hijo 4 ejecutando: %s\n", argv[4]);
			int e = execv(argv[4], argv);
			if(e == -1){
				perror(argv[4]);
    			exit(EXIT_FAILURE);
			}
		}
		else //Proceso Padre: Leer Archivos
		{
			wait(0); wait(0); wait(0); wait(0); wait(0); wait(0);
			printf("---------------------------------------------------\n\n");
			printf("Soy el padre ejecutando: %s\n", argv[5]);
			int e = execv(argv[5], argv);
			if(e == -1){
				perror(argv[5]);
    			exit(EXIT_FAILURE);
			}
		}	

}
