#include "mconf.h"
#include "ncephes/ncephes.h"
#include <math.h>

double ncephes_btdtr(double a, double b, double x) {
    return (ncephes_incbet(a, b, x));
}
