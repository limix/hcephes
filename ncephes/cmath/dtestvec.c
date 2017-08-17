
/* Test vectors for math functions.
   See C9X section F.9.  */
/*
Cephes Math Library Release 2.8:  June, 2000
Copyright 1998, 2000 by Stephen L. Moshier
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int isfinite (double);

/* C9X spells lgam lncephes_gamma.  */
#define GLIBC2 0

extern double NCEPHES_PI;
static double MNCEPHES_PI, NCEPHES_PIO2, MNCEPHES_PIO2, NCEPHES_PIO4, MNCEPHES_PIO4, THNCEPHES_PIO4, MTHNCEPHES_PIO4;

#if 0
#define NCEPHES_PI 3.141592653589793238463E0
#define NCEPHES_PIO2 1.570796326794896619231E0
#define NCEPHES_PIO4 7.853981633974483096157E-1
#define THNCEPHES_PIO4 2.35619449019234492884698
#define SQRT2 1.414213562373095048802E0
#define SQRTH 7.071067811865475244008E-1
#define INF (1.0/0.0)
#define MINF (-1.0/0.0)
#endif

extern double MACHEP, SQRTH, SQRT2;
extern double NCEPHES_NAN, NCEPHES_INF, NEGZERO;
static double INF, MINF;
static double ZERO, MZERO, HALF, MHALF, ONE, MONE, TWO, MTWO, THREE, MTHREE;
/* #define NCEPHES_NAN (1.0/0.0 - 1.0/0.0) */

/* Functions of one variable.  */
double log (double);
double exp ( double);
double atan (double);
double sin (double);
double cos (double);
double tan (double);
double acos (double);
double asin (double);
double acosh (double);
double asinh (double);
double atanh (double);
double sinh (double);
double cosh (double);
double tanh (double);
double exp2 (double);
double expm1 (double);
double log10 (double);
double log1p (double);
double log2 (double);
double fabs (double);
double erf (double);
double erfc (double);
double ncephes_gamma (double);
double floor (double);
double ceil (double);
double cbrt (double);
#if GLIBC2
double lncephes_gamma (double);
#else
double lgam (double);
#endif

struct oneargument
  {
    char *name;			/* Name of the function. */
    double (*func) (double);
    double *arg1;
    double *answer;
    int thresh;			/* Error report threshold. */
  };

