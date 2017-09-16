#ifndef NCEPHES_POLYN_H
#define NCEPHES_POLYN_H

#include "ncephes/type.h"

double ncephes_euclid(double *num, double *den);
int ncephes_poldiv(double *, int, double *, int, double *);
int ncephes_polrt(double xcof[], double cof[], int m, cmplx root[]);
void ncephes_poladd(double a[], int na, double b[], int nb, double c[]);
void ncephes_polclr(double *, int);
void ncephes_polmov(double *, int, double *);
void ncephes_polmul(double *, int, double *, int, double *);
void ncephes_polsbt(double a[], int na, double b[], int nb, double c[]);
void ncephes_polsub(double a[], int na, double b[], int nb, double c[]);

#endif
