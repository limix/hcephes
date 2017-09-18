#include "mconf.h"

double MACHEP = 1.11022302462515654042E-16; /* 2**-53 */

#ifdef NCEPHES_DENORMAL
double MAXLOG = 7.09782712893383996732E2; /* log(DBL_MAX) */

/* double MINLOG = -7.44440071921381262314E2; */ /* log(2**-1074) */
double MINLOG = -7.451332191019412076235E2;      /* log(2**-1075) */
#else
double MAXLOG = 7.08396418532264106224E2;  /* log 2**1022 */
double MINLOG = -7.08396418532264106224E2; /* log 2**-1022 */
#endif
double NCEPHES_SQ2OPI = 7.9788456080286535587989E-1;  /* sqrt( 2/pi ) */
double NCEPHES_LOGSQ2 = 3.46573590279972654709E-1;    /* log(2)/2 */
double NCEPHES_THPIO4 = 2.35619449019234492885;       /* 3*pi/4 */
double NCEPHES_TWOOPI = 6.36619772367581343075535E-1; /* 2/pi */

#include <float.h>
#include <math.h>

#ifndef NAN
#if _MSC_VER == 1500
#define NAN sqrt(-1)
#else
#include <bits/nan.h>
#endif
#endif

const double NCEPHES_INF = HUGE_VAL;
const double NCEPHES_NAN = NAN;
const double NCEPHES_MAXNUM = HUGE_VAL;
const double NCEPHES_PI = 3.14159265358979323846;
const double NCEPHES_PIO2 = 3.14159265358979323846 / 2;
const double NCEPHES_PIO4 = 3.14159265358979323846 / 4;
const double NCEPHES_SQRTH = 7.07106781186547524401E-1; /* sqrt(2)/2 */
double NCEPHES_LOGE2 = 6.93147180559945309417E-1;       /* log(2) */
double NCEPHES_NEGZERO = -0.0;

#ifndef NCEPHES_UNK
extern unsigned short MACHEP[];
extern unsigned short MAXLOG[];
extern unsigned short UNDLOG[];
extern unsigned short MINLOG[];
extern unsigned short SQ2OPI[];
extern unsigned short LOGSQ2[];
extern unsigned short THPIO4[];
#endif
