#ifndef NCEPHES_H
#define NCEPHES_H

#define NCEPHES_SQ2OPI 7.9788456080286535587989E-1  /* sqrt( 2/pi ) */
#define NCEPHES_LOGSQ2 3.46573590279972654709E-1    /* log(2)/2 */
#define NCEPHES_THPIO4 2.35619449019234492885       /* 3*pi/4 */
#define NCEPHES_TWOOPI 6.36619772367581343075535E-1 /* 2/pi */
#define NCEPHES_PI 3.14159265358979323846
#define NCEPHES_PIO2 (3.14159265358979323846 / 2)
#define NCEPHES_PIO4 (3.14159265358979323846 / 4)
#define NCEPHES_SQRTH 7.07106781186547524401E-1 /* sqrt(2)/2 */

typedef struct {
    double n; /* numerator */
    double d; /* denominator */
} fract;

typedef struct {
    long double r;
    long double i;
} cmplxl;

typedef struct {
    float r;
    float i;
} cmplxf;

typedef struct {
    double r;
    double i;
} cmplx;

double ncephes_chbevl(double x, double array[], int n);
double ncephes_bdtr(int k, int n, double p);        // ok
double ncephes_bdtrc(int k, int n, double p);       // ok
double ncephes_bdtri(int k, int n, double y);       // ok
double ncephes_beta(double a, double b);            // ok
double ncephes_btdtr(double a, double b, double x); // ok
double ncephes_chdtr(double df, double x);          // ok
double ncephes_chdtrc(double df, double x);         // ok
double ncephes_chdtri(double df, double y);         // ok
double ncephes_cosm1(double x);                     // ok
double ncephes_ellie(double phi, double m);         // ok
double ncephes_ellik(double phi, double m);         // ok
double ncephes_ellpe(double x);                     // ok
double ncephes_ellpk(double x);                     // ok
double ncephes_euclid(double *num, double *den);    // ok
double ncephes_expm1(double x);                     // ok
double ncephes_expx2(double x, int sign);           // ok
double ncephes_fdtr(int ia, int ib, double x);      // ok
double ncephes_fdtrc(int ia, int ib, double x);     // ok
double ncephes_fdtri(int ia, int ib, double y);     // ok
double ncephes_gamma(double x);                     // ok
double ncephes_gdtr(double a, double b, double x);  // ok
double ncephes_gdtrc(double a, double b, double x); // ok
double ncephes_hyp2f0(double a, double b, double x, int type, double *err);
double ncephes_hyp2f1(double a, double b, double c, double x);
double ncephes_hyperg(double a, double b, double x);
double ncephes_i0(double x);
double ncephes_i0e(double x);
double ncephes_i1(double x);
double ncephes_i1e(double x);
double ncephes_igam(double a, double x);                // ok
double ncephes_igamc(double a, double x);               // ok
double ncephes_igami(double a, double y0);              // ok
double ncephes_incbet(double aa, double bb, double xx); // ok
double ncephes_incbi(double aa, double bb, double yy0); // ok
double ncephes_iv(double v, double x);
double ncephes_j0(double x);
double ncephes_j1(double x);
double ncephes_jn(int n, double x);
double ncephes_jv(double n, double x);
double ncephes_k0(double x);
double ncephes_k0e(double x);
double ncephes_k1(double x);
double ncephes_k1e(double x);
double ncephes_kn(int nn, double x);
double ncephes_kolmogi(double p);              // ok
double ncephes_kolmogorov(double y);           // ok
double ncephes_lbeta(double a, double b);      // ok
double ncephes_lgam_sgn(double x, int *sign);  // ok
double ncephes_lgam(double x);                 // ok
double ncephes_log1p(double x);                // ok
double ncephes_nbdtr(int k, int n, double p);  // ok
double ncephes_nbdtrc(int k, int n, double p); // ok
double ncephes_nbdtri(int k, int n, double p); // ok
double ncephes_ndtr(double a);                 // ok
double ncephes_ndtri(double y0);               // ok
double ncephes_onef2(double a, double b, double c, double x, double *err);
double ncephes_pdtr(int k, double m);  // ok
double ncephes_pdtrc(int k, double m); // ok
double ncephes_pdtri(int k, double y); // ok
double ncephes_psi(double x);
double ncephes_smirnov(int n, double e);  // ok
double ncephes_smirnovi(int n, double p); // ok
double ncephes_stdtr(int k, double t);    // ok
double ncephes_stdtri(int k, double p);   // ok
double ncephes_struve(double v, double x);
double ncephes_threef0(double a, double b, double c, double x, double *err);
double ncephes_y0(double x);
double ncephes_y1(double x);
double ncephes_yn(int n, double x);
double ncephes_yv(double v, double x);
int ncephes_airy(double x, double *ai, double *aip, double *bi, double *bip);
int ncephes_poldiv(double *, int, double *, int, double *);
int ncephes_polrt(double xcof[], double cof[], int m, cmplx root[]);
void ncephes_poladd(double a[], int na, double b[], int nb, double c[]);
void ncephes_polclr(double *, int);
void ncephes_polmov(double *, int, double *);
void ncephes_polmul(double *, int, double *, int, double *);
void ncephes_polsbt(double a[], int na, double b[], int nb, double c[]);
void ncephes_polsub(double a[], int na, double b[], int nb, double c[]);
void ncephes_radd(fract *f1, fract *f2, fract *f3);
void ncephes_rdiv(fract *ff1, fract *ff2, fract *ff3);
void ncephes_revers(double y[], double x[], int n);
void ncephes_rmul(fract *ff1, fract *ff2, fract *ff3);
void ncephes_rsub(fract *f1, fract *f2, fract *f3);
double ncephes_polevl(double x, double coef[], int N);
double ncephes_p1evl(double x, double coef[], int N);

#endif
