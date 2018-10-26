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



int numDirectorios(char ruta[]){
	int num = 0;
	DIR *dir = opendir(ruta);
	char *nombre;

    struct dirent *directorios = readdir(dir);

    while (directorios != NULL)
    {
    	nombre=directorios->d_name;

        if (directorios->d_type == DT_DIR && strcmp(nombre,".") && strcmp(nombre,"..")){
            printf("%s\n", nombre);
            num++;
        }

        directorios = readdir(dir);
    }

    closedir(dir);
  	return num;
}

void *hilo(void *arg)
{
	int n2, n;
	n=(int)arg;
	printf("%s\n", n);
	n2=n*2;
	pthread_exit((void*)n2);
}


int main()
{
	int noHilos = 0, i = 0, devol = 0;
	pthread_t id_hilo = 0;
	char ruta[300]="/home/acer/Escritorio";

  	//printf ("Ingrese la ruta del directorio\n");
  	//scanf ("%s", ruta);
  	noHilos = numDirectorios(ruta);


  	pthread_create(&id_hilo, NULL, hilo, (void*)noHilos);
  	pthread_join(id_hilo, (void*)&devol);
  	printf("Devol: %d\n", devol);


}