struct oneargument test1[] =
{
  {"atan", atan, &ONE, &NCEPHES_PIO4, 0},
  {"sin", sin, &NCEPHES_PIO2, &ONE, 0},
#if 0
  {"cos", cos, &NCEPHES_PIO4, &SQRTH, 0},
  {"sin", sin, 32767., 1.8750655394138942394239E-1, 0},
  {"cos", cos, 32767., 9.8226335176928229845654E-1, 0},
  {"tan", tan, 32767., 1.9089234430221485740826E-1, 0},
  {"sin", sin, 8388607., 9.9234509376961249835628E-1, 0},
  {"cos", cos, 8388607., -1.2349580912475928183718E-1, 0},
  {"tan", tan, 8388607., -8.0354556223613614748329E0, 0},
  /*
  {"sin", sin, 2147483647., -7.2491655514455639054829E-1, 0},
  {"cos", cos, 2147483647., -6.8883669187794383467976E-1, 0},
  {"tan", tan, 2147483647., 1.0523779637351339136698E0, 0},
  */
  {"cos", cos, &NCEPHES_PIO2, 6.1232339957367574e-17, 1},
  {"sin", sin, &NCEPHES_PIO4, &SQRTH, 1},
#endif
  {"acos", acos, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"acos", acos, &ONE, &ZERO, 0},
  {"acos", acos, &TWO, &NCEPHES_NAN, 0},
  {"acos", acos, &MTWO, &NCEPHES_NAN, 0},
  {"asin", asin, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"asin", asin, &ZERO, &ZERO, 0},
  {"asin", asin, &MZERO, &MZERO, 0},
  {"asin", asin, &TWO, &NCEPHES_NAN, 0},
  {"asin", asin, &MTWO, &NCEPHES_NAN, 0},
  {"atan", atan, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"atan", atan, &ZERO, &ZERO, 0},
  {"atan", atan, &MZERO, &MZERO, 0},
  {"atan", atan, &INF, &NCEPHES_PIO2, 0},
  {"atan", atan, &MINF, &MNCEPHES_PIO2, 0},
  {"cos", cos, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"cos", cos, &ZERO, &ONE, 0},
  {"cos", cos, &MZERO, &ONE, 0},
  {"cos", cos, &INF, &NCEPHES_NAN, 0},
  {"cos", cos, &MINF, &NCEPHES_NAN, 0},
  {"sin", sin, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"sin", sin, &MZERO, &MZERO, 0},
  {"sin", sin, &ZERO, &ZERO, 0},
  {"sin", sin, &INF, &NCEPHES_NAN, 0},
  {"sin", sin, &MINF, &NCEPHES_NAN, 0},
  {"tan", tan, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"tan", tan, &ZERO, &ZERO, 0},
  {"tan", tan, &MZERO, &MZERO, 0},
  {"tan", tan, &INF, &NCEPHES_NAN, 0},
  {"tan", tan, &MINF, &NCEPHES_NAN, 0},
  {"acosh", acosh, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"acosh", acosh, &ONE, &ZERO, 0},
  {"acosh", acosh, &INF, &INF, 0},
  {"acosh", acosh, &HALF, &NCEPHES_NAN, 0},
  {"acosh", acosh, &MONE, &NCEPHES_NAN, 0},
  {"asinh", asinh, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"asinh", asinh, &ZERO, &ZERO, 0},
  {"asinh", asinh, &MZERO, &MZERO, 0},
  {"asinh", asinh, &INF, &INF, 0},
  {"asinh", asinh, &MINF, &MINF, 0},
  {"atanh", atanh, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"atanh", atanh, &ZERO, &ZERO, 0},
  {"atanh", atanh, &MZERO, &MZERO, 0},
  {"atanh", atanh, &ONE, &INF, 0},
  {"atanh", atanh, &MONE, &MINF, 0},
  {"atanh", atanh, &TWO, &NCEPHES_NAN, 0},
  {"atanh", atanh, &MTWO, &NCEPHES_NAN, 0},
  {"cosh", cosh, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"cosh", cosh, &ZERO, &ONE, 0},
  {"cosh", cosh, &MZERO, &ONE, 0},
  {"cosh", cosh, &INF, &INF, 0},
  {"cosh", cosh, &MINF, &INF, 0},
  {"sinh", sinh, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"sinh", sinh, &ZERO, &ZERO, 0},
  {"sinh", sinh, &MZERO, &MZERO, 0},
  {"sinh", sinh, &INF, &INF, 0},
  {"sinh", sinh, &MINF, &MINF, 0},
  {"tanh", tanh, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"tanh", tanh, &ZERO, &ZERO, 0},
  {"tanh", tanh, &MZERO, &MZERO, 0},
  {"tanh", tanh, &INF, &ONE, 0},
  {"tanh", tanh, &MINF, &MONE, 0},
  {"exp", exp, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"exp", exp, &ZERO, &ONE, 0},
  {"exp", exp, &MZERO, &ONE, 0},
  {"exp", exp, &INF, &INF, 0},
  {"exp", exp, &MINF, &ZERO, 0},
#if !GLIBC2
  {"exp2", exp2, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"exp2", exp2, &ZERO, &ONE, 0},
  {"exp2", exp2, &MZERO, &ONE, 0},
  {"exp2", exp2, &INF, &INF, 0},
  {"exp2", exp2, &MINF, &ZERO, 0},
#endif
  {"expm1", expm1, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"expm1", expm1, &ZERO, &ZERO, 0},
  {"expm1", expm1, &MZERO, &MZERO, 0},
  {"expm1", expm1, &INF, &INF, 0},
  {"expm1", expm1, &MINF, &MONE, 0},
  {"log", log, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"log", log, &ZERO, &MINF, 0},
  {"log", log, &MZERO, &MINF, 0},
  {"log", log, &ONE, &ZERO, 0},
  {"log", log, &MONE, &NCEPHES_NAN, 0},
  {"log", log, &INF, &INF, 0},
  {"log10", log10, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"log10", log10, &ZERO, &MINF, 0},
  {"log10", log10, &MZERO, &MINF, 0},
  {"log10", log10, &ONE, &ZERO, 0},
  {"log10", log10, &MONE, &NCEPHES_NAN, 0},
  {"log10", log10, &INF, &INF, 0},
  {"log1p", log1p, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"log1p", log1p, &ZERO, &ZERO, 0},
  {"log1p", log1p, &MZERO, &MZERO, 0},
  {"log1p", log1p, &MONE, &MINF, 0},
  {"log1p", log1p, &MTWO, &NCEPHES_NAN, 0},
  {"log1p", log1p, &INF, &INF, 0},
#if !GLIBC2
  {"log2", log2, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"log2", log2, &ZERO, &MINF, 0},
  {"log2", log2, &MZERO, &MINF, 0},
  {"log2", log2, &MONE, &NCEPHES_NAN, 0},
  {"log2", log2, &INF, &INF, 0},
#endif
  /*  {"fabs", fabs, NCEPHES_NAN, NCEPHES_NAN, 0}, */
  {"fabs", fabs, &ONE, &ONE, 0},
  {"fabs", fabs, &MONE, &ONE, 0},
  {"fabs", fabs, &ZERO, &ZERO, 0},
  {"fabs", fabs, &MZERO, &ZERO, 0},
  {"fabs", fabs, &INF, &INF, 0},
  {"fabs", fabs, &MINF, &INF, 0},
  {"cbrt", cbrt, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"cbrt", cbrt, &ZERO, &ZERO, 0},
  {"cbrt", cbrt, &MZERO, &MZERO, 0},
  {"cbrt", cbrt, &INF, &INF, 0},
  {"cbrt", cbrt, &MINF, &MINF, 0},
  {"erf", erf, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"erf", erf, &ZERO, &ZERO, 0},
  {"erf", erf, &MZERO, &MZERO, 0},
  {"erf", erf, &INF, &ONE, 0},
  {"erf", erf, &MINF, &MONE, 0},
  {"erfc", erfc, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"erfc", erfc, &INF, &ZERO, 0},
  {"erfc", erfc, &MINF, &TWO, 0},
  {"ncephes_gamma", ncephes_gamma, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"ncephes_gamma", ncephes_gamma, &INF, &INF, 0},
  {"ncephes_gamma", ncephes_gamma, &MONE, &NCEPHES_NAN, 0},
  {"ncephes_gamma", ncephes_gamma, &ZERO, &NCEPHES_NAN, 0},
  {"ncephes_gamma", ncephes_gamma, &MINF, &NCEPHES_NAN, 0},
#if GLIBC2
  {"lncephes_gamma", lncephes_gamma, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"lncephes_gamma", lncephes_gamma, &INF, &INF, 0},
  {"lncephes_gamma", lncephes_gamma, &MONE, &INF, 0},
  {"lncephes_gamma", lncephes_gamma, &ZERO, &INF, 0},
  {"lncephes_gamma", lncephes_gamma, &MINF, &INF, 0},
#else
  {"lgam", lgam, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"lgam", lgam, &INF, &INF, 0},
  {"lgam", lgam, &MONE, &INF, 0},
  {"lgam", lgam, &ZERO, &INF, 0},
  {"lgam", lgam, &MINF, &INF, 0},
#endif
  {"ceil", ceil, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"ceil", ceil, &ZERO, &ZERO, 0},
  {"ceil", ceil, &MZERO, &MZERO, 0},
  {"ceil", ceil, &INF, &INF, 0},
  {"ceil", ceil, &MINF, &MINF, 0},
  {"floor", floor, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"floor", floor, &ZERO, &ZERO, 0},
  {"floor", floor, &MZERO, &MZERO, 0},
  {"floor", floor, &INF, &INF, 0},
  {"floor", floor, &MINF, &MINF, 0},
  {"null", NULL, &ZERO, &ZERO, 0},
};

