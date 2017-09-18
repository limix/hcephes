#include "mconf.h"
#include "ncephes/ncephes.h"
#include <math.h>

#define EUL 5.772156649015328606065e-1
#define MAXFAC 31

extern double MACHEP, NCEPHES_MAXNUM, MAXLOG;

double ncephes_kn(int nn, double x) {
    double k, kf, nk1f, nkf, zn, t, s, z0, z;
    double ans, fn, pn, pk, zmn, tlg, tox;
    int i, n;

    if (nn < 0)
        n = -nn;
    else
        n = nn;

    if (n > MAXFAC) {
    overf:
        ncephes_mtherr("kn", OVERFLOW);
        return (NCEPHES_MAXNUM);
    }

    if (x <= 0.0) {
        if (x < 0.0)
            ncephes_mtherr("kn", DOMAIN);
        else
            ncephes_mtherr("kn", SING);
        return (NCEPHES_MAXNUM);
    }

    if (x > 9.55)
        goto asymp;

    ans = 0.0;
    z0 = 0.25 * x * x;
    fn = 1.0;
    pn = 0.0;
    zmn = 1.0;
    tox = 2.0 / x;

    if (n > 0) {
        /* compute factorial of n and psi(n) */
        pn = -EUL;
        k = 1.0;
        for (i = 1; i < n; i++) {
            pn += 1.0 / k;
            k += 1.0;
            fn *= k;
        }

        zmn = tox;

        if (n == 1) {
            ans = 1.0 / x;
        } else {
            nk1f = fn / n;
            kf = 1.0;
            s = nk1f;
            z = -z0;
            zn = 1.0;
            for (i = 1; i < n; i++) {
                nk1f = nk1f / (n - i);
                kf = kf * i;
                zn *= z;
                t = nk1f * zn / kf;
                s += t;
                if ((NCEPHES_MAXNUM - fabs(t)) < fabs(s))
                    goto overf;
                if ((tox > 1.0) && ((NCEPHES_MAXNUM / tox) < zmn))
                    goto overf;
                zmn *= tox;
            }
            s *= 0.5;
            t = fabs(s);
            if ((zmn > 1.0) && ((NCEPHES_MAXNUM / zmn) < t))
                goto overf;
            if ((t > 1.0) && ((NCEPHES_MAXNUM / t) < zmn))
                goto overf;
            ans = s * zmn;
        }
    }

    tlg = 2.0 * log(0.5 * x);
    pk = -EUL;
    if (n == 0) {
        pn = pk;
        t = 1.0;
    } else {
        pn = pn + 1.0 / n;
        t = 1.0 / fn;
    }
    s = (pk + pn - tlg) * t;
    k = 1.0;
    do {
        t *= z0 / (k * (k + n));
        pk += 1.0 / k;
        pn += 1.0 / (k + n);
        s += (pk + pn - tlg) * t;
        k += 1.0;
    } while (fabs(t / s) > MACHEP);

    s = 0.5 * s / zmn;
    if (n & 1)
        s = -s;
    ans += s;

    return (ans);

    /* Asymptotic expansion for Kn(x) */
    /* Converges to 1.4e-17 for x > 18.4 */

asymp:

    if (x > MAXLOG) {
        ncephes_mtherr("kn", UNDERFLOW);
        return (0.0);
    }
    k = n;
    pn = 4.0 * k * k;
    pk = 1.0;
    z0 = 8.0 * x;
    fn = 1.0;
    t = 1.0;
    s = t;
    nkf = NCEPHES_MAXNUM;
    i = 0;
    do {
        z = pn - pk * pk;
        t = t * z / (fn * z0);
        nk1f = fabs(t);
        if ((i >= n) && (nk1f > nkf)) {
            goto adone;
        }
        nkf = nk1f;
        s += t;
        fn += 1.0;
        pk += 2.0;
        i += 1;
    } while (fabs(t / s) > MACHEP);

adone:
    ans = exp(-x) * sqrt(NCEPHES_PI / (2.0 * x)) * s;
    return (ans);
}
