
#include "ncephes/ncephes.h"


double ncephes_btdtr(double a, double b, double x) {
    return (ncephes_incbet(a, b, x));
}
