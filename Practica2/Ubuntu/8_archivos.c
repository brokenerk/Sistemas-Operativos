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
	if(archivo_abierto == -1)
    {
        perror(ruta);
        exit(EXIT_FAILURE);
    }
    else
    {
        for(int j=0 ; j<r*5 ; j++)//Escribimos 5 veces el texto en el archivo
        {
            if(write(archivo_abierto, content[k], strlen(content[k])) == strlen (content[k]))
            {
                if(k==r-1 && k==j)
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
                     
        if(close(archivo_abierto) != 0 )
        {
            perror(ruta);
            exit(EXIT_FAILURE);
        }
    }
    
}

int main(int argc, const char *argv[])
{
	srand (time(NULL));
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

	char* path = leerDirectorio();

	if(mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) ==-1)
	{
		perror(path);
        exit(EXIT_FAILURE);
    }
    else
    {
    	printf("\nEste es el directorio creado: %s\n", path);
    	
    	strcat(path, "/archivo");
    	char* dir=(char*)calloc(2000,sizeof(char));
    	int random = (rand()%10)+1;
    	char numero[10];

    	for(int i=0; i<random; i++)
    	{
    		strcpy(dir, path);
    		sprintf(numero,"%d",i+1);
    		strcat(dir, numero);
    		strcat(dir, ".txt");

    		if(creat(dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1)
    		{
    			perror(dir);
        		exit(EXIT_FAILURE);
    		}
    		else
    		{
    			escribirArchivo(open(dir, O_WRONLY | O_APPEND), contenido, i, random, dir);
    		}
    	}

    }
    return 0;
}