/* Functions of two variables.  */
double atan2 (double, double);
double pow (double, double);

struct twoarguments
  {
    char *name;			/* Name of the function. */
    double (*func) (double, double);
    double *arg1;
    double *arg2;
    double *answer;
    int thresh;
  };

struct twoarguments test2[] =
{
  {"atan2", atan2, &ZERO, &ONE, &ZERO, 0},
  {"atan2", atan2, &MZERO, &ONE, &MZERO, 0},
  {"atan2", atan2, &ZERO, &ZERO, &ZERO, 0},
  {"atan2", atan2, &MZERO, &ZERO, &MZERO, 0},
  {"atan2", atan2, &ZERO, &MONE, &NCEPHES_PI, 0},
  {"atan2", atan2, &MZERO, &MONE, &MNCEPHES_PI, 0},
  {"atan2", atan2, &ZERO, &MZERO, &NCEPHES_PI, 0},
  {"atan2", atan2, &MZERO, &MZERO, &MNCEPHES_PI, 0},
  {"atan2", atan2, &ONE, &ZERO, &NCEPHES_PIO2, 0},
  {"atan2", atan2, &ONE, &MZERO, &NCEPHES_PIO2, 0},
  {"atan2", atan2, &MONE, &ZERO, &MNCEPHES_PIO2, 0},
  {"atan2", atan2, &MONE, &MZERO, &MNCEPHES_PIO2, 0},
  {"atan2", atan2, &ONE, &INF, &ZERO, 0},
  {"atan2", atan2, &MONE, &INF, &MZERO, 0},
  {"atan2", atan2, &INF, &ONE, &NCEPHES_PIO2, 0},
  {"atan2", atan2, &INF, &MONE, &NCEPHES_PIO2, 0},
  {"atan2", atan2, &MINF, &ONE, &MNCEPHES_PIO2, 0},
  {"atan2", atan2, &MINF, &MONE, &MNCEPHES_PIO2, 0},
  {"atan2", atan2, &ONE, &MINF, &NCEPHES_PI, 0},
  {"atan2", atan2, &MONE, &MINF, &MNCEPHES_PI, 0},
  {"atan2", atan2, &INF, &INF, &NCEPHES_PIO4, 0},
  {"atan2", atan2, &MINF, &INF, &MNCEPHES_PIO4, 0},
  {"atan2", atan2, &INF, &MINF, &THNCEPHES_PIO4, 0},
  {"atan2", atan2, &MINF, &MINF, &MTHNCEPHES_PIO4, 0},
  {"atan2", atan2, &ONE, &ONE, &NCEPHES_PIO4, 0},
  {"atan2", atan2, &NCEPHES_NAN, &ONE, &NCEPHES_NAN, 0},
  {"atan2", atan2, &ONE, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"atan2", atan2, &NCEPHES_NAN, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"pow", pow, &ONE, &ZERO, &ONE, 0},
  {"pow", pow, &ONE, &MZERO, &ONE, 0},
  {"pow", pow, &MONE, &ZERO, &ONE, 0},
  {"pow", pow, &MONE, &MZERO, &ONE, 0},
  {"pow", pow, &INF, &ZERO, &ONE, 0},
  {"pow", pow, &INF, &MZERO, &ONE, 0},
  {"pow", pow, &NCEPHES_NAN, &ZERO, &ONE, 0},
  {"pow", pow, &NCEPHES_NAN, &MZERO, &ONE, 0},
  {"pow", pow, &TWO, &INF, &INF, 0},
  {"pow", pow, &MTWO, &INF, &INF, 0},
  {"pow", pow, &HALF, &INF, &ZERO, 0},
  {"pow", pow, &MHALF, &INF, &ZERO, 0},
  {"pow", pow, &TWO, &MINF, &ZERO, 0},
  {"pow", pow, &MTWO, &MINF, &ZERO, 0},
  {"pow", pow, &HALF, &MINF, &INF, 0},
  {"pow", pow, &MHALF, &MINF, &INF, 0},
  {"pow", pow, &INF, &HALF, &INF, 0},
  {"pow", pow, &INF, &TWO, &INF, 0},
  {"pow", pow, &INF, &MHALF, &ZERO, 0},
  {"pow", pow, &INF, &MTWO, &ZERO, 0},
  {"pow", pow, &MINF, &THREE, &MINF, 0},
  {"pow", pow, &MINF, &TWO, &INF, 0},
  {"pow", pow, &MINF, &MTHREE, &MZERO, 0},
  {"pow", pow, &MINF, &MTWO, &ZERO, 0},
  {"pow", pow, &NCEPHES_NAN, &ONE, &NCEPHES_NAN, 0},
  {"pow", pow, &ONE, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"pow", pow, &NCEPHES_NAN, &NCEPHES_NAN, &NCEPHES_NAN, 0},
  {"pow", pow, &ONE, &INF, &NCEPHES_NAN, 0},
  {"pow", pow, &MONE, &INF, &NCEPHES_NAN, 0},
  {"pow", pow, &ONE, &MINF, &NCEPHES_NAN, 0},
  {"pow", pow, &MONE, &MINF, &NCEPHES_NAN, 0},
  {"pow", pow, &MTWO, &HALF, &NCEPHES_NAN, 0},
  {"pow", pow, &ZERO, &MTHREE, &INF, 0},
  {"pow", pow, &MZERO, &MTHREE, &MINF, 0},
  {"pow", pow, &ZERO, &MHALF, &INF, 0},
  {"pow", pow, &MZERO, &MHALF, &INF, 0},
  {"pow", pow, &ZERO, &THREE, &ZERO, 0},
  {"pow", pow, &MZERO, &THREE, &MZERO, 0},
  {"pow", pow, &ZERO, &HALF, &ZERO, 0},
  {"pow", pow, &MZERO, &HALF, &ZERO, 0},
  {"null", NULL, &ZERO, &ZERO, &ZERO, 0},
};

