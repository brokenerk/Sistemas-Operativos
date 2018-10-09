#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void nodosEnColados(int n) 
{
	if (n == 0)
		exit(0);

	printf("proceso padre: %d\n", getppid());
	printf("proceso actual %d\n", getpid());
	int parent = fork();
	if (parent == 0) 
	{
		printf("proceso hijo %d\n", getpid());
		nodosEnColados(--n);
		exit(0);
	}
	wait(0);
}

void nodosParalelos(int n) {
	printf("proceso actual %d\n", getpid());
	int idproc=0;
	for (int i = 0; i < n; i++) {
		if ((idproc = fork()) == 0) {
			printf("proceso padre: %d\n", getppid());
			printf("proceso hijo: %d\n", getpid());
			exit(0);
		}
		wait(0);
	}
}
