#include "mconf.h"
#include "ncephes/polyn.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* near pointer version of malloc() */
/*
#define malloc _nmalloc
#define free _nfree
*/

/* Pointers to internal arrays.  Note poldiv() allocates
 * and deallocates some temporary arrays every time it is called.
 */
static double *pt1 = 0;
static double *pt2 = 0;
static double *pt3 = 0;

/* Maximum degree of polynomial. */
int MAXPOL = 0;
extern int MAXPOL;

/* Number of bytes (chars) in maximum size polynomial. */
static int psize = 0;

/* Initialize max degree of polynomials
 * and allocate temporary storage.
 */
void ncephes_polini(int maxdeg) {

    MAXPOL = maxdeg;
    psize = (maxdeg + 1) * sizeof(double);

    /* Release previously allocated memory, if any. */
    if (pt3)
        free(pt3);
    if (pt2)
        free(pt2);
    if (pt1)
        free(pt1);

    /* Allocate new arrays */
    pt1 = (double *)malloc(psize); /* used by polsbt */
    pt2 = (double *)malloc(psize); /* used by polsbt */
    pt3 = (double *)malloc(psize); /* used by ncephes_polmul */

    /* Report if failure */
    if ((pt1 == NULL) || (pt2 == NULL) || (pt3 == NULL)) {
        ncephes_mtherr("polini", ERANGE);
        exit(1);
    }
}

/* Print the coefficients of a, with d decimal precision.
 */
static char *form = "abcdefghijk";

void ncephes_polprt(double a[], int na, int d) {
    int i, j, d1;
    char *p;

    /* Create format descriptor string for the printout.
     * Do this partly by hand, since sprintf() may be too
     * bug-ridden to accomplish this feat by itself.
     */
    p = form;
    *p++ = '%';
    d1 = d + 8;
    sprintf(p, "%d ", d1);
    p += 1;
    if (d1 >= 10)
        p += 1;
    *p++ = '.';
    sprintf(p, "%d ", d);
    p += 1;
    if (d >= 10)
        p += 1;
    *p++ = 'e';
    *p++ = ' ';
    *p++ = '\0';

    /* Now do the printing.
     */
    d1 += 1;
    j = 0;
    for (i = 0; i <= na; i++) {
        /* Detect end of available line */
        j += d1;
        if (j >= 78) {
            printf("\n");
            j = d1;
        }
        printf(form, a[i]);
    }
    printf("\n");
}

/* Set a = 0.
 */
void ncephes_polclr(register double *a, int n) {
    int i;

    if (n > MAXPOL)
        n = MAXPOL;
    for (i = 0; i <= n; i++)
        *a++ = 0.0;
}

/* Set b = a.
 */
void ncephes_polmov(register double *a, int na, register double *b) {
    int i;

    if (na > MAXPOL)
        na = MAXPOL;

    for (i = 0; i <= na; i++) {
        *b++ = *a++;
    }
}

/* c = b * a.
 */
void ncephes_polmul(double a[], int na, double b[], int nb, double c[]) {
    int i, j, k, nc;
    double x;

    nc = na + nb;
    ncephes_polclr(pt3, MAXPOL);

    for (i = 0; i <= na; i++) {
        x = a[i];
        for (j = 0; j <= nb; j++) {
            k = i + j;
            if (k > MAXPOL)
                break;
            pt3[k] += x * b[j];
        }
    }

    if (nc > MAXPOL)
        nc = MAXPOL;
    for (i = 0; i <= nc; i++)
        c[i] = pt3[i];
}

/* c = b + a.
 */
void ncephes_poladd(double a[], int na, double b[], int nb, double c[]) {
    int i, n;

    if (na > nb)
        n = na;
    else
        n = nb;

    if (n > MAXPOL)
        n = MAXPOL;

    for (i = 0; i <= n; i++) {
        if (i > na)
            c[i] = b[i];
        else if (i > nb)
            c[i] = a[i];
        else
            c[i] = b[i] + a[i];
    }
}

/* c = b - a.
 */
