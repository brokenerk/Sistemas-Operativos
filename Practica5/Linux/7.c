//Compilar: gcc 7.c -lpthread -o 7
//Ejecutar: ./7 [RutaOrigen] [RutaDestino]

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <pthread.h>

//Estructura para manejar la ruta origen y destino
typedef struct{
	char Origen[400];
	char Destino[400];
} RUTA;

//Función que ignora los archivos y solo lee directorios
int esDirectorio(char path[])
{
	//Nos ayuda para consultar info del directorio/archivo escaneado
	struct stat sb;

	if(stat(path, &sb) == -1)
	{
		perror(path);
	    exit(-1);
	}

	//Revisamos el tipo
	if(S_ISDIR(sb.st_mode))
		return 1;
	else 
		return 0;
}

void concatenar(char dir[], char aux[], char nombre[])
{
	//Concatener directorio y archivo
	strcpy(dir, aux);
	strcat(dir, "/");
	strcat(dir, nombre);
}

int ignorarPuntos(char nombre[])
{
	//Al escanear un directorio, aparecen puntos
	//Con este funcion, los eliminamos para trabajar solo con directorios/archivos
	if(strcmp(nombre, ".") && strcmp(nombre, ".."))
		return 1;
	else
		return 0;
}

void copiarArchivo(char origen[], char destino[])
{
	ssize_t leer, escribir;
	//Llamada al sistema open recibe la ruta del archivo a abrir y el modo (lectura, escritura, ejecucion)
    //Devuelve un descriptor de archivo
	int o = open(origen, O_RDONLY);//Abrimos la ruta origen

	//Llamada al sistema creat recibe la ruta del archivo a crear y los permisos
    //Retorna -1 si existieron errores
	if(creat(destino, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1)
    {
        perror(destino);
        exit(EXIT_FAILURE);
    }
    
    //Abrimos la ruta destino
	int d = open(destino, O_WRONLY | O_APPEND);

	//Nos ayuda para consultar info del directorio/archivo escaneado
	struct stat sorigen;
	if(stat(origen, &sorigen) == -1)
    {
    	perror(origen);
    	exit(EXIT_FAILURE);
    }

    //Obtenemos la longitud en bytes del archivo con ayuda de stat
   	long long longitud = (long long) sorigen.st_size;
   	//Creamos un buffer para ir guardando el contenido del archivo
   	char *contenido = (char *)calloc(longitud, sizeof(char));
   
	if(o == -1)
	{
		perror(origen);
	    exit(-1);
	}

	if(d == -1)
	{
		perror(destino);
	    exit(-1);
	}

	//Leemos el archivo origen y lo escribimos en el destino
	while((leer = read(o, contenido, longitud)) == longitud)
	{
		escribir = write(d, contenido, longitud);
		//Establecemos el fin del contenido
		memset(contenido, '\0', longitud);
		printf("%s ..... COPIADO", destino);
		printf("\n\n");
	}

	close(o);
	close(d);
}

//Funciones que ejecutaran los hilos creados
void *hilo(void *arg)
{
	//Utilizamos la estructura que creamos
	RUTA *directorios, *raices = (RUTA*)arg;
	//Nos sirve para leer todos los directorios contenidos en una ruta
	struct dirent **dirp;
	//Creamos un hilo
	pthread_t *id_hilo = (pthread_t*)calloc(1, sizeof(pthread_t));
	int num, i, t = 0;

	//Leemos la ruta origen en busca de directorios
	num = scandir(raices->Origen, &dirp, NULL, alphasort);

	if(num == -1)
	{
		perror(raices->Origen);
	    exit(-1);
	}
	else if (num > 0)
	{

		//Reasignamos memoria para guardar los directorios encontrados
		directorios = (RUTA*)calloc(num, sizeof(RUTA));
		for(i = 0; num--; i++)
		{
			//Vamos construyendo las rutas de los directorios origen
			concatenar(directorios[i].Origen, raices->Origen, dirp[num]->d_name);
			if(esDirectorio(directorios[i].Origen))
			{
				if(ignorarPuntos(dirp[num]->d_name))
				{
					printf("Soy el hilo %d. Encontre: %s", i, directorios[i].Origen);
					printf("\n");

					//Solo nos quedamos con directorios y construimos las rutas de destino
					concatenar(directorios[i].Destino, raices->Destino, dirp[num]->d_name);
					printf("Soy el hilo %d. Creare: %s", i, directorios[i].Destino);
					printf("\n\n");
					//Creamos los directorios destino
					if(mkdir(directorios[i].Destino,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1)
					{
						perror(directorios[i].Destino);
       					exit(-1);
    				}
    				//Vamos creando un nuevo hilo por cada directorio encontrado
    				id_hilo = (pthread_t*)realloc(id_hilo, sizeof(pthread_t)*(t+1));
    				pthread_create(&id_hilo[t], NULL, hilo, (void*)&directorios[i]);
    				t++;
				}
			}
			else
			{
				//Ahora, creamos las rutas para los archivos dentro de cada directorio
				concatenar(directorios[i].Destino, raices->Destino, dirp[num]->d_name);
				printf("Copiare el archivo: %s", directorios[i].Origen);
				printf("\n");
				//Leemos y escribimos los archivos
				copiarArchivo(directorios[i].Origen, directorios[i].Destino);
			}
		}
		//Esperamos a que todos los hilos acaben
		for(i = 0; i < t; i++)
			pthread_join(id_hilo[i], NULL);

		free(id_hilo);
		free(directorios);
	}

}

int main(int argc, char *argv[])
{
	//Creamos las rutas origen y destino
	RUTA *rutas = (RUTA*)calloc(1, sizeof(RUTA));
	pthread_t id_hilo;
	
	//Si no se ingresaron rutas por linea de comandos, tomamos las predeterminadas
	if(argc != 3)
	{
		strcpy(rutas->Origen, "/home/enrike/Escritorio/origen");
		strcpy(rutas->Destino, "/home/enrike/Escritorio/destino");
	}
	else
	{
		strcpy(rutas->Origen, argv[1]);
		strcpy(rutas->Destino, argv[2]);
	}

	printf("Ruta Origen: %s",rutas->Origen);
	printf("\n");
	printf("Ruta Destino: %s",rutas->Destino);
	printf("\n\n\n");
	/*Revisamos la ruta ingresada es un directorio, y que los directorios de origen
	no existan en la ruta destino*/
	if(esDirectorio(rutas->Origen))
	{
		if(mkdir(rutas->Destino, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1)
		{
			perror(rutas->Destino);
	        exit(-1);
	    }
	    else
	    {
	    	//Creamos un hilo y enviamos las rutas
	    	pthread_create(&id_hilo, NULL, hilo, (void*)rutas);
	    	pthread_join(id_hilo, NULL);
	    }
	}
	return 0;
}