#include "mconf.h"

extern double incbet(double, double, double);
extern double incbi(double, double, double);

double nbdtrc(int k, int n, double p) {
  double dk, dn;

  if ((p < 0.0) || (p > 1.0))
    goto domerr;
  if (k < 0) {
  domerr:
    mtherr("nbdtr", DOMAIN);
    return (0.0);
  }

  dk = k + 1;
  dn = n;
  return (incbet(dk, dn, 1.0 - p));
}

double nbdtr(int k, int n, double p) {
  double dk, dn;

  if ((p < 0.0) || (p > 1.0))
    goto domerr;
  if (k < 0) {
  domerr:
    mtherr("nbdtr", DOMAIN);
    return (0.0);
  }
  dk = k + 1;
  dn = n;
  return (incbet(dn, dk, p));
}

double nbdtri(int k, int n, double p) {
  double dk, dn, w;

  if ((p < 0.0) || (p > 1.0))
    goto domerr;
  if (k < 0) {
  domerr:
    mtherr("nbdtri", DOMAIN);
    return (0.0);
  }
  dk = k + 1;
  dn = n;
  w = incbi(dn, dk, p);
  return (w);
}
