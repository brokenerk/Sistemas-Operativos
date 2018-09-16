/*
    Descripción: Programa que permite mostrar el contenido de
                 un archivo seleccionado por el usuario y que
                 copia uno o más de los archivos creados a un 
                 directorio previamente establecido.
*/
#include <stdio.h>
#include <windows.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

//void elegirArchivo(char *path);
//void mostrarArchivo(char *path);

/********************************************************/
/*                    FUNCIONES                        */
/******************************************************/
/*
  Función que muestra un archivo, recibe la ruta 
  donde se encuentra dicho archivo.
*/
void mostrarArchivo(char *path)
{
  HANDLE file;
  DWORD BytesEscritos = 0;
  char *contenido = (char*)malloc(100000*sizeof(char));
  file = CreateFile(
         path,
         GENERIC_WRITE | GENERIC_READ,
         FILE_SHARE_READ,
         NULL,
         OPEN_EXISTING,
         FILE_ATTRIBUTE_NORMAL,
         NULL);
  if(ReadFile(file, contenido, 100000, &BytesEscritos, NULL))
      printf("\n Contenido del archivo:\n %s", contenido);
    free(contenido);
    CloseHandle(file);
}
/*
  Función que elige un archivo, recibe la ruta 
  donde se encuentra dicho archivo.
*/
void elegirArchivo(char *path)
{
  // Reservamos memoria para el nombre del archivo
  char *name = (char *)malloc(15*sizeof(char));
  // Reservamos memoria para la ruta final
  char *rutaFinal = (char *)malloc(115*sizeof(char));
  fflush(stdin); // Limpia la entrada
  printf("Nombre del archivo:\n");
  scanf("%s", name);
  // Contatenamos la ruta original con el nombre del archivo
  strcat(strcat(strcpy(rutaFinal, path), "\\\\"), name);
  // Se envia la ruta completa con el nombre del archivo
  mostrarArchivo(rutaFinal);
  free(name);
  free(rutaFinal);
}

int main ()
{
  DIR *dirh;
  struct dirent *dirp;
  struct stat sb;
  int opcion, aopc;
  char ruta[100];
  char nFile[50];
  char auxFile[150] = "";
  char aux[100];
  printf ("Ingrese la ruta del directorio\n");
  scanf ("%s", ruta);
  fflush(stdin);
  if ((dirh = opendir (ruta)) == NULL)
  {
    perror(ruta);
    exit(EXIT_FAILURE);
  }
  // Muestra los archivos del directorio actual
  printf("\n NOMBRE DE LOS ARCHIVOS EN EL DIRECTORIO ACTUAL:\n");    
  for (dirp = readdir (dirh); dirp != NULL; dirp = readdir (dirh))
  {
    char aux[100] = "";
    strcat (aux, ruta);
    strcat (aux, "/");
    strcat (aux, dirp->d_name);
    if(strlen(dirp->d_name)>3)
      printf ("\n%s\t\t", dirp->d_name);
  }  

  opcion = 4;
  // Se muestra menu principal
  while(opcion != 3)
  {
    // Muestra menu principal
    printf("\n\n-----------------------------------------------------------------------");
    printf("\n\t\t\t\tELIGE UNA OPCION");
    printf("\n------------------------------------------------------------------------\n");
    printf("1. Ver contenido de un archivo\n");
    printf("2. Mover archivos \n");
    printf("3. Salir\n");
    printf("Opcion:\n ");
    scanf("%d", &aopc);
    fflush(stdin);
    opcion = aopc;
    if(opcion == 1)
    {
      printf("ENTRA A OPCION 1\n");
      elegirArchivo(ruta);      
    }
    if(opcion == 2)
    {
      printf("\n Selecciona el directorio destino\n");
    }
  }
  closedir(dirh);
  return 0;
}