/*							beta.c
 *
 *	Beta function
 *
 *
 *
 * SYNOPSIS:
 *
 * double a, b, y, beta();
 *
 * y = beta( a, b );
 *
 *
 *
 * DESCRIPTION:
 *
 *                   -     -
 *                  | (a) | (b)
 * beta( a, b )  =  -----------.
 *                     -
 *                    | (a+b)
 *
 * For large arguments the logarithm of the function is
 * evaluated using lgam(), then exponentiated.
 *
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    DEC        0,30        1700       7.7e-15     1.5e-15
 *    IEEE       0,30       30000       8.1e-14     1.1e-14
 *
 * ERROR MESSAGES:
 *
 *   message         condition          value returned
 * beta overflow    log(beta) > MAXLOG       0.0
 *                  a or b <0 integer        0.0
 *
 */

/*							beta.c	*/


/*
Cephes Math Library Release 2.0:  April, 1987
Copyright 1984, 1987 by Stephen L. Moshier
Direct inquiries to 30 Frost Street, Cambridge, MA 02140
*/

#include "mconf.h"

#ifdef UNK
#define MAXGAM 34.84425627277176174
#endif
#ifdef DEC
#define MAXGAM 34.84425627277176174
#endif
#ifdef IBMPC
#define MAXGAM 171.624376956302725
#endif
#ifdef MIEEE
#define MAXGAM 171.624376956302725
#endif

#ifdef ANSIPROT
extern double fabs ( double );
extern double cephes_gamma ( double );
extern double lgam_sgn ( double, int * );
extern double exp ( double );
extern double log ( double );
extern double floor ( double );
#else
double fabs(), cephes_gamma(), lgam(), exp(), log(), floor();
#endif
extern double MAXLOG, NCEPHES_MAXNUM;

double 
beta (double a, double b)
{
double y;
int sign;

sign = 1;

if( a <= 0.0 )
	{
	if( a == floor(a) )
		goto over;
	}
if( b <= 0.0 )
	{
	if( b == floor(b) )
		goto over;
	}


y = a + b;
if( fabs(y) > MAXGAM )
	{
    int sgngam;
	y = lgam_sgn(y, &sgngam);
	sign *= sgngam; /* keep track of the sign */
	y = lgam_sgn(b, &sgngam) - y;
	sign *= sgngam;
	y = lgam_sgn(a, &sgngam) + y;
	sign *= sgngam;
	if( y > MAXLOG )
		{
over:
		mtherr( "beta", OVERFLOW );
		return( sign * NCEPHES_MAXNUM );
		}
	return( sign * exp(y) );
	}

y = cephes_gamma(y);
if( y == 0.0 )
	goto over;

if( a > b )
	{
	y = cephes_gamma(a)/y;
	y *= cephes_gamma(b);
	}
else
	{
	y = cephes_gamma(b)/y;
	y *= cephes_gamma(a);
	}

return(y);
}



/* Natural log of |beta|.  Return the sign of beta in sgngam.  */

double 
lbeta (double a, double b)
{
double y;
int sign;

sign = 1;

if( a <= 0.0 )
	{
	if( a == floor(a) )
		goto over;
	}
if( b <= 0.0 )
	{
	if( b == floor(b) )
		goto over;
	}


y = a + b;
if( fabs(y) > MAXGAM )
	{
    int sgngam;
	y = lgam_sgn(y, &sgngam);
	sign *= sgngam; /* keep track of the sign */
	y = lgam_sgn(b, &sgngam) - y;
	sign *= sgngam;
	y = lgam_sgn(a, &sgngam) + y;
	sign *= sgngam;
	sgngam = sign;
	return( y );
	}

y = cephes_gamma(y);
if( y == 0.0 )
	{
over:
	mtherr( "lbeta", OVERFLOW );
	return( sign * NCEPHES_MAXNUM );
	}

if( a > b )
	{
	y = cephes_gamma(a)/y;
	y *= cephes_gamma(b);
	}
else
	{
	y = cephes_gamma(b)/y;
	y *= cephes_gamma(a);
	}

if( y < 0 )
    y = -y;

return( log(y) );
}
