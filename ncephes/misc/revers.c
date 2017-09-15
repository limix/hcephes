#include "mconf.h"
#include <stdlib.h>

extern int MAXPOL; /* initialized by polini() */

#ifdef ANSIPROT
/* See polyn.c.  */
void polmov(double *, int, double *);
void polclr(double *, int);
void poladd(double *, int, double *, int, double *);
void polmul(double *, int, double *, int, double *);
void free(void *);
#else
void polmov(), polclr(), poladd(), polmul();
void free();
#endif

void revers(double y[], double x[], int n) {
    double *yn, *yp, *ysum;
    int j;

    if (y[1] == 0.0)
        ncephes_mtherr("revers", DOMAIN);
    /*	printf( "revers: y[1] = 0\n" );*/
    j = (MAXPOL + 1) * sizeof(double);
    yn = (double *)malloc(j);
    yp = (double *)malloc(j);
    ysum = (double *)malloc(j);

    polmov(y, n, yn);
    polclr(ysum, n);
    x[0] = 0.0;
    x[1] = 1.0 / y[1];
    for (j = 2; j <= n; j++) {
        /* A_(j-1) times the expansion of y^(j-1)  */
        polmul(&x[j - 1], 0, yn, n, yp);
        /* The expansion of the sum of A_k y^k up to k=j-1 */
        poladd(yp, n, ysum, n, ysum);
        /* The expansion of y^j */
        polmul(yn, n, y, n, yn);
        /* The coefficient A_j to make the sum up to k=j equal to zero */
        x[j] = -ysum[j] / yn[j];
    }
    free(yn);
    free(yp);
    free(ysum);
}

#if 0
/* Demonstration program
 */
#define N 10
double y[N], x[N];
double fac();

int
main (void)
{
double a, odd;
int i;

polini( N-1 );
a = 1.0;
y[0] = 0.0;
odd = 1.0;
for( i=1; i<N; i++ )
	{
/* sin(x) */
/*
	if( i & 1 )
		{
		y[i] = odd/fac(i);
		odd = -odd;
		}
	else
		y[i] = 0.0;
*/
	y[i] = 1.0/fac(i);
	}
revers( y, x, N-1 );
for( i=0; i<N; i++ )
	printf( "%2d %.10e %.10e\n", i, x[i], y[i] );
}
#endif