void ncephes_polsub(double a[], int na, double b[], int nb, double c[]) {
    int i, n;

    if (na > nb)
        n = na;
    else
        n = nb;

    if (n > MAXPOL)
        n = MAXPOL;

    for (i = 0; i <= n; i++) {
        if (i > na)
            c[i] = b[i];
        else if (i > nb)
            c[i] = -a[i];
        else
            c[i] = b[i] - a[i];
    }
}

/* c = b/a
 */
int ncephes_poldiv(double a[], int na, double b[], int nb, double c[]) {
    double quot;
    double *ta, *tb, *tq;
    int i, j, k, sing;

    sing = 0;

    /* Allocate temporary arrays.  This would be quicker
     * if done automatically on the stack, but stack space
     * may be hard to obtain on a small computer.
     */
    ta = (double *)malloc(psize);
    ncephes_polclr(ta, MAXPOL);
    ncephes_polmov(a, na, ta);

    tb = (double *)malloc(psize);
    ncephes_polclr(tb, MAXPOL);
    ncephes_polmov(b, nb, tb);

    tq = (double *)malloc(psize);
    ncephes_polclr(tq, MAXPOL);

    /* What to do if leading (constant) coefficient
     * of denominator is zero.
     */
    if (a[0] == 0.0) {
        for (i = 0; i <= na; i++) {
            if (ta[i] != 0.0)
                goto nzero;
        }
        ncephes_mtherr("poldiv", SING);
        goto done;

    nzero:
        /* Reduce the degree of the denominator. */
        for (i = 0; i < na; i++)
            ta[i] = ta[i + 1];
        ta[na] = 0.0;

        if (b[0] != 0.0) {
            /* Optional message:
                            printf( "poldiv singularity, divide quotient by x\n"
               );
            */
            sing += 1;
        } else {
            /* Reduce degree of numerator. */
            for (i = 0; i < nb; i++)
                tb[i] = tb[i + 1];
            tb[nb] = 0.0;
        }
        /* Call self, using reduced polynomials. */
        sing += ncephes_poldiv(ta, na, tb, nb, c);
        goto done;
    }

    /* Long division algorithm.  ta[0] is nonzero.
     */
    for (i = 0; i <= MAXPOL; i++) {
        quot = tb[i] / ta[0];
        for (j = 0; j <= MAXPOL; j++) {
            k = j + i;
            if (k > MAXPOL)
                break;
            tb[k] -= quot * ta[j];
        }
        tq[i] = quot;
    }
    /* Send quotient to output array. */
    ncephes_polmov(tq, MAXPOL, c);

done:

    /* Restore allocated memory. */
    free(tq);
    free(tb);
    free(ta);
    return (sing);
}

/* Change of variables
 * Substitute a(y) for the variable x in b(x).
 * x = a(y)
 * c(x) = b(x) = b(a(y)).
 */

void ncephes_polsbt(double a[], int na, double b[], int nb, double c[]) {
    int i, j, k, n2;
    double x;

    /* 0th degree term:
     */
    ncephes_polclr(pt1, MAXPOL);
    pt1[0] = b[0];

    ncephes_polclr(pt2, MAXPOL);
    pt2[0] = 1.0;
    n2 = 0;

    for (i = 1; i <= nb; i++) {
        /* Form ith power of a. */
        ncephes_polmul(a, na, pt2, n2, pt2);
        n2 += na;
        x = b[i];
        /* Add the ith coefficient of b times the ith power of a. */
        for (j = 0; j <= n2; j++) {
            if (j > MAXPOL)
                break;
            pt1[j] += x * pt2[j];
        }
    }

    k = n2 + nb;
    if (k > MAXPOL)
        k = MAXPOL;
    for (i = 0; i <= k; i++)
        c[i] = pt1[i];
}

/* Evaluate polynomial a(t) at t = x.
 */
double ncephes_poleva(double a[], int na, double x) {
    double s;
    int i;

    s = a[na];
    for (i = na - 1; i >= 0; i--) {
        s = s * x + a[i];
    }
    return (s);
}
