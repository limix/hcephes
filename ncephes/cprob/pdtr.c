#include "mconf.h"

extern double igam(double, double);
extern double igamc(double, double);
extern double igami(double, double);

double pdtrc(int k, double m) {
  double v;

  if ((k < 0) || (m <= 0.0)) {
    mtherr("pdtrc", DOMAIN);
    return (0.0);
  }
  v = k + 1;
  return (igam(v, m));
}

double pdtr(int k, double m) {
  double v;

  if ((k < 0) || (m <= 0.0)) {
    mtherr("pdtr", DOMAIN);
    return (0.0);
  }
  v = k + 1;
  return (igamc(v, m));
}

double pdtri(int k, double y) {
  double v;

  if ((k < 0) || (y < 0.0) || (y >= 1.0)) {
    mtherr("pdtri", DOMAIN);
    return (0.0);
  }
  v = k + 1;
  v = igami(v, y);
  return (v);
}
