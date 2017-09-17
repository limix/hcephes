#include "mconf.h"
#include "ncephes/ncephes.h"
#include <math.h>

static int sx = 1;
static int sy = 10000;
static int sz = 3000;

static union {
    double d;
    unsigned short s[4];
} unkans;

/* This function implements the three
 * congruential generators.
 */

static int ncephes_ranwh(void) {
    int r, s;

    /*  sx = sx * 171 mod 30269 */
    r = sx / 177;
    s = sx - 177 * r;
    sx = 171 * s - 2 * r;
    if (sx < 0)
        sx += 30269;

    /* sy = sy * 172 mod 30307 */
    r = sy / 176;
    s = sy - 176 * r;
    sy = 172 * s - 35 * r;
    if (sy < 0)
        sy += 30307;

    /* sz = 170 * sz mod 30323 */
    r = sz / 178;
    s = sz - 178 * r;
    sz = 170 * s - 63 * r;
    if (sz < 0)
        sz += 30323;
    /* The results are in static sx, sy, sz. */
    return 0;
}

/*	drand.c
 *
 * Random double precision floating point number between 1 and 2.
 *
 * C callable:
 *	drand( &x );
 */

int drand(double *a) {
    unsigned short r;

    /* This algorithm of Wichmann and Hill computes a floating point
     * result:
     */
    ncephes_ranwh();
    unkans.d = sx / 30269.0 + sy / 30307.0 + sz / 30323.0;
    r = unkans.d;
    unkans.d -= r;
    unkans.d += 1.0;

#ifdef IBMPC
    unkans.s[0] = r;
#endif

#ifdef MIEEE
    unkans.s[3] = r;
#endif

    *a = unkans.d;
    return 0;
}
