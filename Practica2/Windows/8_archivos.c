#include <windows.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

char* leerDirectorio(){
	char* directorio = (char*)malloc(2000*sizeof(char));
	printf("Ingrese el nuevo directorio: ");
	scanf("%s", directorio);
	return directorio;
}

void escribirArchivo(HANDLE harchivo, char content[10][1000], int k, int r, char* ruta){
    DWORD bytesEscritos = 0;
	for(int j=0 ; j<r*5 ; j++)
	{
		BOOL escribir = WriteFile( 
                    harchivo,           		// abrir handle del archivo
                    content[k],      			// informacion a escribir
                    (DWORD)strlen(content[k]),  // tamaño de bytes a escribir
                    &bytesEscritos, 			// tamaño de bytes escrit
                    NULL);           			// no overlapped structure

    	if(escribir)
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
    				
    if(CloseHandle(harchivo) == 0)
    {
    	perror(ruta);
    	exit(EXIT_FAILURE);
    }
}

int main(int argc, const char *argv[])
{
	system("cls");
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

	if(!CreateDirectory(path, NULL))
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
    		HANDLE h = CreateFile(dir,						//ruta del archivo
							      GENERIC_WRITE,			//abrir para escribir
							      0,						//no compartir
							      NULL,						// seguridad por default
							      CREATE_NEW,				//crear nuevo archivo solamente
							      FILE_ATTRIBUTE_TEMPORARY,	//archivo normal
							      NULL);					//sin tributos

    		if (h == INVALID_HANDLE_VALUE)
    		{
    			perror(dir);
        		exit(EXIT_FAILURE);
    		}
    		else
    		{
    			escribirArchivo(h, contenido, i, random, dir);
    		}
    	}
	
    }
    return 0;
}

