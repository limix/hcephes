#include "mconf.h"

extern double igam(double, double);
extern double igamc(double, double);

double ncephes_gdtr(double a, double b, double x) {

  if (x < 0.0) {
    mtherr("gdtr", DOMAIN);
    return (0.0);
  }
  return (igam(b, a * x));
}

double ncephes_gdtrc(double a, double b, double x) {

  if (x < 0.0) {
    mtherr("gdtrc", DOMAIN);
    return (0.0);
  }
  return (igamc(b, a * x));
}
