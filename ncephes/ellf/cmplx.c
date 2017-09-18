#include "mconf.h"
#include "ncephes/ncephes.h"
#include <math.h>

extern double atan2(double, double);
extern double frexp(double, int *);
extern double ldexp(double, int);
void cdiv(cmplx *, cmplx *, cmplx *);
void cadd(cmplx *, cmplx *, cmplx *);

/*
typedef struct
        {
        double r;
        double i;
        }cmplx;
*/
cmplx czero = {0.0, 0.0};
extern cmplx czero;
cmplx cone = {1.0, 0.0};
extern cmplx cone;

/*	c = b + a	*/

void cadd(register cmplx *a, register cmplx *b, cmplx *c) {

    c->r = b->r + a->r;
    c->i = b->i + a->i;
}

/*	c = b - a	*/

void csub(register cmplx *a, register cmplx *b, cmplx *c) {

    c->r = b->r - a->r;
    c->i = b->i - a->i;
}

/*	c = b * a */

void cmul(register cmplx *a, register cmplx *b, cmplx *c) {
    double y;

    y = b->r * a->r - b->i * a->i;
    c->i = b->r * a->i + b->i * a->r;
    c->r = y;
}

/*	c = b / a */

void cdiv(register cmplx *a, register cmplx *b, cmplx *c) {
    double y, p, q, w;

    y = a->r * a->r + a->i * a->i;
    p = b->r * a->r + b->i * a->i;
    q = b->i * a->r - b->r * a->i;

    if (y < 1.0) {
        w = HUGE_VAL * y;
        if ((fabs(p) > w) || (fabs(q) > w) || (y == 0.0)) {
            c->r = HUGE_VAL;
            c->i = HUGE_VAL;
            ncephes_mtherr("cdiv", NCEPHES_OVERFLOW);
            return;
        }
    }
    c->r = p / y;
    c->i = q / y;
}

/*	b = a
   Caution, a `short' is assumed to be 16 bits wide.  */

void cmov(void *a, void *b) {
    register short *pa, *pb;
    int i;

    pa = (short *)a;
    pb = (short *)b;
    i = 8;
    do
        *pb++ = *pa++;
    while (--i);
}

void cneg(register cmplx *a) {

    a->r = -a->r;
    a->i = -a->i;
}

    /*							ncephes_cabs()
     *
     *	Complex absolute value
     *
     *
     *
     * SYNOPSIS:
     *
     * double ncephes_cabs();
     * cmplx z;
     * double a;
     *
     * a = ncephes_cabs( &z );
     *
     *
     *
     * DESCRIPTION:
     *
     *
     * If z = x + iy
     *
     * then
     *
     *       a = sqrt( x**2 + y**2 ).
     *
     * Overflow and underflow are avoided by testing the magnitudes
     * of x and y before squaring.  If either is outside half of
     * the floating point full scale range, both are rescaled.
     *
     *
     * ACCURACY:
     *
     *                      Relative error:
     * arithmetic   domain     # trials      peak         rms
     *    DEC       -30,+30     30000       3.2e-17     9.2e-18
     *    IEEE      -10,+10    100000       2.7e-16     6.9e-17
     */

    /*
    Cephes Math Library Release 2.1:  January, 1989
    Copyright 1984, 1987, 1989 by Stephen L. Moshier
    Direct inquiries to 30 Frost Street, Cambridge, MA 02140
    */

    /*
    typedef struct
            {
            double r;
            double i;
            }cmplx;
    */

#ifdef NCEPHES_UNK
#define PREC 27
#define MAXEXP 1024
#define MINEXP -1077
#endif
#ifdef DEC
#define PREC 29
#define MAXEXP 128
#define MINEXP -128
#endif
#ifdef IBMPC
#define PREC 27
#define MAXEXP 1024
#define MINEXP -1077
#endif
#ifdef MIEEE
#define PREC 27
#define MAXEXP 1024
#define MINEXP -1077
#endif

