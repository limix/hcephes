#ifndef NCEPHES_POLYN_H
#define NCEPHES_POLYN_H

#include "ncephes/type.h"

double ncephes_euclid(double *num, double *den);
double ncephes_p1evl(double x, double coef[], int N);
double ncephes_polevl(double x, double coef[], int N);
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
void ncephes_rmul(fract *ff1, fract *ff2, fract *ff3);
void ncephes_rsub(fract *f1, fract *f2, fract *f3);

#endif
