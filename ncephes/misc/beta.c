#include "mconf.h"

#ifdef NCEPHES_UNK
#define MAXGAM 34.84425627277176174
#endif
#ifdef DEC
#define MAXGAM 34.84425627277176174
#endif
#ifdef IBMPC
#define MAXGAM 171.624376956302725
#endif
#ifdef MIEEE
#define MAXGAM 171.624376956302725
#endif

extern double fabs(double);
extern double ncephes_gamma(double);
extern double ncephes_lgam_sgn(double, int *);
extern double exp(double);
extern double log(double);
extern double floor(double);

extern double MAXLOG, NCEPHES_MAXNUM;

double ncephes_beta(double a, double b) {
    double y;
    int sign;

    sign = 1;

    if (a <= 0.0) {
        if (a == floor(a))
            goto over;
    }
    if (b <= 0.0) {
        if (b == floor(b))
            goto over;
    }

    y = a + b;
    if (fabs(y) > MAXGAM) {
        int sgngam;
        y = ncephes_lgam_sgn(y, &sgngam);
        sign *= sgngam; /* keep track of the sign */
        y = ncephes_lgam_sgn(b, &sgngam) - y;
        sign *= sgngam;
        y = ncephes_lgam_sgn(a, &sgngam) + y;
        sign *= sgngam;
        if (y > MAXLOG) {
        over:
            ncephes_mtherr("beta", NCEPHES_OVERFLOW);
            return (sign * NCEPHES_MAXNUM);
        }
        return (sign * exp(y));
    }

    y = ncephes_gamma(y);
    if (y == 0.0)
        goto over;

    if (a > b) {
        y = ncephes_gamma(a) / y;
        y *= ncephes_gamma(b);
    } else {
        y = ncephes_gamma(b) / y;
        y *= ncephes_gamma(a);
    }

    return (y);
}

/* Natural log of |beta|.  Return the sign of beta in sgngam.  */

double ncephes_lbeta(double a, double b) {
    double y;
    int sign;

    sign = 1;

    if (a <= 0.0) {
        if (a == floor(a))
            goto over;
    }
    if (b <= 0.0) {
        if (b == floor(b))
            goto over;
    }

    y = a + b;
    if (fabs(y) > MAXGAM) {
        int sgngam;
        y = ncephes_lgam_sgn(y, &sgngam);
        sign *= sgngam; /* keep track of the sign */
        y = ncephes_lgam_sgn(b, &sgngam) - y;
        sign *= sgngam;
        y = ncephes_lgam_sgn(a, &sgngam) + y;
        sign *= sgngam;
        sgngam = sign;
        return (y);
    }

    y = ncephes_gamma(y);
    if (y == 0.0) {
    over:
        ncephes_mtherr("lbeta", NCEPHES_OVERFLOW);
        return (sign * NCEPHES_MAXNUM);
    }

    if (a > b) {
        y = ncephes_gamma(a) / y;
        y *= ncephes_gamma(b);
    } else {
        y = ncephes_gamma(b) / y;
        y *= ncephes_gamma(a);
    }

    if (y < 0)
        y = -y;

    return (log(y));
}
