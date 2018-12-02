#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>	
#include <sys/shm.h>
#include "funciones.h"
#define TAM_MEM 400

void escribir(double **matriz, int n, double *shm);
void leer(double **matriz, int n, double *shm);
void encender(int semid);
void apagar(int semid);
char* leerDirectorio();

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

	int i, n = 10, shmid1, shmid2, semaforo0, semaforo1;
	double **matriz1, **matriz2, **matriz3, **matriz4, **suma, **mul, **inv1, **inv2, *shm1, *shm2;
	key_t llave1 = 5678, llave2 = 5679;

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
	if(((shmid1 = shmget(llave1, TAM_MEM, IPC_CREAT | 0666)) < 0) || ((shmid2 = shmget(llave2, TAM_MEM, IPC_CREAT | 0666)) < 0))
	{
		perror("Error al obtener la memoria compartida: shmget");
		exit(-1);
	}

	if(((shm1 = shmat(shmid1, NULL, 0)) == (double*)-1) || ((shm2 = shmat(shmid2, NULL, 0)) == (double*)-1))
	{
		perror("Error al lanzar la memoria compartida: shmat");
		exit(-1);
	}

	//---------Revisamos que se hayan iniciando los semaforos---------------
	if(((semaforo0 = semget(llave1, 1, IPC_CREAT | 0666)) == -1) || ((semaforo1 = semget(llave2, 1, IPC_CREAT | 0666)) == -1)){
		perror("Error al iniciar los semaforos: semget");
		exit(-1);
	}

	//---------Inicializamos los semaforos --> apagados---------------
	if ((semctl(semaforo0, 0, SETVAL, 0) == -1) || (semctl(semaforo1, 0, SETVAL, 0) == -1))
    {
		printf ("Error al crear los semaforos: semctl\n");
		exit(-1);
    }

	printf("------------SEMAFOROS(2) INICIADOS--------------\n");


	//--------------------Creamos los procesos-----------------------------
	if(fork() == 0)
	{
		if(fork() == 0)
		{
			//------------------PROCESO HIJO: SUMA
			printf("------------------------------\n");
			printf("Proceso HIJO leeyendo matriz 3\n");
			leer(matriz3, n, shm1);

			printf("Proceso HIJO leeyendo matriz 4\n");
			leer(matriz4, n, shm2);

			printf("Proceso HIJO sumando matrices\n");
			sumar(matriz3, matriz4, suma, n);

			printf("Proceso HIJO escribiendo la suma\n");
			escribir(suma, n, shm1);

			//--------ENCENDER SEMAFORO 1-----------
			encender(semaforo1);
		}
		else
		{
			//------------------PROCESO PADRE: MULTIPLICACION
			srand(getpid());
			printf("------------------------------\n");

			printf("Proceso PADRE leeyendo matriz 1\n");
			leer(matriz1, n, shm1);

			printf("Proceso PADRE leeyendo matriz 2\n");
			leer(matriz2, n, shm2);

			printf("Proceso PADRE multiplicando matrices\n");
			multiplicar(matriz1, matriz2, mul, n);

			printf("Proceso PADRE creando matriz 3\n");
			llenar(matriz3, n); 
			imprimir(matriz3, n);

			printf("\nProceso PADRE creando matriz 4\n");
			llenar(matriz4, n); 
			imprimir(matriz4, n);

			printf("Proceso PADRE escribiendo matriz 3\n");
			escribir(matriz3, n, shm1);

			printf("Proceso PADRE escribiendo matriz 4\n");
			escribir(matriz4, n, shm2);

			//--------APAGAR SEMAFORO 1-----------
			apagar(semaforo1);

			printf("Proceso PADRE escribiendo la multiplicacion\n");
			escribir(mul, n, shm2);

			//--------ENCENDER SEMAFORO 0-----------
			encender(semaforo0);
		}
	}
	else
	{
		//------------------PROCESO ABUELO: Crea matrices y lee inversas
		srand(getpid());
		printf("------------------------------\n");

		printf("Proceso ABUELO creando matriz 1\n");
		llenar(matriz1, n); 
		imprimir(matriz1, n);

		printf("Proceso ABUELO creando matriz 2\n");
		llenar(matriz2, n); 
		imprimir(matriz2, n);

		printf("Proceso ABUELO escribiendo matriz 1\n");
		escribir(matriz1, n, shm1);

		printf("Proceso ABUELO escribiendo matriz 2\n");
		escribir(matriz2, n, shm2);

		//--------APAGAR SEMAFORO 0-----------
		apagar(semaforo0);

		//--------------------MULTIPLICACION---------------
		printf("Proceso ABUELO leeyendo multiplicacion\n");
		leer(mul, n, shm2);
		
		printf("\nMultiplicacion realizada por el Proceso PADRE:\n");
		imprimir(mul, n);
		printf("Escribiendo archivo TXT de inversa multiplicacion....");
		inversa(mul, inv2, n);
		crearArchivo(inv2, n, "/inv_mul.txt", path);
		printf("Listo\n\n");

		//--------------------SUMA----------__-----
		printf("Proceso ABUELO leeyendo suma\n");
		leer(suma, n, shm1);

		printf("\nSuma realizada por el Proceso HIJO:\n");
		imprimir(suma, n);
		printf("Escribiendo archivo TXT de inversa suma....");
		inversa(suma, inv1, n);
		crearArchivo(inv1, n, "/inv_suma.txt", path);
		printf("Listo\n\n");
	}
	exit(0);
}

void escribir(double **matriz, int n, double *z)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			*z++ = matriz[i][j];
		}
	}
}

void leer(double **matriz, int n, double *z)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			matriz[i][j] = *z++;
		}
	}
}

void encender(int semid)
{
	struct sembuf sops;
	sops.sem_num = 0;
	sops.sem_op = 1;
	sops.sem_flg = 0;

	if (semop(semid, &sops, 1) == -1)
	{
		perror("semop: error al encender el semaforo\n");
		exit(-1);
	}
	printf("\n------------SEMAFORO %d: ENCENDIDO--------------\n", semid);
}

void apagar(int semid)
{
	struct sembuf sops;
	sops.sem_num = 0;
	sops.sem_op = -1;
	sops.sem_flg = 0;

	if (semop(semid, &sops, 1) == -1)
	{
		perror("semop: error al encender el semaforo\n");
		exit(-1);
	}
	printf("\n------------SEMAFORO %d: APAGADO--------------\n", semid);
}


char* leerDirectorio()
{
	char* directorio = (char*)calloc(2000,sizeof(char));
	printf("Ingrese el nuevo directorio: ");
	scanf("%s", directorio);
	return directorio;
}