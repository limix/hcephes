#include "mconf.h"
#include "ncephes/ncephes.h"

#define MAXGAM 34.84425627277176174

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
        if (y > NCEPHES_MAXLOG) {
        over:
            ncephes_mtherr("beta", NCEPHES_OVERFLOW);
            return (sign * HUGE_VAL);
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
        return (sign * HUGE_VAL);
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
