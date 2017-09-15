#include "mconf.h"

extern double incbet(double, double, double);

double ncephes_btdtr(double a, double b, double x) { return (incbet(a, b, x)); }
