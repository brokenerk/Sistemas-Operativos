#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <time.h>
#include <pthread.h>
#include <sys/wait.h>

char *ruta[2];
char **directorios;
int num_arc;

char** leerArchivos(char *ruta){
	int num = 0;
	num_arc = 0;
	DIR *dir;
	char **archivos = (char**)calloc(10, sizeof(char*));

	if((dir = opendir(ruta)) == NULL)
	{
    	perror(ruta);
    	exit(-1);
    }

    struct dirent *dirh;

    if((dirh = readdir(dir)) == NULL)
    {
    	perror(ruta);
    	exit(-1);
    }

    while (dirh != NULL)
    {
        if (dirh->d_type != DT_DIR && strcmp(dirh->d_name,".") && strcmp(dirh->d_name,".."))
        {
        	num++;
            archivos = (char**)realloc(archivos,num);
			archivos[num-1] = dirh->d_name;
        }

        dirh = readdir(dir);
    }

    if(closedir(dir) == -1)
    {
    	perror(ruta);
    	exit(-1);
    }

    num_arc = num;

    return archivos;
}

int leerDirectorios(char ruta[])
{
	int num = 0;
	DIR *dir;

	if((dir = opendir(ruta)) == NULL)
	{
    	perror(ruta);
    	exit(-1);
    }

    struct dirent *dirh;

    if((dirh = readdir(dir)) == NULL)
    {
    	perror(ruta);
    	exit(-1);
    }

    while (dirh != NULL)
    {
        if (dirh->d_type == DT_DIR && strcmp(dirh->d_name,".") && strcmp(dirh->d_name,".."))
        {
        	num++;
            directorios = (char**)realloc(directorios,num);
			directorios[num-1] = dirh->d_name;
        }

        dirh = readdir(dir);
    }

    if(closedir(dir) == -1)
    {
    	perror(ruta);
    	exit(-1);
    }

  	return num;
}

void crearDirectorio(char* nuevoDir)
{
	if(mkdir(nuevoDir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) ==-1)
	{
		perror(nuevoDir);
        exit(-1);
    }
    printf("Directorio %s creado", nuevoDir);
    printf("\n");
}

void copiarArchivos(char* nuevoDir)
{
	char* ndir = (char *)calloc(2000, sizeof(char));
	char* dir_arc = (char *)calloc(2000, sizeof(char));
	char *contenido = (char *)calloc(8000, sizeof(char));
	
	strcpy(ndir, nuevoDir);
	char **archivos = leerArchivos(ndir);
	strcat(ndir, "/");

	for(int x = 0; x < num_arc; x++)
	{
		strcpy(dir_arc, "");
		strcpy(dir_arc, ndir);
		strcat(dir_arc, archivos[x]);

		//printf("%s", dir_arc);
		printf("\n");

		int h = open(dir_arc, O_RDONLY);
	    if(h == -1)
	    {
	    	perror(dir_arc);
	    	exit(EXIT_FAILURE);
	    }
	    struct stat sb;
	    stat(dir_arc, &sb);
	    long long longitud = (long long) sb.st_size;
	    char *contenido = (char *)calloc(longitud, sizeof(char));

	    read(h, contenido, longitud);
	    printf("%s", contenido);
		printf("\n");
	    close(h);
	    wait(0);
	    wait(0);
	    wait(0);
	    wait(0);
	}
	
	free(archivos);

}

void* hilo(void *arg)
{
	int n = (int)arg;
	char* dirorigen = (char *)calloc(2000, sizeof(char));
	char* dirdestino = (char *)calloc(2000, sizeof(char));
	
	strcpy(dirorigen,ruta[0]);
	strcpy(dirdestino,ruta[1]);

	strcat(dirorigen,"/");
	strcat(dirdestino,"/");

	strcat(dirorigen,directorios[n]);
	strcat(dirdestino,directorios[n]);

	

	//crearDirectorio(dirdestino);

	copiarArchivos(dirorigen);
	
}


int main(int argc, char *argv[])
{
	int noHilos = 0, i = 0, devol = 0;
	directorios = (char**)calloc(10, sizeof(char*));
	
	
	if(argc != 3)
	{
		ruta[0] = "/home/enrike/Escritorio/origen";
		ruta[1] = "/home/enrike/Escritorio/destino";
	}
	else
	{
		ruta[0] = argv[0];
		ruta[1] = argv[1];
	}

	//Contamos los directorios de la ruta origen
  	noHilos = leerDirectorios(ruta[0]);
  	printf("Numero de directorios: %d\n", noHilos);

  	pthread_t *id_hilo;
	id_hilo = calloc(noHilos,sizeof(pthread_t));

	for (i = 1; i < noHilos; i++) 
	{
		if (pthread_create(&id_hilo[i], NULL, hilo, (void*)i) != 0 ) 
		{
			perror("El hilo no pudo crearse");
			exit(-1);
		}

	}

	hilo(0);

	//Esperar a que terminen los hilos
	for (i = 1; i < noHilos; i++)
	{
		pthread_join (id_hilo[i], NULL);
		//printf("%d\n", devol);
	}

	free(id_hilo);
	return 0;

}