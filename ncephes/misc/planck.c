#include "mconf.h"

extern double ncephes_polylog(int, double);
extern double exp(double);
extern double ncephes_log1p(double); /* log(1+x) */
extern double ncephes_expm1(double); /* exp(x) - 1 */
double ncephes_planckc(double, double);
double ncephes_plancki(double, double);

/*  NIST value (1999): 2 pi h c^2 = 3.741 7749(22) �� 10-16 W m2  */
double planck_c1 = 3.7417749e-16;
/*  NIST value (1999):  h c / k  = 0.014 387 69 m K */
double planck_c2 = 0.01438769;

double ncephes_plancki(double w, double T) {
    double b, h, y, bw;

    b = T / planck_c2;
    bw = b * w;

    if (bw > 0.59375) {
        y = b * b;
        h = y * y;
        /* Right tail.  */
        y = ncephes_planckc(w, T);
        /* pi^4 / 15  */
        y = 6.493939402266829149096 * planck_c1 * h - y;
        return y;
    }

    h = exp(-planck_c2 / (w * T));
    y = 6. * ncephes_polylog(4, h) * bw;
    y = (y + 6. * ncephes_polylog(3, h)) * bw;
    y = (y + 3. * ncephes_polylog(2, h)) * bw;
    y = (y - ncephes_log1p(-h)) * bw;
    h = w * w;
    h = h * h;
    y = y * (planck_c1 / h);
    return y;
}

/*							ncephes_planckc
 *
 *	Complemented Planck radiation integral
 *
 *
 *
 * SYNOPSIS:
 *
 * double lambda, T, y, ncephes_planckc();
 *
 * y = ncephes_planckc( lambda, T );
 *
 *
 *
 * DESCRIPTION:
 *
 *  Integral from w to infinity (area under right hand tail)
 *  of Planck's radiation formula.
 *
 *  The program for large lambda uses an asymptotic series in inverse
 *  powers of the wavelength.
 *
 * ACCURACY:
 *
 *                      Relative error.
 *   The domain refers to lambda T / c2.
 * arithmetic   domain     # trials      peak         rms
 *    IEEE      0.6, 10      50000      1.1e-15     2.2e-16
 *
 */

double ncephes_planckc(double w, double T) {
    double b, d, p, u, y;

    b = T / planck_c2;
    d = b * w;
    if (d <= 0.59375) {
        y = 6.493939402266829149096 * planck_c1 * b * b * b * b;
        return (y - ncephes_plancki(w, T));
    }
    u = 1.0 / d;
    p = u * u;
#if 0
  y = 236364091.*p/365866013534056632601804800000.;
  y = (y - 15458917./475677107995483570176000000.)*p;
  y = (y + 174611./123104841613737984000000.)*p;
  y = (y - 43867./643745871363538944000.)*p;
  y = ((y + 3617./1081289781411840000.)*p - 1./5928123801600.)*p;
  y = ((y + 691./78460462080000.)*p - 1./2075673600.)*p;
  y = ((((y + 1./35481600.)*p - 1.0/544320.)*p + 1.0/6720.)*p -  1./40.)*p;
  y = y + log(d * ncephes_expm1(u));
  y = y - 5.*u/8. + 1./3.;
#else
    y = -236364091. * p / 45733251691757079075225600000.;
    y = (y + 77683. / 352527500984795136000000.) * p;
    y = (y - 174611. / 18465726242060697600000.) * p;
    y = (y + 43867. / 107290978560589824000.) * p;
    y = ((y - 3617. / 202741834014720000.) * p + 1. / 1270312243200.) * p;
    y = ((y - 691. / 19615115520000.) * p + 1. / 622702080.) * p;
    y = ((((y - 1. / 13305600.) * p + 1. / 272160.) * p - 1. / 5040.) * p +
         1. / 60.) *
        p;
    y = y - 0.125 * u + 1. / 3.;
#endif
    y = y * planck_c1 * b / (w * w * w);
    return y;
}

/*							ncephes_planckd
 *
 *	Planck's black body radiation formula
 *
 *
 *
 * SYNOPSIS:
 *
 * double lambda, T, y, ncephes_planckd();
 *
 * y = ncephes_planckd( lambda, T );
 *
 *
 *
 * DESCRIPTION:
 *
 *  Evaluates Planck's radiation formula
 *                      -5
 *            c1  lambda
 *     E =  ------------------
 *            c2/(lambda T)
 *           e             - 1
 *
 */

double ncephes_planckd(double w, double T) {
    return (planck_c2 /
            ((w * w * w * w * w) * (exp(planck_c2 / (w * T)) - 1.0)));
}

/* Wavelength, w, of maximum radiation at given temperature T.
   c2/wT = constant
   Wein displacement law.
  */
double ncephes_planckw(double T) {
    return (planck_c2 / (4.96511423174427630 * T));
}
