#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <math.h>

int main(){
	pid_t pid;
	char *argv[3];
	argv[0] = "/home/enrike/Escritorio/P4-SO/expresion";
	argv[1] = "/home/enrike/Escritorio/P4-SO/permisos";
	argv[2] = NULL;

	if(pid = fork() == 0)
	{
		printf("Soy el primer hijo\n");

		if(pid = fork() == 0){
			printf("Soy el hijo ejecutando: %s\n", argv[0]);
			int e = execv(argv[0], argv);
			if(e == -1){
				perror(argv[0]);
    			exit(EXIT_FAILURE);
			}
		}

		wait(0);
		wait(0);

		if(pid = fork() == 0){
			printf("Soy el hijo ejecutando: %s\n", argv[1]);
			int e = execv(argv[1], argv);
			if(e == -1){
				perror(argv[1]);
    			exit(EXIT_FAILURE);
			}
		}

		else{
			wait(0);
			printf("Soy el padre de los hijitos\n");
			exit(0);
		}	

	}
	else
	{
		wait(0);
		printf("Soy el primer padre del hijo\n");
		exit(0);
	}

}
