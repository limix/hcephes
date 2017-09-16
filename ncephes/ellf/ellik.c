#include "mconf.h"
#include "ncephes/ellf.h"
#include <math.h>

extern double NCEPHES_PI, NCEPHES_PIO2, MACHEP, NCEPHES_MAXNUM;

double ncephes_ellik(double phi, double m) {
    double a, b, c, e, temp, t, K;
    int d, mod, sign, npio2;

    if (m == 0.0)
        return (phi);
    a = 1.0 - m;
    if (a == 0.0) {
        if (fabs(phi) >= NCEPHES_PIO2) {
            ncephes_mtherr("ellik", NCEPHES_SING);
            return (NCEPHES_MAXNUM);
        }
        return (log(tan((NCEPHES_PIO2 + phi) / 2.0)));
    }
    npio2 = floor(phi / NCEPHES_PIO2);
    if (npio2 & 1)
        npio2 += 1;
    if (npio2) {
        K = ncephes_ellpk(a);
        phi = phi - npio2 * NCEPHES_PIO2;
    } else
        K = 0.0;
    if (phi < 0.0) {
        phi = -phi;
        sign = -1;
    } else
        sign = 0;
    b = sqrt(a);
    t = tan(phi);
    if (fabs(t) > 10.0) {
        /* Transform the amplitude */
        e = 1.0 / (b * t);
        /* ... but avoid multiple recursions.  */
        if (fabs(e) < 10.0) {
            e = atan(e);
            if (npio2 == 0)
                K = ncephes_ellpk(a);
            temp = K - ncephes_ellik(e, m);
            goto done;
        }
    }
    a = 1.0;
    c = sqrt(m);
    d = 1;
    mod = 0;

    while (fabs(c / a) > MACHEP) {
        temp = b / a;
        phi = phi + atan(t * temp) + mod * NCEPHES_PI;
        mod = (phi + NCEPHES_PIO2) / NCEPHES_PI;
        t = t * (1.0 + temp) / (1.0 - temp * t * t);
        c = (a - b) / 2.0;
        temp = sqrt(a * b);
        a = (a + b) / 2.0;
        b = temp;
        d += d;
    }

    temp = (atan(t) + mod * NCEPHES_PI) / (d * a);

done:
    if (sign < 0)
        temp = -temp;
    temp += npio2 * K;
    return (temp);
}
