#include <sys/resource.h>
#include <sys/time.h>
#include "tiempo.h"

void uswtime(double *usertime, double *systime, double *walltime)
{
	double mega = 1.0e-6;
	struct rusage buffer;
	struct timeval tp;
	struct timezone tzp;
	getrusage(RUSAGE_SELF, &buffer);
	gettimeofday(&tp, &tzp);
	*usertime = (double) buffer.ru_utime.tv_sec +1.0e-6 * buffer.ru_utime.tv_usec;
	*systime  = (double) buffer.ru_stime.tv_sec +1.0e-6 * buffer.ru_stime.tv_usec;
	*walltime = (double) tp.tv_sec + 1.0e-6 * tp.tv_usec; 
}

/*Modo de Empleo:
La función uswtime se puede emplear para medir los tiempos de ejecución de determinados 
segmentos de código en nuestros programas. 
De forma esquemática, el empleo de esta función constaría de los siguientes pasos:
    1.- Invocar a uswtime para fijar el instante a partir del cual se va a medir el tiempo.
            uswtime(&utime0, &stime0, &wtime0);
    2.- Ejecutar el código cuyo tiempo de ejecución se desea medir.
    3.- Invocar a uswtime para establecer el instante en el cual finaliza la medición
        del tiempo de ejecución.
            uswtime(&utime1, &stime1, &wtime1);
    4.- Calcular los tiempos de ejecución como la diferencia entre la primera y segunda
        invocación a uswtime:

            real:   wtime1 - wtime0*/
