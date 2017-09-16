#include "mconf.h"
#include "ncephes/cprob.h"
#include <math.h>

extern double MACHEP, NCEPHES_MAXNUM, MAXLOG, MINLOG;

double ncephes_igami(double a, double y0) {
    double x0, x1, x, yl, yh, y, d, lgm, dithresh;
    int i, dir;

    /* bound the solution */
    x0 = NCEPHES_MAXNUM;
    yl = 0;
    x1 = 0;
    yh = 1.0;
    dithresh = 5.0 * MACHEP;

    /* approximation to inverse function */
    d = 1.0 / (9.0 * a);
    y = (1.0 - d - ncephes_ndtri(y0) * sqrt(d));
    x = a * y * y * y;

    lgm = ncephes_lgam(a);

    for (i = 0; i < 10; i++) {
        if (x > x0 || x < x1)
            goto ihalve;
        y = ncephes_igamc(a, x);
        if (y < yl || y > yh)
            goto ihalve;
        if (y < y0) {
            x0 = x;
            yl = y;
        } else {
            x1 = x;
            yh = y;
        }
        /* compute the derivative of the function at this point */
        d = (a - 1.0) * log(x) - x - lgm;
        if (d < -MAXLOG)
            goto ihalve;
        d = -exp(d);
        /* compute the step to the next approximation of x */
        d = (y - y0) / d;
        if (fabs(d / x) < MACHEP)
            goto done;
        x = x - d;
    }

/* Resort to interval halving if Newton iteration did not converge. */
ihalve:

    d = 0.0625;
    if (x0 == NCEPHES_MAXNUM) {
        if (x <= 0.0)
            x = 1.0;
        while (x0 == NCEPHES_MAXNUM) {
            x = (1.0 + d) * x;
            y = ncephes_igamc(a, x);
            if (y < y0) {
                x0 = x;
                yl = y;
                break;
            }
            d = d + d;
        }
    }
    d = 0.5;
    dir = 0;

    for (i = 0; i < 400; i++) {
        x = x1 + d * (x0 - x1);
        y = ncephes_igamc(a, x);
        lgm = (x0 - x1) / (x1 + x0);
        if (fabs(lgm) < dithresh)
            break;
        lgm = (y - y0) / y0;
        if (fabs(lgm) < dithresh)
            break;
        if (x <= 0.0)
            break;
        if (y >= y0) {
            x1 = x;
            yh = y;
            if (dir < 0) {
                dir = 0;
                d = 0.5;
            } else if (dir > 1)
                d = 0.5 * d + 0.5;
            else
                d = (y0 - yl) / (yh - yl);
            dir += 1;
        } else {
            x0 = x;
            yl = y;
            if (dir > 0) {
                dir = 0;
                d = 0.5;
            } else if (dir < -1)
                d = 0.5 * d;
            else
                d = (y0 - yl) / (yh - yl);
            dir -= 1;
        }
    }
    if (x == 0.0)
        ncephes_mtherr("igami", NCEPHES_UNDERFLOW);

done:
    return (x);
}
