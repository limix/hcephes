#ifndef TYPE_H
#define TYPE_H

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

#endif
