#include "mconf.h"
#include "ncephes/ncephes.h"
#include <math.h>

/* Chebyshev coefficients for x(K1(x) - log(x/2) I1(x))
 * in the interval [0,2].
 *
 * lim(x->0){ x(K1(x) - log(x/2) I1(x)) } = 1.
 */

static double A[] = {-7.02386347938628759343E-18, -2.42744985051936593393E-15,
                     -6.66690169419932900609E-13, -1.41148839263352776110E-10,
                     -2.21338763073472585583E-8,  -2.43340614156596823496E-6,
                     -1.73028895751305206302E-4,  -6.97572385963986435018E-3,
                     -1.22611180822657148235E-1,  -3.53155960776544875667E-1,
                     1.52530022733894777053E0};

/* Chebyshev coefficients for exp(x) sqrt(x) K1(x)
 * in the interval [2,infinity].
 *
 * lim(x->inf){ exp(x) sqrt(x) K1(x) } = sqrt(pi/2).
 */

static double B[] = {-5.75674448366501715755E-18, 1.79405087314755922667E-17,
                     -5.68946255844285935196E-17, 1.83809354436663880070E-16,
                     -6.05704724837331885336E-16, 2.03870316562433424052E-15,
                     -7.01983709041831346144E-15, 2.47715442448130437068E-14,
                     -8.97670518232499435011E-14, 3.34841966607842919884E-13,
                     -1.28917396095102890680E-12, 5.13963967348173025100E-12,
                     -2.12996783842756842877E-11, 9.21831518760500529508E-11,
                     -4.19035475934189648750E-10, 2.01504975519703286596E-9,
                     -1.03457624656780970260E-8,  5.74108412545004946722E-8,
                     -3.50196060308781257119E-7,  2.40648494783721712015E-6,
                     -1.93619797416608296024E-5,  1.95215518471351631108E-4,
                     -2.85781685962277938680E-3,  1.03923736576817238437E-1,
                     2.72062619048444266945E0};

extern double PI;
extern double MINLOG, MAXNUM;

double ncephes_k1(double x) {
    double y, z;

    z = 0.5 * x;
    if (z <= 0.0) {
        ncephes_mtherr("k1", DOMAIN);
        return (MAXNUM);
    }

    if (x <= 2.0) {
        y = x * x - 2.0;
        y = log(z) * ncephes_i1(x) + ncephes_chbevl(y, A, 11) / x;
        return (y);
    }

    return (exp(-x) * ncephes_chbevl(8.0 / x - 2.0, B, 25) / sqrt(x));
}

double ncephes_k1e(double x) {
    double y;

    if (x <= 0.0) {
        ncephes_mtherr("k1e", DOMAIN);
        return (MAXNUM);
    }

    if (x <= 2.0) {
        y = x * x - 2.0;
        y = log(0.5 * x) * ncephes_i1(x) + ncephes_chbevl(y, A, 11) / x;
        return (y * exp(x));
    }

    return (ncephes_chbevl(8.0 / x - 2.0, B, 25) / sqrt(x));
}
