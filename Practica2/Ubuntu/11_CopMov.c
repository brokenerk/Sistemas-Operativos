/*
    Descripción: Programa que permite mostrar el contenido de
                 un archivo seleccionado por el usuario y que
                 copia uno o más de los archivos creados a un 
                 directorio previamente establecido.
    Observaciones: -> Para copiar un archivo, el archivo no debe
                      existir en la ruta de destino.
                   -> Se debe ingresar un archivo que SI exista
                      en el directorio que al inicio se eligio.
                   -> El archivo se copia con el mismo nombre.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <time.h>

//void elegirArchivo(char *path);
//void mostrarArchivo(char *path);

void mostrarArchivo(char *path)
{
  char name[300];
  printf("Nombre del archivo:\n");
  scanf("%s", name);
  // Concatenamos ruta actual y nombre del archivo
  strcat(path,"/");
  strcat(path, name);
  
  int archivo = open(path, O_RDONLY);
  if(archivo == -1)
  {
    perror(path);
    exit(EXIT_FAILURE);
  }
  struct stat sb;
  if(stat (path, &sb) == -1)
  {
    perror(path);
    exit(EXIT_FAILURE);
  }
  long long longitud = (long long) sb.st_size;
  char *contenido = (char*)calloc(longitud,sizeof(char));
  printf("Contenido:\n");

  if(read(archivo, contenido, longitud) == longitud)
  {
    printf("%s\n", contenido);
  }
  if(close(archivo) == -1)
  {
    perror(path);
    exit(EXIT_FAILURE);
  }
}

/*
  Copia un archivo en otro directorio, dado por el usuario
*/
void copiarArchivo(char *path)
{
  char pathDestino[1000], name[300];
  int archivoOrigen, archivoDestino;
  int opc = 1;
  while(opc == 1)
  {
    printf("Ingrese el destino del archivo\n");
    scanf("%s", pathDestino);
    
    printf("Nombre del archivo:\n");
    scanf("%s", name);
    // Concatenamos ruta actual y nombre del archivo
    strcat(path,"/");
    strcat(path, name);
    // Concatenamos ruta destino y nombre del archivo
    strcat(pathDestino,"/");
    strcat(pathDestino, name);

    archivoOrigen = open (path, O_RDONLY);
    archivoDestino = open (pathDestino, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

    if(archivoOrigen == -1)
    {
      perror(path);
      exit(EXIT_FAILURE);
    }

    struct stat sb;
    if(stat (path, &sb) == -1)
    {
      perror(path);
      exit(EXIT_FAILURE);
    }
    long long longitud = (long long) sb.st_size;
    char *contenido = (char*)calloc(longitud,sizeof(char));

    if(archivoOrigen != -1)
    {
      while(read(archivoOrigen, contenido, longitud) == longitud)
      {
        if(write(archivoDestino, contenido, longitud) == longitud)
        {
          printf("\n************ ARCHIVO COPIADO CON EXITO\n");
        }

      }
      if(close(archivoOrigen) == -1 || close(archivoDestino) == -1)
      {
        perror(path);
        exit(EXIT_FAILURE);
      }  
    }

    printf("Elige un archivo existente\n");
    printf("\n Copiar otro archivo\n");
    printf("1. Si\n");
    printf("2. No\n");
    scanf("%d", &opc);
  }

  
}
/********************************************************/
/*                       MAIN                          */
/******************************************************/

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
      //printf("ENTRA A OPCION 1\n");
      mostrarArchivo(ruta);      
    }
    if(opcion == 2)
    {
      copiarArchivo(ruta);
    }
  }
  if(closedir(dirh) == -1)
  {
    perror(ruta);
    exit(EXIT_FAILURE);
  }
  return 0;
}