// Creacion por copia exacta
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	/* code */
	int i = 10;
	int id_proc;
	id_proc = fork();
	if(id_proc == 0)
	{
		i += 10;
		printf("SOY EL PROCESO HIJO %i\n", i);
		exit(0);
	}
	else
	{
		i += 100;
		printf("SOY EL PROCESO PADRE %i\n", i);
		exit(0);
	}
}


