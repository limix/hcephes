#include "mconf.h"
#include "ncephes/misc.h"
#include "ncephes/polyn.h"
#include <stdlib.h>

extern int MAXPOL; /* initialized by polini() */

void ncephes_revers(double y[], double x[], int n) {
    double *yn, *yp, *ysum;
    int j;

    if (y[1] == 0.0)
        ncephes_mtherr("revers", NCEPHES_DOMAIN);

    j = (MAXPOL + 1) * sizeof(double);
    yn = (double *)malloc(j);
    yp = (double *)malloc(j);
    ysum = (double *)malloc(j);

    ncephes_polmov(y, n, yn);
    ncephes_polclr(ysum, n);
    x[0] = 0.0;
    x[1] = 1.0 / y[1];
    for (j = 2; j <= n; j++) {
        /* A_(j-1) times the expansion of y^(j-1)  */
        ncephes_polmul(&x[j - 1], 0, yn, n, yp);
        /* The expansion of the sum of A_k y^k up to k=j-1 */
        ncephes_poladd(yp, n, ysum, n, ysum);
        /* The expansion of y^j */
        ncephes_polmul(yn, n, y, n, yn);
        /* The coefficient A_j to make the sum up to k=j equal to zero */
        x[j] = -ysum[j] / yn[j];
    }
    free(yn);
    free(yp);
    free(ysum);
}
