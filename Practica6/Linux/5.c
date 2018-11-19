#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void *hilo10(void *arg);
void *hilo5(void *arg);
void *hiloTerminal(void *arg);

int main(void)
{
	int id_proc;
    id_proc = fork();
    if(id_proc == 0)
    {
        printf("Soy el proceso hilador\n");
        pthread_t id_hilo;
        for(int i = 0; i < 15; i++)
        {
            printf("\nHe creado %d / 15 hilos", i + 1);
            pthread_create(&id_hilo, NULL, (void*)hilo10, NULL);
            sleep(0);
            for(int ii = 0; ii < 15; ii++)
            {
            	pthread_join(id_hilo,NULL);
            }
        }
        return 0;
    }
    else
    {
        printf("Soy padre del proceso hilador\n");
        exit(0);
    }
}

void *hilo10(void *arg)
{
    printf(" id = %lu", pthread_self());
    pthread_t id_hilo;
    for(int j = 0; j < 10; j++)
    {
        printf("\n\tHe creado %d / 10 hilos", j + 1);
 		pthread_create(&id_hilo, NULL, (void*)hilo5, NULL);
        for(int jj = 0; jj < 10; jj++)
        {
        	pthread_join(id_hilo,NULL);
        }
    }
    return NULL;
}

void *hilo5(void *arg)
{
    sleep(0);
    printf(" id = %lu", pthread_self());
    pthread_t id_hilo;
    for(int i = 0; i < 5; i++)
    {
        printf("\n\t\tHe creado %d / 5 hilos", i + 1);
        pthread_create(&id_hilo, NULL, (void*)hiloTerminal, NULL);
        for(int ii = 0; ii < 5; ii++)
        {
            pthread_join(id_hilo,NULL);
        }
    }
    return NULL;
}

void *hiloTerminal(void *arg)
{
	printf(" id = %lu\n", pthread_self());
    printf("\t\t\tHijo Terminal Practica 5");
    return NULL;
}