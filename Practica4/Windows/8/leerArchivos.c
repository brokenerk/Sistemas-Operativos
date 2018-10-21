#include <windows.h>
#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

// Declaracion de funciones
void imprimirArchivo(char *directorio, char *nombre);

int main(int argc, char const *argv[])
{
  char* path = (char*)calloc(2000,sizeof(char));
  strcpy(path, "C:\\Users\\YaKerTaker\\Google Drive\\5to SEMESTRE\\Sistemas-Operativos\\Practica4\\Windows\\8\\Resultados");
  printf(" ----------------------------------\n");
  printf(" ----------- RESULTADOS -----------\n");
  printf(" ----------------------------------\n");
    
  printf("SUMA\n"); imprimirArchivo(path, "suma.txt");
  printf("\nRESTA\n"); imprimirArchivo(path, "resta.txt");
  printf("\nMULTIPLICAR\n"); imprimirArchivo(path, "multiplicacion.txt");
  printf("\nTRANSPUESTA MATRIZ 1\n"); imprimirArchivo(path, "transpuesta1.txt");
  printf("\nTRANSPUESTA MATRIZ 2\n"); imprimirArchivo(path, "transpuesta2.txt");
  printf("\nINVERSA MATRIZ 1\n"); imprimirArchivo(path, "inversa1.txt");
  printf("\nINVERSA MATRIZ 2\n"); imprimirArchivo(path, "inversa2.txt");
  
  return 0;
}

void imprimirArchivo(char *directorio, char *nombre)
{
  char *name = (char *)calloc(150,sizeof(char));
  strcpy(name, nombre);
  char *dir = (char *)calloc(150,sizeof(char));
  // Contatenamos la ruta original con el nombre del archivo
  strcat(strcat(strcpy(dir, directorio), "\\"), name);

  HANDLE file;
  DWORD BytesEscritos = 0;
  char *contenido = (char*)calloc(1000000,sizeof(char));
  file = CreateFile(
         dir,
         GENERIC_WRITE | GENERIC_READ,
         FILE_SHARE_READ,
         NULL,
         OPEN_EXISTING,
         FILE_ATTRIBUTE_NORMAL,
         NULL);

  if(file == INVALID_HANDLE_VALUE)
  {
    printf("Error 1\n");
    perror(dir);
    exit(EXIT_FAILURE);
  }
  else
  {
    if(ReadFile(file, contenido, 1000000, &BytesEscritos, NULL))
    {
      printf("%s", contenido);
    }
    free(contenido);

    if(CloseHandle(file) == 0)
    {
      perror(dir);
      exit(EXIT_FAILURE);
    }
  }

  free(name);
  free(dir);
}