#include "mconf.h"
#include "ncephes/ncephes.h"
#include <math.h>

double ncephes_nbdtrc(int k, int n, double p) {
    double dk, dn;

    if ((p < 0.0) || (p > 1.0))
        goto domerr;
    if (k < 0) {
    domerr:
        ncephes_mtherr("nbdtr", NCEPHES_DOMAIN);
        return (0.0);
    }

    dk = k + 1;
    dn = n;
    return (ncephes_incbet(dk, dn, 1.0 - p));
}

double ncephes_nbdtr(int k, int n, double p) {
    double dk, dn;

    if ((p < 0.0) || (p > 1.0))
        goto domerr;
    if (k < 0) {
    domerr:
        ncephes_mtherr("nbdtr", NCEPHES_DOMAIN);
        return (0.0);
    }
    dk = k + 1;
    dn = n;
    return (ncephes_incbet(dn, dk, p));
}

double ncephes_nbdtri(int k, int n, double p) {
    double dk, dn, w;

    if ((p < 0.0) || (p > 1.0))
        goto domerr;
    if (k < 0) {
    domerr:
        ncephes_mtherr("nbdtri", NCEPHES_DOMAIN);
        return (0.0);
    }
    dk = k + 1;
    dn = n;
    w = ncephes_incbi(dn, dk, p);
    return (w);
}
