#include "mconf.h"

extern double fabs(double);
extern double floor(double);
extern double exp(double);

#ifdef DEC
#define M 32.0
#define MINV .03125
#else
#define M 128.0
#define MINV .0078125
#endif

extern double MAXLOG;
extern double NCEPHES_INF;

double ncephes_expx2(double x, int sign) {
  double u, u1, m, f;

  x = fabs(x);
  if (sign < 0)
    x = -x;

  /* Represent x as an exact multiple of M plus a residual.
     M is a power of 2 chosen so that exp(m * m) does not overflow
     or underflow and so that |x - m| is small.  */
  m = MINV * floor(M * x + 0.5);
  f = x - m;

  /* x^2 = m^2 + 2mf + f^2 */
  u = m * m;
  u1 = 2 * m * f + f * f;

  if (sign < 0) {
    u = -u;
    u1 = -u1;
  }

  if ((u + u1) > MAXLOG)
    return (NCEPHES_INF);

  /* u is exact, u1 is small.  */
  u = exp(u) * exp(u1);
  return (u);
}
