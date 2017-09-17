#include "mconf.h"
#include "ncephes/ncephes.h"
#include <math.h>

double ncephes_fdtrc(int ia, int ib, double x) {
    double a, b, w;

    if ((ia < 1) || (ib < 1) || (x < 0.0)) {
        ncephes_mtherr("fdtrc", NCEPHES_DOMAIN);
        return (0.0);
    }
    a = ia;
    b = ib;
    w = b / (b + a * x);
    return (ncephes_incbet(0.5 * b, 0.5 * a, w));
}

double ncephes_fdtr(int ia, int ib, double x) {
    double a, b, w;

    if ((ia < 1) || (ib < 1) || (x < 0.0)) {
        ncephes_mtherr("fdtr", NCEPHES_DOMAIN);
        return (0.0);
    }
    a = ia;
    b = ib;
    w = a * x;
    w = w / (b + w);
    return (ncephes_incbet(0.5 * a, 0.5 * b, w));
}

double ncephes_fdtri(int ia, int ib, double y) {
    double a, b, w, x;

    if ((ia < 1) || (ib < 1) || (y <= 0.0) || (y > 1.0)) {
        ncephes_mtherr("fdtri", NCEPHES_DOMAIN);
        return (0.0);
    }
    a = ia;
    b = ib;
    /* Compute probability for x = 0.5.  */
    w = ncephes_incbet(0.5 * b, 0.5 * a, 0.5);
    /* If that is greater than y, then the solution w < .5.
       Otherwise, solve at 1-y to remove cancellation in (b - b*w).  */
    if (w > y || y < 0.001) {
        w = ncephes_incbi(0.5 * b, 0.5 * a, y);
        x = (b - b * w) / (a * w);
    } else {
        w = ncephes_incbi(0.5 * a, 0.5 * b, 1.0 - y);
        x = b * w / (a * (1.0 - w));
    }
    return (x);
}
