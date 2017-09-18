#ifndef NCEPHES_MCONF_H
#define NCEPHES_MCONF_H

/* Constant definitions for math error conditions
 */
#define NCEPHES_DOMAIN 1    /* argument domain error */
#define NCEPHES_OVERFLOW 3  /* overflow range error */
#define NCEPHES_UNDERFLOW 4 /* underflow range error */
#define NCEPHES_SING 2      /* argument singularity */
#define NCEPHES_PLOSS 6     /* partial loss of precision */
#define NCEPHES_ERANGE 34

/* Type of computer arithmetic */

/* UNKnown arithmetic, invokes coefficients given in
 * normal decimal format.  Beware of range boundary
 * problems (MACHEP, MAXLOG, etc. in const.c) and
 * roundoff problems in pow.c:
 * (Sun SPARCstation)
 */

/* SciPy note: by defining UNK, we prevent the compiler from
 * casting integers to floating point numbers.  If the Endianness
 * is detected incorrectly, this causes problems on some platforms.
 */
#define NCEPHES_UNK 1

/* If you define UNK, then be sure to set BIGENDIAN properly. */
#ifdef FLOAT_WORDS_BIGENDIAN
#define BIGENDIAN 1
#else
#define BIGENDIAN 0
#endif

int ncephes_mtherr(char *name, int code);

#endif /* NCEPHES_MCONF_H */
