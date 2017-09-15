#include "mconf.h"

extern double ncephes_incbet(double, double, double);

double ncephes_btdtr(double a, double b, double x) {
  return (ncephes_incbet(a, b, x));
}
