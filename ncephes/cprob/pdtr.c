#include "mconf.h"
#include "ncephes/cprob.h"
#include <math.h>

double ncephes_pdtrc(int k, double m) {
    double v;

    if ((k < 0) || (m <= 0.0)) {
        mtherr("pdtrc", DOMAIN);
        return (0.0);
    }
    v = k + 1;
    return (ncephes_igam(v, m));
}

double ncephes_pdtr(int k, double m) {
    double v;

    if ((k < 0) || (m <= 0.0)) {
        mtherr("pdtr", DOMAIN);
        return (0.0);
    }
    v = k + 1;
    return (ncephes_igamc(v, m));
}

double ncephes_pdtri(int k, double y) {
    double v;

    if ((k < 0) || (y < 0.0) || (y >= 1.0)) {
        mtherr("pdtri", DOMAIN);
        return (0.0);
    }
    v = k + 1;
    v = ncephes_igami(v, y);
    return (v);
}
