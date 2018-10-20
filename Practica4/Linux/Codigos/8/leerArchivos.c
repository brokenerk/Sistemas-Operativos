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

// Declaracion de funciones
void imprimirArchivo(char *directorio, char *nombre);

int main(int argc, char const *argv[])
{
  char* path = (char*)calloc(2000,sizeof(char));
  strcpy(path, "/home/enrike/Escritorio/P4-SO/8/Resultados");
  printf(" ----------------------------------\n");
  printf(" ----------- RESULTADOS -----------\n");
  printf(" ----------------------------------\n");
    
  printf("SUMA\n"); imprimirArchivo(path, "/suma.txt");
  printf("\nRESTA\n"); imprimirArchivo(path, "/resta.txt");
  printf("\nMULTIPLICAR\n"); imprimirArchivo(path, "/multiplicacion.txt");
  printf("\nTRANSPUESTA MATRIZ 1\n"); imprimirArchivo(path, "/tran1.txt");
  printf("\nTRANSPUESTA MATRIZ 2\n"); imprimirArchivo(path, "/tran2.txt");
  printf("\nINVERSA MATRIZ 1\n"); imprimirArchivo(path, "/inv_1.txt");
  printf("\nINVERSA MATRIZ 2\n"); imprimirArchivo(path, "/inv_2.txt");
  
  return 0;
}

void imprimirArchivo(char *directorio, char *nombre)
{
	char* dir = (char *)calloc(2000, sizeof(char));
  char* aux = (char *)calloc(2000, sizeof(char));
  strcpy(aux, directorio);
  strcpy(dir, directorio);
  strcat(dir, nombre);

  int archivo = open(dir, O_RDONLY);
  if(archivo == -1)
  {
    perror(dir);
    exit(EXIT_FAILURE);
  }
  struct stat sb;
  if(stat(dir, &sb) == -1)
  {
    perror(dir);
    exit(EXIT_FAILURE);
  }
  long long longitud = (long long) sb.st_size;
  char *contenido = (char *)calloc(longitud, sizeof(char));
   
  if(read(archivo, contenido, longitud) == longitud)
  {
   	printf("%s", contenido);
  }
  if(close(archivo) == -1)
  {
   	perror(dir);
   	exit(EXIT_FAILURE);
  }
  strcpy(directorio, aux); 
}