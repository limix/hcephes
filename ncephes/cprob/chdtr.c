#include "mconf.h"

extern double ncephes_igamc(double, double);
extern double ncephes_igam(double, double);
extern double ncephes_igami(double, double);

double ncephes_chdtrc(double df, double x) {

  if ((x < 0.0) || (df < 1.0)) {
    mtherr("chdtrc", DOMAIN);
    return (0.0);
  }
  return (ncephes_igamc(df / 2.0, x / 2.0));
}

double ncephes_chdtr(double df, double x) {

  if ((x < 0.0) || (df < 1.0)) {
    mtherr("chdtr", DOMAIN);
    return (0.0);
  }
  return (ncephes_igam(df / 2.0, x / 2.0));
}

double ncephes_chdtri(double df, double y) {
  double x;

  if ((y < 0.0) || (y > 1.0) || (df < 1.0)) {
    mtherr("chdtri", DOMAIN);
    return (0.0);
  }

  x = ncephes_igami(0.5 * df, y);
  return (2.0 * x);
}