/* Integer functions of one variable.  */

int isnan (double);
int signbit (double);

struct intans
  {
    char *name;			/* Name of the function. */
    int (*func) (double);
    double *arg1;
    int ianswer;
  };

struct intans test3[] =
{
  {"isfinite", isfinite, &ZERO, 1},
  {"isfinite", isfinite, &INF, 0},
  {"isfinite", isfinite, &MINF, 0},
  {"isnan", isnan, &NCEPHES_NAN, 1},
  {"isnan", isnan, &INF, 0},
  {"isnan", isnan, &ZERO, 0},
  {"isnan", isnan, &MZERO, 0},
  {"signbit", signbit, &MZERO, 1},
  {"signbit", signbit, &MONE, 1},
  {"signbit", signbit, &ZERO, 0},
  {"signbit", signbit, &ONE, 0},
  {"signbit", signbit, &MINF, 1},
  {"signbit", signbit, &INF, 0},
  {"null", NULL, &ZERO, 0},
};

static volatile double x1;
static volatile double x2;
static volatile double y;
static volatile double answer;

void 
pvec (double x)
{
  union
  {
    double d;
    unsigned short s[4];
  } u;
  int i;

  u.d = x;
  for (i = 0; i < 4; i++)
    printf ("0x%04x ", u.s[i]);
  printf ("\n");
}


