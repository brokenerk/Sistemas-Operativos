#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "funciones.h"
char* leerDirectorio();

int main(void)
{
	// CREAR DIRECTORIO
	// Obtenemos el directorio desde la entrada de teclado
	char* path = leerDirectorio();
	//Llamda al sistema mkdir recibe la ruta del directorio a crear, y los permisos de escritura, lectura y ejecucion para cada tipo de usuario
	//Retorna -1 si ocurrieron errores
	if(mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) ==-1)
	{
		perror(path);
        exit(EXIT_FAILURE);
    }

	int n = 10, i, j;
	int pipefd_0_1[2];
	int pipefd_1_0[2];
	int pipefd_1_2[2];
	int pipefd_2_0[2];
	double **matrixA, **matrixB, **mul, **suma, **inv1, **inv2;

	// Inicializa las matrices.
	matrixA = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		matrixA[i] = (double*)calloc(n,sizeof(double));

	matrixB = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		matrixB[i] = (double*)calloc(n,sizeof(double));

	mul = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		mul[i] = (double*)calloc(n,sizeof(double));

	suma = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		suma[i] = (double*)calloc(n,sizeof(double));

	inv1 = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		inv1[i] = (double*)calloc(n,sizeof(double));

	inv2 = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		inv2[i] = (double*)calloc(n,sizeof(double));

	if (pipe (pipefd_0_1) != 0 || pipe (pipefd_1_0) != 0 || pipe (pipefd_1_2) != 0 || pipe (pipefd_2_0) != 0)
	{
	exit(1);
	}

	if (fork()) 
	{ //0
	    srand(getpid());
	    llenar(matrixA, n);
	    llenar(matrixB, n);

	    printf("MATRIZ A\n"); imprimir(matrixA, n);
	    printf("\nMATRIZ B\n"); imprimir(matrixB, n);

	    for(i = 0; i < n; i++){
	    	for(j = 0; j < n; j++){
	    		write(pipefd_0_1[1], &matrixA[i][j], sizeof(double)); 
	    		write(pipefd_0_1[1], &matrixB[i][j], sizeof(double));
	    	}	
	    }
    
		for(i = 0; i < n; i++){
			for(j = 0; j < n; j++){
				read(pipefd_1_0[0], &mul[i][j], sizeof(double));
				read(pipefd_2_0[0], &suma[i][j], sizeof(double));
			}
		}

		printf("\nMultiplicacion realizada por el Proceso PADRE:\n");
		imprimir(mul, n);
		printf("Escribiendo archivo TXT de inversa multiplicacion....");
		inversa(mul, inv1, n);
		crearArchivo(inv1, n, "/inv_mul.txt", path);
		printf("Listo\n\n");

		printf("Suma realizada por el Proceso HIJO:\n");
		imprimir(suma,n);
		printf("Escribiendo archivo TXT de inversa suma....");
		inversa(suma, inv2, n);
		crearArchivo(inv2, n, "/inv_suma.txt", path);
		printf("Listo\n\n");

		exit(0);
  	}
  	else
	{
      	if (fork())
        { // 1
			srand(getpid());
			llenar(matrixA, n);
			llenar(matrixB, n);
			printf("\nMATRIZ C\n"); imprimir(matrixA, n);
			printf("\nMATRIZ D\n"); imprimir(matrixB, n);

			for(i = 0; i < n; i++){
				for(j = 0; j < n; j++){
					write(pipefd_1_2[1], &matrixA[i][j], sizeof(double));
			    	write(pipefd_1_2[1], &matrixB[i][j], sizeof(double));

			    	read(pipefd_0_1[0], &matrixA[i][j], sizeof(double));
			    	read(pipefd_0_1[0], &matrixB[i][j], sizeof(double));
				}
			}

			multiplicar(matrixA, matrixB, mul, n);

			for(i = 0; i < n; i++){
				for(j = 0; j < n; j++){
					write(pipefd_1_0[1], &mul[i][j], sizeof(double));
				}
			}
			exit(0);
		}
        else 
        { // 2
        	for(i = 0; i < n; i++){
		    	for(j = 0; j < n; j++){
		    		read(pipefd_1_2[0], &matrixA[i][j], sizeof(double));
          			read(pipefd_1_2[0], &matrixB[i][j], sizeof(double));
		    	}
		    }
          

			sumar(matrixA, matrixB, suma, n);
			for(i = 0; i < n; i++){
		    	for(j = 0; j < n; j++){
		    		write(pipefd_2_0[1], &suma[i][j], sizeof(double));
		    	}
		    }
			exit(0);
      	}
	}	
}

char* leerDirectorio()
{
	char* directorio = (char*)calloc(2000,sizeof(char));
	printf("Ingrese el nuevo directorio: ");
	scanf("%s", directorio);
	return directorio;
}