double ncephes_cabs(register cmplx *z) {
    double x, y, b, re, im;
    int ex, ey, e;

#ifdef NCEPHES_INFINITIES
    /* Note, ncephes_cabs(HUGE_VAL,NCEPHES_NAN) = HUGE_VAL. */
    if (z->r == HUGE_VAL || z->i == HUGE_VAL || z->r == -HUGE_VAL ||
        z->i == -HUGE_VAL)
        return (HUGE_VAL);
#endif

#ifdef NCEPHES_NANS
    if (isnan(z->r))
        return (z->r);
    if (isnan(z->i))
        return (z->i);
#endif

    re = fabs(z->r);
    im = fabs(z->i);

    if (re == 0.0)
        return (im);
    if (im == 0.0)
        return (re);

    /* Get the exponents of the numbers */
    x = frexp(re, &ex);
    y = frexp(im, &ey);

    /* Check if one number is tiny compared to the other */
    e = ex - ey;
    if (e > PREC)
        return (re);
    if (e < -PREC)
        return (im);

    /* Find approximate exponent e of the geometric mean. */
    e = (ex + ey) >> 1;

    /* Rescale so mean is about 1 */
    x = ldexp(re, -e);
    y = ldexp(im, -e);

    /* Hypotenuse of the right triangle */
    b = sqrt(x * x + y * y);

    /* Compute the exponent of the answer. */
    y = frexp(b, &ey);
    ey = e + ey;

    /* Check it for overflow and underflow. */
    if (ey > MAXEXP) {
        ncephes_mtherr("ncephes_cabs", NCEPHES_OVERFLOW);
        return (HUGE_VAL);
    }
    if (ey < MINEXP)
        return (0.0);

    /* Undo the scaling */
    b = ldexp(b, e);
    return (b);
}
/*							ncephes_csqrt()
 *
 *	Complex square root
 *
 *
 *
 * SYNOPSIS:
 *
 * void ncephes_csqrt();
 * cmplx z, w;
 *
 * ncephes_csqrt( &z, &w );
 *
 *
 *
 * DESCRIPTION:
 *
 *
 * If z = x + iy,  r = |z|, then
 *
 *                       1/2
 * Im w  =  [ (r - x)/2 ]   ,
 *
 * Re w  =  y / 2 Im w.
 *
 *
 * Note that -w is also a square root of z.  The root chosen
 * is always in the upper half plane.
 *
 * Because of the potential for cancellation error in r - x,
 * the result is sharpened by doing a Heron iteration
 * (see sqrt.c) in complex arithmetic.
 *
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    DEC       -10,+10     25000       3.2e-17     9.6e-18
 *    IEEE      -10,+10    100000       3.2e-16     7.7e-17
 *
 *                        2
 * Also tested by ncephes_csqrt( z ) = z, and tested by arguments
 * close to the real axis.
 */

void ncephes_csqrt(cmplx *z, cmplx *w) {
    cmplx q, s;
    double x, y, r, t;

    x = z->r;
    y = z->i;

    if (y == 0.0) {
        if (x < 0.0) {
            w->r = 0.0;
            w->i = sqrt(-x);
            return;
        } else {
            w->r = sqrt(x);
            w->i = 0.0;
            return;
        }
    }

    if (x == 0.0) {
        r = fabs(y);
        r = sqrt(0.5 * r);
        if (y > 0)
            w->r = r;
        else
            w->r = -r;
        w->i = r;
        return;
    }

    /* Approximate  sqrt(x^2+y^2) - x  =  y^2/2x - y^4/24x^3 + ... .
     * The relative error in the first term is approximately y^2/12x^2 .
     */
    if ((fabs(y) < 2.e-4 * fabs(x)) && (x > 0)) {
        t = 0.25 * y * (y / x);
    } else {
        r = ncephes_cabs(z);
        t = 0.5 * (r - x);
    }

    r = sqrt(t);
    q.i = r;
    q.r = y / (2.0 * r);
    /* Heron iteration in complex arithmetic */
    cdiv(&q, z, &s);
    cadd(&q, &s, w);
    w->r *= 0.5;
    w->i *= 0.5;
}

double hypot(double x, double y) {
    cmplx z;

    z.r = x;
    z.i = y;
    return (ncephes_cabs(&z));
}
