#include "mconf.h"
#include "ncephes/ncephes.h"
#include <math.h>
#include <stdio.h>

static double P[] = {1.53552577301013293365E-4, 2.50888492163602060990E-3,
                     8.68786816565889628429E-3, 1.07350949056076193403E-2,
                     7.77395492516787092951E-3, 7.58395289413514708519E-3,
                     1.15688436810574127319E-2, 2.18317996015557253103E-2,
                     5.68051945617860553470E-2, 4.43147180560990850618E-1,
                     1.00000000000000000299E0};
static double Q[] = {3.27954898576485872656E-5, 1.00962792679356715133E-3,
                     6.50609489976927491433E-3, 1.68862163993311317300E-2,
                     2.61769742454493659583E-2, 3.34833904888224918614E-2,
                     4.27180926518931511717E-2, 5.85936634471101055642E-2,
                     9.37499997197644278445E-2, 2.49999999999888314361E-1};

double ncephes_ellpe(double x) {
    x = 1.0 - x;
    if ((x <= 0.0) || (x > 1.0)) {
        if (x == 0.0)
            return 1.0;
        ncephes_mtherr("ellpe", NCEPHES_DOMAIN);
        return 0.0;
    }
    printf("First: %.10f\n", ncephes_polevl(x, P, 10));
    printf("Secon: %.10f\n", log(x));
    printf("Third: %.10f\n", ncephes_polevl(x, Q, 9));
    return ncephes_polevl(x, P, 10) - log(x) * (x * ncephes_polevl(x, Q, 9));
}
