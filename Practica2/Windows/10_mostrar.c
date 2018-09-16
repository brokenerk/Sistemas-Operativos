/*
    Descripción: Programa que muestra los archivos de una ruta
                 con su nombre, tamaño, fecha y hora de acceso.
*/
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

int main ()
{
  DIR *dirh;
  struct dirent *dirp;
  struct stat sb;
  char ruta[100];
  char aux[100];
  printf ("Ingrese la ruta del directorio\n");
  scanf ("%s", ruta);
  if ((dirh = opendir (ruta)) == NULL)
  {
    perror(ruta);
    exit(EXIT_FAILURE);
  }

  printf("\n NOMBRE\t\t\t TAMANO\t\t\t FECHA Y HORA \t\t\t\t\n");

  if(readdir(dirh) == NULL)
  {
    perror(ruta);
    exit(EXIT_FAILURE);
  }
    
  for (dirp = readdir (dirh); dirp != NULL; dirp = readdir (dirh))
  {
    char aux[100] = "";
    strcat (aux, ruta);
    strcat (aux, "/");
    strcat (aux, dirp->d_name);
    if(strlen(dirp->d_name)>3)
    {
      printf ("\n%s\t\t", dirp->d_name);
      stat (aux, &sb);
      printf ("%ld bytes\t\t", (long) sb.st_size); // Imprime el tam del archivo 
      printf ("%s", ctime (&sb.st_atime)); // Imprime la fecha y hora
    }
  }
  if(closedir(dirh) == -1)
  {
    perror(ruta);
    exit(EXIT_FAILURE); 
  }
  return 0;
}
