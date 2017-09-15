#include "mconf.h"

extern double ncephes_incbet(double, double, double);
extern double ncephes_incbi(double, double, double);

double ncephes_nbdtrc(int k, int n, double p) {
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
  return (ncephes_incbet(dk, dn, 1.0 - p));
}

double ncephes_nbdtr(int k, int n, double p) {
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
  return (ncephes_incbet(dn, dk, p));
}

double ncephes_nbdtri(int k, int n, double p) {
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
  w = ncephes_incbi(dn, dk, p);
  return (w);
}
