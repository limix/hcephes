#ifndef CPROB_H
#define CPROB_H

double ncephes_bdtrc(int k, int n, double p);
double ncephes_bdtr(int k, int n, double p);
double ncephes_bdtri(int k, int n, double y);
double ncephes_btdtr(double a, double b, double x);
double ncephes_chdtrc(double df, double x);
double ncephes_chdtr(double df, double x);
double ncephes_chdtri(double df, double y);
double ncephes_expx2(double x, int sign);
double ncephes_fdtrc(int ia, int ib, double x);
double ncephes_fdtr(int ia, int ib, double x);
double ncephes_fdtri(int ia, int ib, double y);
double ncephes_gamma(double x);
double ncephes_lgam(double x);
double ncephes_gdtr(double a, double b, double x);
double ncephes_gdtrc(double a, double b, double x);
double ncephes_igamc(double a, double x);
double ncephes_igam(double a, double x);
double ncephes_igami(double a, double y0);
double ncephes_incbet(double aa, double bb, double xx);
double ncephes_incbi(double aa, double bb, double yy0);
double ncephes_smirnov(int n, double e);
double ncephes_kolmogorov(double y);
double ncephes_smirnovi(int n, double p);
double ncephes_kolmogi(double p);
double ncephes_nbdtrc(int k, int n, double p);
double ncephes_nbdtr(int k, int n, double p);
double ncephes_nbdtri(int k, int n, double p);
double ncephes_ndtr(double a);
double ncephes_erfc(double a);
double ncephes_erf(double x);
double ncephes_ndtri(double y0);
double ncephes_pdtrc(int k, double m);
double ncephes_pdtr(int k, double m);
double ncephes_pdtri(int k, double y);
double ncephes_stdtr(int k, double t);
double ncephes_stdtri(int k, double p);
double ncephes_log1p(double x);
double ncephes_expm1(double x);
double ncephes_cosm1(double x);

#endif
