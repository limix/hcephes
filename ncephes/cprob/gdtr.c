#include "mconf.h"
#include "ncephes/ncephes.h"
#include <math.h>

double ncephes_gdtr(double a, double b, double x) {

    if (x < 0.0) {
        ncephes_mtherr("gdtr", NCEPHES_DOMAIN);
        return (0.0);
    }
    return (ncephes_igam(b, a * x));
}

double ncephes_gdtrc(double a, double b, double x) {

    if (x < 0.0) {
        ncephes_mtherr("gdtrc", NCEPHES_DOMAIN);
        return (0.0);
    }
    return (ncephes_igamc(b, a * x));
}
