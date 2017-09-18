#include "hcephes/hcephes.h"

double hcephes_btdtr(double a, double b, double x) {
    return (hcephes_incbet(a, b, x));
}
