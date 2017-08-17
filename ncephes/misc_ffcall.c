#include "ncephes/misc.h"

double beta(double a, double b);
double lbeta(double a, double b);

double ncephes_beta(double a, double b) { return beta(a, b); }
double ncephes_lbeta(double a, double b) { return lbeta(a, b); }

