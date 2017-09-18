#include "ncephes/ncephes.h"

double ncephes_chdtrc(double df, double x) {

    if ((x < 0.0) || (df < 1.0)) {
        ncephes_mtherr("chdtrc", NCEPHES_DOMAIN);
        return (0.0);
    }
    return (ncephes_igamc(df / 2.0, x / 2.0));
}

double ncephes_chdtr(double df, double x) {

    if ((x < 0.0) || (df < 1.0)) {
        ncephes_mtherr("chdtr", NCEPHES_DOMAIN);
        return (0.0);
    }
    return (ncephes_igam(df / 2.0, x / 2.0));
}

double ncephes_chdtri(double df, double y) {
    double x;

    if ((y < 0.0) || (y > 1.0) || (df < 1.0)) {
        ncephes_mtherr("chdtri", NCEPHES_DOMAIN);
        return (0.0);
    }

    x = ncephes_igami(0.5 * df, y);
    return (2.0 * x);
}
