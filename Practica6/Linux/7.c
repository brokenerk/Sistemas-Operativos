#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>	
#include <sys/shm.h>
#include "funciones.h"
#define TAM_MEM 27

void escribir(double **matriz, int n, int clave);
void leer(double **matriz, int n, int clave);
char* leerDirectorio();
int *shm, *z, c, d;


int main()
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

	int i, n, shmid, pid;
	double **matriz1, **matriz2, **matriz3, **matriz4, **suma, **mul, **inv1, **inv2;
	
	n = 10; // Tam de la matriz cuadrada
	key_t llave = 5678;

	// Inicializa las matrices.
	matriz1 = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		matriz1[i] = (double*)calloc(n,sizeof(double));

	matriz2 = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		matriz2[i] = (double*)calloc(n,sizeof(double));

	matriz3 = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		matriz3[i] = (double*)calloc(n,sizeof(double));

	matriz4 = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		matriz4[i] = (double*)calloc(n,sizeof(double));
	
	suma = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		suma[i] = (double*)calloc(n,sizeof(double));

	mul = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		mul[i] = (double*)calloc(n,sizeof(double));

	inv1 = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		inv1[i] = (double*)calloc(n,sizeof(double));

	inv2 = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		inv2[i] = (double*)calloc(n,sizeof(double));

	//---------Revisamos que se haya creado la mem compartida---------------

	if((shmid = shmget(llave, TAM_MEM, IPC_CREAT | 0666)) < 0)
	{
		perror("Error al obtener la memoria compartida: shmget");
		exit(-1);
	}

	if((shm = shmat(shmid, NULL, 0)) == (int*)-1)
	{
		perror("Error al lanzar la memoria compartida: shmat");
		exit(-1);
	}

	//--------------------Creamos los procesos-----------------------------

	if((pid = fork()) == 0)
	{
		if((pid = fork()) == 0)
		{
			//------------------PROCESO HIJO: SUMA
			sleep(11);

			printf("------------------------------\n");
			printf("Proceso HIJO leeyendo matriz 3\n");
			leer(matriz3, n, 789);
			sleep(4);

			printf("Proceso HIJO leeyendo matriz 4\n");
			leer(matriz4, n, 890);

			printf("Proceso HIJO sumando matrices\n");
			sumar(matriz3, matriz4, suma, n);
			sleep(2);

			printf("Proceso HIJO escribiendo la suma\n");
			escribir(suma, n, 654);
			exit(0);
		}
		else
		{
			//------------------PROCESO PADRE: MULTIPLICACION
			srand(getpid());
			printf("------------------------------\n");
			sleep(1);

			printf("Proceso PADRE leeyendo matriz 1\n");
			leer(matriz1, n, 456);
			sleep(3);

			printf("Proceso PADRE leeyendo matriz 2\n");
			leer(matriz2, n, 678);
			sleep(2);

			printf("Proceso PADRE multiplicando matrices\n");
			multiplicar(matriz1, matriz2, mul, n);

			printf("Proceso PADRE escribiendo la multiplicacion\n");
			escribir(mul, n, 654);
			sleep(2);

			printf("Proceso PADRE creando matriz 3\n");
			llenar(matriz3, n); 
			imprimir(matriz3, n);

			printf("Proceso PADRE escribiendo matriz 3\n");
			escribir(matriz3, n, 789);
			sleep(2);

			printf("\nProceso PADRE creando matriz 4\n");
			llenar(matriz4, n); 
			imprimir(matriz4, n);

			printf("Proceso PADRE escribiendo matriz 4\n");
			escribir(matriz4, n, 890);

			exit(0);
		}
	}
	else{
		//------------------PROCESO ABUELO: Crea matrices y lee inversas
		srand(getpid());
		printf("------------------------------\n");
		printf("Proceso ABUELO creando matriz 1\n");
		llenar(matriz1, n); 
		imprimir(matriz1, n);

		printf("\nProceso ABUELO creando matriz 2\n");
		llenar(matriz2, n); 
		imprimir(matriz2, n);

		printf("Proceso ABUELO escribiendo matriz 1\n");
		escribir(matriz1, n, 456);
		sleep(1);

		printf("Proceso ABUELO escribiendo matriz 2\n");
		escribir(matriz2, n, 678);
		sleep(3.5);

		printf("Proceso ABUELO leeyendo multiplicacion\n");
		leer(mul, n, 654);
		sleep(12);

		printf("Proceso ABUELO leeyendo suma\n");
		leer(suma, n, 654);
		sleep(1);

		printf("Suma realizada por el Proceso HIJO:\n");
		imprimir(suma, n);

		printf("Escribiendo archivo TXT de inversa suma....");
		inversa(suma, inv1, n);
		crearArchivo(inv1, n, "/inv_suma.txt", path);
		printf("Listo\n\n");

		printf("Multiplicacion realizada por el Proceso PADRE:\n");
		imprimir(mul, n);

		printf("Escribiendo archivo TXT de inversa multiplicacion....");
		inversa(mul, inv2, n);
		crearArchivo(inv2, n, "/inv_mul.txt", path);
		printf("Listo\n\n");
		
		exit(0);
	}
	return 0;
}

void escribir(double **matriz, int n, int clave)
{
	int j, i;
	z = shm;

	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			*z++ = matriz[i][j];
		}
	}

	*z = clave;
	while(*shm != '*')
		sleep(1);
}

void leer(double **matriz, int n, int clave)
{
	int x = 0, y = 0, valor;
	for(z = shm; *z != clave; z++)
	{
		valor = *z;
		matriz[x][y] = valor;

		if(y == n-1)
		{
			x++;
			y = 0;
		}
		else
			y++;
	}
	*shm = '*';
}

char* leerDirectorio()
{
	char* directorio = (char*)calloc(2000,sizeof(char));
	printf("Ingrese el nuevo directorio: ");
	scanf("%s", directorio);
	return directorio;
}