int 
main (void)
{
  int i, nerrors, k, ianswer, ntests;
  double (*fun1) (double);
  double (*fun2) (double, double);
  int (*fun3) (double);
  double e;
  union
    {
      double d;
      char c[8];
    } u, v;

  ZERO = 0.0;
  MZERO = NEGZERO;
  HALF = 0.5;
  MHALF = -HALF;
  ONE = 1.0;
  MONE = -ONE;
  TWO = 2.0;
  MTWO = -TWO;
  THREE = 3.0;
  MTHREE = -THREE;
  INF = NCEPHES_INF;
  MINF = -NCEPHES_INF;
  MNCEPHES_PI = -NCEPHES_PI;
  NCEPHES_PIO2 = 0.5 * NCEPHES_PI;
  MNCEPHES_PIO2 = -NCEPHES_PIO2;
  NCEPHES_PIO4 = 0.5 * NCEPHES_PIO2;
  MNCEPHES_PIO4 = -NCEPHES_PIO4;
  THNCEPHES_PIO4 = 3.0 * NCEPHES_PIO4;
  MTHNCEPHES_PIO4 = -THNCEPHES_PIO4;

  nerrors = 0;
  ntests = 0;
  i = 0;
  for (;;)
    {
      fun1 = test1[i].func;
      if (fun1 == NULL)
	break;
      x1 = *(test1[i].arg1);
      y = (*(fun1)) (x1);
      answer = *(test1[i].answer);
      if (test1[i].thresh == 0)
	{
	  v.d = answer;
	  u.d = y;
	  if (memcmp(u.c, v.c, 8) != 0)
	    {
	      if( isnan(v.d) && isnan(u.d) )
		goto nxttest1;
	      goto wrongone;
	    }
	  else
	    goto nxttest1;
	}
      if (y != answer)
	{
	  e = y - answer;
	  if (answer != 0.0)
	    e = e / answer;
	  if (e < 0)
	    e = -e;
	  if (e > test1[i].thresh * MACHEP)
	    {
wrongone:
	      printf ("%s (%.16e) = %.16e\n    should be %.16e\n",
		      test1[i].name, x1, y, answer);
	      nerrors += 1;
	    }
	}
nxttest1:
      ntests += 1;
      i += 1;
    }

  i = 0;
  for (;;)
    {
      fun2 = test2[i].func;
      if (fun2 == NULL)
	break;
      x1 = *(test2[i].arg1);
      x2 = *(test2[i].arg2);
      y = (*(fun2)) (x1, x2);
      answer = *(test2[i].answer);
      if (test2[i].thresh == 0)
	{
	  v.d = answer;
	  u.d = y;
	  if (memcmp(u.c, v.c, 8) != 0)
	    {
	      if( isnan(v.d) && isnan(u.d) )
		goto nxttest2;
#if 0
	      if( isnan(v.d) )
		pvec(v.d);
	      if( isnan(u.d) )
		pvec(u.d);
#endif
	    goto wrongtwo;
	    }
	  else
	    goto nxttest2;
	}
      if (y != answer)
	{
	  e = y - answer;
	  if (answer != 0.0)
	    e = e / answer;
	  if (e < 0)
	    e = -e;
	  if (e > test2[i].thresh * MACHEP)
	    {
wrongtwo:
	      printf ("%s (%.16e, %.16e) = %.16e\n    should be %.16e\n",
		      test2[i].name, x1, x2, y, answer);
	      nerrors += 1;
	    }
	}
nxttest2:
      ntests += 1;
      i += 1;
    }


  i = 0;
  for (;;)
    {
      fun3 = test3[i].func;
      if (fun3 == NULL)
	break;
      x1 = *(test3[i].arg1);
      k = (*(fun3)) (x1);
      ianswer = test3[i].ianswer;
      if (k != ianswer)
	{
	  printf ("%s (%.16e) = %d\n    should be. %d\n",
		  test3[i].name, x1, k, ianswer);
	  nerrors += 1;
	}
      ntests += 1;
      i += 1;
    }

  printf ("testvect: %d errors in %d tests\n", nerrors, ntests);
  exit (0);
}
