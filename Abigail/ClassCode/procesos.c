// Creacipon por copia exacta
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	/* code */
	int id_proc;
	id_proc = fork();
	if(id_proc == 0)
	{
		printf("SOY EL PROCESO HIJO\n");
		exit(0);
	}
	else
	{
		printf("SOY EL PROCESO PADRE\n");
		exit(0);
	}
}
