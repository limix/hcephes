#include "mconf.h"
#include "ncephes/cprob.h"
#include <math.h>

double ncephes_gdtr(double a, double b, double x) {

    if (x < 0.0) {
        mtherr("gdtr", DOMAIN);
        return (0.0);
    }
    return (ncephes_igam(b, a * x));
}

double ncephes_gdtrc(double a, double b, double x) {

    if (x < 0.0) {
        mtherr("gdtrc", DOMAIN);
        return (0.0);
    }
    return (ncephes_igamc(b, a * x));
}
