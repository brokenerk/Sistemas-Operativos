#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <pthread.h>

typedef struct{
	char Origen[400];
	char Destino[400];
} RUTA;

int esDirectorio(char path[])
{
	struct stat sb;

	if(stat(path, &sb) == -1)
	{
		perror(path);
		printf("no es directorio\n");
	    exit(-1);
	}
	printf("---ok\n");

	if(S_ISDIR(sb.st_mode))
	{
		printf("-regreso 1\n");
		return 1;
	}
	else {
		printf("-regreso 0\n");
		return 0;
	}
}

void concatenar(char dir[], char aux[], char nombre[])
{
	strcpy(dir, aux);
	strcat(dir, "/");
	strcat(dir, nombre);
}

int ignorarPuntos(char nombre[])
{

	if(strcmp(nombre, ".") && strcmp(nombre, ".."))
		return 1;
	else
		return 0;
}

void copiarArchivo(char origen[], char destino[])
{
	ssize_t leer, escribir;

	int o = open(origen, O_RDONLY);

	if(creat(destino, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1)
    {
        perror(destino);
        exit(EXIT_FAILURE);
    }
    
	int d = open(destino, O_WRONLY | O_APPEND);

	struct stat sorigen;
	if(stat(origen, &sorigen) == -1)
    {
    	perror(origen);
    	exit(EXIT_FAILURE);
    }
    printf("ok\n");

   	long long longitud = (long long) sorigen.st_size;
   	char *contenido = (char *)calloc(longitud, sizeof(char));
   


	if(o == -1)
	{
		printf("error o\n");
		perror(origen);
	    exit(-1);
	}
	printf("ok\n");

	if(d == -1)
	{
		printf("error d\n");
		perror(destino);
	    exit(-1);
	}
	printf("ok\n");



	while((leer = read(o, contenido, longitud)) == longitud)
	{
		escribir = write(d, contenido, longitud);
		memset(contenido, '\0', longitud);
	}

	close(o);
	close(d);
}

void *hilo(void *arg)
{
	RUTA *directorios, *raices = (RUTA*)arg;
	struct dirent **dirp;
	pthread_t *id_hilo = (pthread_t*)calloc(1, sizeof(pthread_t));
	int num, i, t = 0;

	num = scandir(raices->Origen, &dirp, NULL, alphasort);

	if(num == -1)
	{
		printf("***error\n");
		perror(raices->Origen);
	    exit(-1);
	}
	
	else if (num > 0)
	{
		printf("***ok\n");
		directorios = (RUTA*)calloc(num, sizeof(RUTA));

		for(i = 0; num--; i++)
		{
			concatenar(directorios[i].Origen, raices->Origen, dirp[num]->d_name);
			if(esDirectorio(directorios[i].Origen))
			{
				if(ignorarPuntos(dirp[num]->d_name))
				{
					concatenar(directorios[i].Destino, raices->Destino, dirp[num]->d_name);
					if(mkdir(directorios[i].Destino,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1)
					{
						perror(directorios[i].Destino);
       					exit(-1);
    				}
    				printf("ok\n");

    				id_hilo = (pthread_t*)realloc(id_hilo, sizeof(pthread_t)*(t+1));
    				pthread_create(&id_hilo[t], NULL, hilo, (void*)&directorios[i]);
    				t++;
				}
			}
			else
			{
				concatenar(directorios[i].Destino, raices->Destino, dirp[num]->d_name);
				copiarArchivo(directorios[i].Origen, directorios[i].Destino);
			}
		}

		for(i = 0; i < t; i++)
			pthread_join(id_hilo[i], NULL);

		free(id_hilo);
		free(directorios);
	}

}

int main(int argc, char *argv[])
{
	RUTA *rutas = (RUTA*)calloc(1, sizeof(RUTA));
	pthread_t id_hilo;
	
	if(argc != 3)
	{
		strcpy(rutas->Origen, "/home/enrike/Escritorio/origen");
		strcpy(rutas->Destino, "/home/enrike/Escritorio/destino");
	}
	else
	{
		strcpy(rutas->Origen, argv[0]);
		strcpy(rutas->Destino, argv[1]);
	}

	if(esDirectorio(rutas->Origen))
	{
		if(mkdir(rutas->Destino, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1)
		{
			perror(rutas->Destino);
	        exit(-1);
	    }
	    else
	    {
	    	pthread_create(&id_hilo, NULL, hilo, (void*)rutas);
	    	pthread_join(id_hilo, NULL);
	    }
	}
	return 0;
}