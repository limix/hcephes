#include "mconf.h"

extern double incbet(double, double, double);
extern double incbi(double, double, double);

double ncephes_fdtrc(int ia, int ib, double x) {
  double a, b, w;

  if ((ia < 1) || (ib < 1) || (x < 0.0)) {
    mtherr("fdtrc", DOMAIN);
    return (0.0);
  }
  a = ia;
  b = ib;
  w = b / (b + a * x);
  return (incbet(0.5 * b, 0.5 * a, w));
}

double ncephes_fdtr(int ia, int ib, double x) {
  double a, b, w;

  if ((ia < 1) || (ib < 1) || (x < 0.0)) {
    mtherr("fdtr", DOMAIN);
    return (0.0);
  }
  a = ia;
  b = ib;
  w = a * x;
  w = w / (b + w);
  return (incbet(0.5 * a, 0.5 * b, w));
}

double ncephes_fdtri(int ia, int ib, double y) {
  double a, b, w, x;

  if ((ia < 1) || (ib < 1) || (y <= 0.0) || (y > 1.0)) {
    mtherr("fdtri", DOMAIN);
    return (0.0);
  }
  a = ia;
  b = ib;
  /* Compute probability for x = 0.5.  */
  w = incbet(0.5 * b, 0.5 * a, 0.5);
  /* If that is greater than y, then the solution w < .5.
     Otherwise, solve at 1-y to remove cancellation in (b - b*w).  */
  if (w > y || y < 0.001) {
    w = incbi(0.5 * b, 0.5 * a, y);
    x = (b - b * w) / (a * w);
  } else {
    w = incbi(0.5 * a, 0.5 * b, 1.0 - y);
    x = b * w / (a * (1.0 - w));
  }
  return (x);
}
