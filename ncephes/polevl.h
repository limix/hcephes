#ifndef NCEPHES_POLELV_H
#define NCEPHES_POLELV_H

static inline double ncephes_polevl(double x, double coef[], int N) {
    double ans;
    int i;
    double *p;

    p = coef;
    ans = *p++;
    i = N;

    do
        ans = ans * x + *p++;
    while (--i);

    return ans;
}

/*							p1evl()	*/
/*                                          N
 * Evaluate polynomial when coefficient of x  is 1.0.
 * Otherwise same as polevl.
 */

static inline double ncephes_p1evl(double x, double coef[], int N) {
    double ans;
    double *p;
    int i;

    p = coef;
    ans = x + *p++;
    i = N - 1;

    do
        ans = ans * x + *p++;
    while (--i);

    return ans;
}

#endif
