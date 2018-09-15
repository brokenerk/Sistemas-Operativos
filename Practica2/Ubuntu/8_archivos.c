#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char* leerDirectorio(){
	char* directorio = (char*)malloc(2000*sizeof(char));
	printf("Ingrese el nuevo directorio: ");
	scanf("%s", directorio);
	return directorio;
}

void escribirArchivo(int archivo_abierto, char content[10][1000], int k, int r, char* ruta){
	//Si el descriptor de archivo devuelve -1, existieron errores
	if(archivo_abierto == -1)
    {
        perror(ruta);
        exit(EXIT_FAILURE);
    }
    else
    {
        for(int j=0 ; j<r*5 ; j++)//Escribimos 5 veces el texto en el archivo
        {
        	//Llamada al sistema write recibe un descriptor de archivo, el contenido a escribir y la longitud del contenido
        	//Devuelve la cantidad de bytes escritos
            if(write(archivo_abierto, content[k], strlen(content[k])) == strlen (content[k]))
            {
                if(k==r-1 && k==j)//Revisamos que ya leimos todos los contenidos y terminamos
                {
                    printf("%d Archivos creados\n", r);
                }
            }
            else
            {
                perror(ruta);
                exit(EXIT_FAILURE);
            }
        }
         //Llamada al sistema close recibe un descriptor de archivo y retorna un valor cero si no han habido errores
        if(close(archivo_abierto) != 0 )
        {
            perror(ruta);
            exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, const char *argv[])
{
	srand (time(NULL)); //Funcion para generar aleatorios
	char contenido[10][1000] = {"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Lorem ipsum dolor sit amet, consectetur adipiscing elit. nposuere iaculis libero.",
								 "Suspendisse mollis massa id arcu efficitur venenatis. Suspendisse mollis massa id arcu efficitur venenatis. non, posuere iaculis libero.", 
								 "Mauris tortor tellus, accumsan vel libero non, posuere iaculis libero. Mauris tortor tellus, accumsan vel libero non, posuere iaculis libero.", 
								 "Phasellus ut massa auctor, condimentum urna a, rhoncus felis. Phasellus ut massa auctor, condimentum urna a, rhoncus felis. non, posuere. ", 
								 "Pellentesque urna justo, pretium nec aliquet a, tincidunt nec elit. Pellentesque urna justo, pretium nec aliquet a, tincidunt nec elit.", 
								 "Donec ac lorem aliquam, suscipit massa nec, mollis lorem. Donec ac lorem aliquam, suscipit massa nec, mollis lorem. non, posuere iaculis.",
								 "Maecenas venenatis turpis sem, ut dignissim nibh consectetur id. Maecenas venenatis turpis sem, ut dignissim nibh consectetur id. non, posuere.",
								 "In sit amet risus orci. Nulla elementum purus vitae tincidunt commodo. In sit amet risus orci. Nulla elementum purus vitae tincidunt commodo.",
								 "Integer laoreet cursus odio, sed consequat tellus pellentesque ac. Integer laoreet cursus odio, sed consequat tellus pellentesque ac. Integer.",
								 "Class taciti sociosqu ad litora torquent per conubia nostra, per inceptos. Class taciti sociosqu ad litora torquent per conubia nostra, per inceptos."};

	char* path = leerDirectorio();//Obtenemos el directorio desde la entrada de teclado

	//Llamda al sistema mkdir recibe la ruta del directorio a crear, y los permisos de escritura, lectura y ejecucion para cada tipo de usuario
	//Retorna -1 si ocurrieron errores
	if(mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) ==-1)
	{
		perror(path);
        exit(EXIT_FAILURE);
    }
    else
    {
    	printf("\nEste es el directorio creado: %s\n", path);
    	strcat(path, "/archivo");//Concatenamos a la ruta con strcat()
    	char* dir=(char*)calloc(2000,sizeof(char));
    	int random = (rand()%10)+1;//Creamos numeros aleatorios de 1 a 10 
    	char numero[10];

    	for(int i=0; i<random; i++)
    	{
    		strcpy(dir, path);//Copiamos a cada salto la cadena path a la cadena dir para limpiarla
    		//Damos formato de cadena y concatenamos el numero de archivo generado por el ciclo y agregamos la extension TXT
    		sprintf(numero,"%d",i+1);
    		strcat(dir, numero);
    		strcat(dir, ".txt");

    		//Llamada al sistema creat recibe la ruta del archivo a crear y los permisos
    		//Retorna -1 si existieron errores
    		if(creat(dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1)
    		{
    			perror(dir);
        		exit(EXIT_FAILURE);
    		}
    		else
    		{
    			//Llamada al sistema open recibe la ruta del archivo a abrir y el modo (lectura, escritura, ejecucion)
    			//Devuelve un descriptor de archivo
    			escribirArchivo(open(dir, O_WRONLY | O_APPEND), contenido, i, random, dir);
    		}
    	}
    }
    return 0;
}

