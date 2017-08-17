/* ellf.c
 * 
 * Read ellf.doc before attempting to compile this program.
 */


#include <stdio.h>
#include <stdlib.h>

/* size of arrays: */
#define ARRSIZ 50


/* System configurations */
#include "mconf.h"


extern double NCEPHES_PI, NCEPHES_PIO2, MACHEP, NCEPHES_MAXNUM;

static double aa[ARRSIZ];
static double pp[ARRSIZ];
static double y[ARRSIZ];
static double zs[ARRSIZ];
cmplx z[ARRSIZ];
static double wr = 0.0;
static double cbp = 0.0;
static double wc = 0.0;
static double rn = 8.0;
static double c = 0.0;
static double cgam = 0.0;
static double scale = 0.0;
double fs = 1.0e4;
double dbfac = 0.0;
static double a = 0.0;
static double b = 0.0;
static double q = 0.0;
static double r = 0.0;
static double u = 0.0;
static double k = 0.0;
static double m = 0.0;
static double Kk = 0.0;
static double Kk1 = 0.0;
static double Kpk = 0.0;
static double Kpk1 = 0.0;
static double eps = 0.0;
static double rho = 0.0;
static double phi = 0.0;
static double sn = 0.0;
static double cn = 0.0;
static double dn = 0.0;
static double sn1 = 0.0;
static double cn1 = 0.0;
static double dn1 = 0.0;
static double phi1 = 0.0;
static double m1 = 0.0;
static double m1p = 0.0;
double fnyq = 0.0;
static double ai = 0.0;
static double pn = 0.0;
static double an = 0.0;
static double gam = 0.0;
static double cng = 0.0;
double gain = 0.0;
static int lr = 0;
static int nt = 0;
static int i = 0;
static int j = 0;
static int jt = 0;
static int nc = 0;
static int ii = 0;
static int ir = 0;
int zord = 0;
static int icnt = 0;
static int mh = 0;
static int jj = 0;
static int jh = 0;
static int jl = 0;
static int n = 8;
static int np = 0;
static int nz = 0;
static int type = 1;
static int kind = 1;


#ifdef ANSIPROT
extern double exp ( double );
extern double log ( double );
extern double cos ( double );
extern double sin ( double );
extern double sqrt ( double );
extern double fabs ( double );
extern double asin ( double );
extern double atan ( double );
extern double atan2 ( double, double );
extern double pow ( double, double );
extern double ncephes_cabs ( cmplx *z );
extern void cadd ( cmplx *a, cmplx *b, cmplx *c );
extern void cdiv ( cmplx *a, cmplx *b, cmplx *c );
extern void cmov ( void *a, void *b );
extern void cmul ( cmplx *a, cmplx *b, cmplx *c );
extern void cneg ( cmplx *a );
extern void ncephes_csqrt ( cmplx *z, cmplx *w );
extern void csub ( cmplx *a, cmplx *b, cmplx *c );
extern double ellie ( double phi, double m );
extern double ellik ( double phi, double m );
extern double ellpe ( double x );
extern int ellpj ( double, double, double *, double *, double *, double * );
extern double ellpk ( double x );
double cay ( double q );
int lampln ( void );
int spln ( void );
int xfun ( void );
int zplna ( void );
int zplnb ( void );
int zplnc ( void );
int quadf ( double, double, int );
double response ( double, double );
#else
double exp(), log(), cos(), sin(), sqrt();
double ellpk(), ellik(), asin(), atan(), atan2(), pow();
double cay(), ncephes_cabs();
double response();
int lampln(), spln(), xfun(), zplna(), zplnb(), zplnc(), quadf();
#define fabs(x) ( (x) < 0 ? -(x) : (x) )
#endif


int 
lampln (void)
{

wc = 1.0;
k = wc/wr;
m = k * k;
Kk = ellpk( 1.0 - m );
Kpk = ellpk( m );
q = exp( -NCEPHES_PI * rn * Kpk / Kk );	/* the nome of k1 */
m1 = cay(q); /* see below */
/* Note m1 = eps / sqrt( A*A - 1.0 ) */
a = eps/m1;
a =  a * a + 1;
a = 10.0 * log(a) / log(10.0);
printf( "dbdown %.9E\n", a );
a = 180.0 * asin( k ) / NCEPHES_PI;
b = 1.0/(1.0 + eps*eps);
b = sqrt( 1.0 - b );
printf( "theta %.9E, rho %.9E\n", a, b );
m1 *= m1;
m1p = 1.0 - m1;
Kk1 = ellpk( m1p );
Kpk1 = ellpk( m1 );
r = Kpk1 * Kk / (Kk1 * Kpk);
printf( "consistency check: n= %.14E\n", r );
/*   -1
 * sn   j/eps\m  =  j ellik( atan(1/eps), m )
 */
b = 1.0/eps;
phi = atan( b );
u = ellik( phi, m1p );
printf( "phi %.7e m %.7e u %.7e\n", phi, m1p, u );
/* consistency check on inverse sn */
ellpj( u, m1p, &sn, &cn, &dn, &phi );
a = sn/cn;
printf( "consistency check: sn/cn = %.9E = %.9E = 1/eps\n", a, b );
u = u * Kk / (rn * Kk1);	/* or, u = u * Kpk / Kpk1 */
return 0;
}




/* calculate s plane poles and zeros, normalized to wc = 1 */
int 
spln (void)
{
for( i=0; i<ARRSIZ; i++ )
	zs[i] = 0.0;
np = (n+1)/2;
nz = 0;
if( kind == 1 )
	{
/* Butterworth poles equally spaced around the unit circle
 */
	if( n & 1 )
		m = 0.0;
	else
		m = NCEPHES_PI / (2.0*n);
	for( i=0; i<np; i++ )
		{	/* poles */
		lr = i + i;
		zs[lr] = -cos(m);
		zs[lr+1] = sin(m);
		m += NCEPHES_PI / n;
		}	
	/* high pass or band reject
	 */
	if( type >= 3 )
		{
		/* map s => 1/s
		 */
		for( j=0; j<np; j++ )
			{
			ir = j + j;
			ii = ir + 1;
			b = zs[ir]*zs[ir] + zs[ii]*zs[ii];
			zs[ir] = zs[ir] / b;
			zs[ii] = zs[ii] / b;
			}
		/* The zeros at infinity map to the origin.
		 */
		nz = np;
		if( type == 4 )
			{
			nz += n/2;
			}
		for( j=0; j<nz; j++ )
			{
			ir = ii + 1;
			ii = ir + 1;
			zs[ir] = 0.0;
			zs[ii] = 0.0;
			}
		}
	}
if( kind == 2 )
	{
	/* For Chebyshev, find radii of two Butterworth circles
	 * See Gold & Rader, page 60
	 */
	rho = (phi - 1.0)*(phi+1);  /* rho = eps^2 = {sqrt(1+eps^2)}^2 - 1 */
	eps = sqrt(rho);
	/* sqrt( 1 + 1/eps^2 ) + 1/eps  = {sqrt(1 + eps^2)  +  1} / eps
	 */
	phi = (phi + 1.0) / eps;
	phi = pow( phi, 1.0/rn );  /* raise to the 1/n power */
	b = 0.5 * (phi + 1.0/phi); /* y coordinates are on this circle */
	a = 0.5 * (phi - 1.0/phi); /* x coordinates are on this circle */
	if( n & 1 )
		m = 0.0;
	else
		m = NCEPHES_PI / (2.0*n);
	for( i=0; i<np; i++ )
		{	/* poles */
		lr = i + i;
		zs[lr] = -a * cos(m);
		zs[lr+1] = b * sin(m);
		m += NCEPHES_PI / n;
		}	
	/* high pass or band reject
	 */
	if( type >= 3 )
		{
		/* map s => 1/s
		 */
		for( j=0; j<np; j++ )
			{
			ir = j + j;
			ii = ir + 1;
			b = zs[ir]*zs[ir] + zs[ii]*zs[ii];
			zs[ir] = zs[ir] / b;
			zs[ii] = zs[ii] / b;
			}
		/* The zeros at infinity map to the origin.
		 */
		nz = np;
		if( type == 4 )
			{
			nz += n/2;
			}
		for( j=0; j<nz; j++ )
			{
			ir = ii + 1;
			ii = ir + 1;
			zs[ir] = 0.0;
			zs[ii] = 0.0;
			}
		}
	}
if( kind == 3 )
	{
	nz = n/2;
	ellpj( u, 1.0-m, &sn1, &cn1, &dn1, &phi1 );
	for( i=0; i<ARRSIZ; i++ )
		zs[i] = 0.0;
	for( i=0; i<nz; i++ )
		{	/* zeros */
		a = n - 1 - i - i;
		b = (Kk * a) / rn;
		ellpj( b, m, &sn, &cn, &dn, &phi );
		lr = 2*np + 2*i;
		zs[ lr ] = 0.0;
		a = wc/(k*sn);	/* k = sqrt(m) */
		zs[ lr + 1 ] = a;
		}
	for( i=0; i<np; i++ )
		{	/* poles */
		a = n - 1 - i - i;
		b = a * Kk / rn;		
		ellpj( b, m, &sn, &cn, &dn, &phi );
		r = k * sn * sn1;
		b = cn1*cn1 + r*r;
		a = -wc*cn*dn*sn1*cn1/b;
		lr = i + i;
		zs[lr] = a;
		b = wc*sn*dn1/b;
		zs[lr+1] = b;
		}	
	if( type >= 3 )
		{
		nt = np + nz;
		for( j=0; j<nt; j++ )
			{
			ir = j + j;
			ii = ir + 1;
			b = zs[ir]*zs[ir] + zs[ii]*zs[ii];
			zs[ir] = zs[ir] / b;
			zs[ii] = zs[ii] / b;
			}
		while( np > nz )
			{
			ir = ii + 1;
			ii = ir + 1;
			nz += 1;
			zs[ir] = 0.0;
			zs[ii] = 0.0;
			}
		}
	}
printf( "s plane poles:\n" );
j = 0;
for( i=0; i<np+nz; i++ )
	{
	a = zs[j];
	++j;
	b = zs[j];
	++j;
	printf( "%.9E %.9E\n", a, b );
	if( i == np-1 )
		printf( "s plane zeros:\n" );
	}
return 0;
}






/*		cay()
 *
 * Find parameter corresponding to given nome by expansion
 * in theta functions:
 * AMS55 #16.38.5, 16.38.7
 *
 *       1/2
 * ( 2K )                   4     9
 * ( -- )     =  1 + 2q + 2q  + 2q  + ...  =  Theta (0,q)
 * ( pi )                                          3
 *
 *
 *       1/2
 * ( 2K )     1/4       1/4        2    6    12    20
 * ( -- )    m     =  2q    ( 1 + q  + q  + q   + q   + ...) = Theta (0,q)
 * ( pi )                                                           2
 *
 * The nome q(m) = exp( - pi K(1-m)/K(m) ).
 *
 *                                1/2
 * Given q, this program returns m   .
 */
double 
cay (double q)
{
double a, b, p, r;
double t1, t2;

a = 1.0;
b = 1.0;
r = 1.0;
p = q;

do
{
r *= p;
a += 2.0 * r;
t1 = fabs( r/a );

r *= p;
b += r;
p *= q;
t2 = fabs( r/b );
if( t2 > t1 )
	t1 = t2;
}
while( t1 > MACHEP );

a = b/a;
a = 4.0 * sqrt(q) * a * a;	/* see above formulas, solved for m */
return(a);
}




/*		zpln.c
 * Program to convert s plane poles and zeros to the z plane.
 */

extern cmplx cone;

int 
zplna (void)
{
cmplx r, cnum, cden, cwc, ca, cb, b4ac;
double C;

if( kind == 3 )
	C = c;
else
	C = wc;

for( i=0; i<ARRSIZ; i++ )
	{
	z[i].r = 0.0;
	z[i].i = 0.0;
	}

nc = np;
jt = -1;
ii = -1;

for( icnt=0; icnt<2; icnt++ )
{
	/* The maps from s plane to z plane */
do
	{
	ir = ii + 1;
	ii = ir + 1;
	r.r = zs[ir];
	r.i = zs[ii];

	switch( type )
		{
		case 1:
		case 3:
/* Substitute  s - r  =  s/wc - r = (1/wc)(z-1)/(z+1) - r
 *
 *     1  1 - r wc (       1 + r wc )
 * =  --- -------- ( z  -  -------- )
 *    z+1    wc    (       1 - r wc )
 *
 * giving the root in the z plane.
 */
		cnum.r = 1 + C * r.r;
		cnum.i = C * r.i;
		cden.r = 1 - C * r.r;
		cden.i = -C * r.i;
		jt += 1;
		cdiv( &cden, &cnum, &z[jt] );
		if( r.i != 0.0 )
			{
		/* fill in complex conjugate root */
			jt += 1;
			z[jt].r = z[jt-1 ].r;
			z[jt].i = -z[jt-1 ].i;
			}
		break;

		case 2:
		case 4:
/* Substitute  s - r  =>  s/wc - r
 *
 *     z^2 - 2 z cgam + 1
 * =>  ------------------  -  r
 *         (z^2 + 1) wc  
 *
 *         1
 * =  ------------  [ (1 - r wc) z^2  - 2 cgam z  +  1 + r wc ]
 *    (z^2 + 1) wc  
 *
 * and solve for the roots in the z plane.
 */
		if( kind == 2 )
			cwc.r = cbp;
		else
			cwc.r = c;
		cwc.i = 0.0;
		cmul( &r, &cwc, &cnum );     /* r wc */
		csub( &cnum, &cone, &ca );   /* a = 1 - r wc */
		cmul( &cnum, &cnum, &b4ac ); /* 1 - (r wc)^2 */
		csub( &b4ac, &cone, &b4ac );
		b4ac.r *= 4.0;               /* 4ac */
		b4ac.i *= 4.0;
		cb.r = -2.0 * cgam;          /* b */
		cb.i = 0.0;
		cmul( &cb, &cb, &cnum );     /* b^2 */
		csub( &b4ac, &cnum, &b4ac ); /* b^2 - 4 ac */
		ncephes_csqrt( &b4ac, &b4ac );
		cb.r = -cb.r;  /* -b */
		cb.i = -cb.i;
		ca.r *= 2.0; /* 2a */
		ca.i *= 2.0;
		cadd( &b4ac, &cb, &cnum );   /* -b + sqrt( b^2 - 4ac) */
		cdiv( &ca, &cnum, &cnum );   /* ... /2a */
		jt += 1;
		cmov( &cnum, &z[jt] );
		if( cnum.i != 0.0 )
			{
			jt += 1;
			z[jt].r = cnum.r;
			z[jt].i = -cnum.i;
			}
		if( (r.i != 0.0) || (cnum.i == 0) )
			{
			csub( &b4ac, &cb, &cnum );  /* -b - sqrt( b^2 - 4ac) */
			cdiv( &ca, &cnum, &cnum );  /* ... /2a */
			jt += 1;
			cmov( &cnum, &z[jt] );
			if( cnum.i != 0.0 )
				{
				jt += 1;
				z[jt].r = cnum.r;
				z[jt].i = -cnum.i;
				}
			}
		} /* end switch */
	}
	while( --nc > 0 );

if( icnt == 0 )
	{
	zord = jt+1;
	if( nz <= 0 )
		{
		if( kind != 3 )
			return(0);
		else
			break;
		}
	}
nc = nz;
} /* end for() loop */
return 0;
}




int 
zplnb (void)
{

if( kind != 3 )
	{ /* Butterworth or Chebyshev */
/* generate the remaining zeros */
	while( 2*zord - 1 > jt )
		{
		if( type != 3 )
			{
	printf( "adding zero at Nyquist frequency\n" );
			jt += 1;
			z[jt].r = -1.0; /* zero at Nyquist frequency */
			z[jt].i = 0.0;
			}
		if( (type == 2) || (type == 3) )
			{
	printf( "adding zero at 0 Hz\n" );
			jt += 1;
			z[jt].r = 1.0; /* zero at 0 Hz */
			z[jt].i = 0.0;
			}
		}
	}
else
	{ /* elliptic */
	while( 2*zord - 1 > jt )
		{
		jt += 1;
		z[jt].r = -1.0; /* zero at Nyquist frequency */
		z[jt].i = 0.0;
		if( (type == 2) || (type == 4) )
			{
			jt += 1;
			z[jt].r = 1.0; /* zero at 0 Hz */
			z[jt].i = 0.0;
			}
		}
	}
printf( "order = %d\n", zord );

/* Expand the poles and zeros into numerator and
 * denominator polynomials
 */
for( icnt=0; icnt<2; icnt++ )
	{
	for( j=0; j<ARRSIZ; j++ )
		{
		pp[j] = 0.0;
		y[j] = 0.0;
		}
	pp[0] = 1.0;
	for( j=0; j<zord; j++ )
		{
		jj = j;
		if( icnt )
			jj += zord;
		a = z[jj].r;
		b = z[jj].i;
		for( i=0; i<=j; i++ )
			{
			jh = j - i;
			pp[jh+1] = pp[jh+1] - a * pp[jh] + b * y[jh];
			y[jh+1] =  y[jh+1]  - b * pp[jh] - a * y[jh];
			}
		}
	if( icnt == 0 )
		{
		for( j=0; j<=zord; j++ )
			aa[j] = pp[j];
		}
	}
/* Scale factors of the pole and zero polynomials */
a = 1.0;
switch( type )
	{
	case 3:
	a = -1.0;

	case 1:
	case 4:

	pn = 1.0;
	an = 1.0;
	for( j=1; j<=zord; j++ )
		{
		pn = a * pn + pp[j];
		an = a * an + aa[j];
		}
	break;

	case 2:
	gam = NCEPHES_PI/2.0 - asin( cgam );  /* = acos( cgam ) */
	mh = zord/2;
	pn = pp[mh];
	an = aa[mh];
	ai = 0.0;
	if( mh > ((zord/4)*2) )
		{
		ai = 1.0;
		pn = 0.0;
		an = 0.0;
		}
	for( j=1; j<=mh; j++ )
		{
		a = gam * j - ai * NCEPHES_PI / 2.0;
		cng = cos(a);
		jh = mh + j;
		jl = mh - j;
		pn = pn + cng * (pp[jh] + (1.0 - 2.0 * ai) * pp[jl]);
		an = an + cng * (aa[jh] + (1.0 - 2.0 * ai) * aa[jl]);
		}
	}
return 0;
}




int 
zplnc (void)
{

gain = an/(pn*scale);
if( (kind != 3) && (pn == 0) )
	gain = 1.0;
printf( "constant gain factor %23.13E\n", gain );
for( j=0; j<=zord; j++ )
	pp[j] = gain * pp[j];

printf( "z plane Denominator      Numerator\n" );
for( j=0; j<=zord; j++ )
	{
	printf( "%2d %17.9E %17.9E\n", j, aa[j], pp[j] );
	}
printf( "poles and zeros with corresponding quadratic factors\n" );
for( j=0; j<zord; j++ )
	{
	a = z[j].r;
	b = z[j].i;
	if( b >= 0.0 )
		{
		printf( "pole  %23.13E %23.13E\n", a, b );
		quadf( a, b, 1 );
		}
	jj = j + zord;
	a = z[jj].r;
	b = z[jj].i;
	if( b >= 0.0 )
		{
		printf( "zero  %23.13E %23.13E\n", a, b );
		quadf( a, b, 0 );
		}
	}
return 0;
}




/* display quadratic factors
 */
int 
quadf (
    double x,
    double y,
    int pzflg	/* 1 if poles, 0 if zeros */
)
{
double a, b, r, f, g, g0;

if( y > 1.0e-16 )
	{
	a = -2.0 * x;
	b = x*x + y*y;
	}
else
	{
	a = -x;
	b = 0.0;
	}
printf( "q. f.\nz**2 %23.13E\nz**1 %23.13E\n", b, a );
if( b != 0.0 )
	{
/* resonant frequency */
	r = sqrt(b);
	f = NCEPHES_PI/2.0 - asin( -a/(2.0*r) );
	f = f * fs / (2.0 * NCEPHES_PI );
/* gain at resonance */
	g = 1.0 + r;
	g = g*g - (a*a/r);
	g = (1.0 - r) * sqrt(g);
	g0 = 1.0 + a + b;	/* gain at d.c. */
	}
else
	{
/* It is really a first-order network.
 * Give the gain at fnyq and D.C.
 */
	f = fnyq;
	g = 1.0 - a;
	g0 = 1.0 + a;
	}

if( pzflg )
	{
	if( g != 0.0 )
		g = 1.0/g;
	else
		g = NCEPHES_MAXNUM;
	if( g0 != 0.0 )
		g0 = 1.0/g0;
	else
		g = NCEPHES_MAXNUM;
	}
printf( "f0 %16.8E  gain %12.4E  DC gain %12.4E\n\n", f, g, g0 );
return 0;
}



/* Print table of filter frequency response
 */
int 
xfun (void)
{
double f, r;
int i;

f = 0.0;

for( i=0; i<=20; i++ )
	{
	r = response( f, gain );
	if( r <= 0.0 )
		r = -999.99;
	else
		r = 2.0 * dbfac * log( r );
	printf( "%10.1f  %10.2f\n", f, r );
	f = f + 0.05 * fnyq;
	}
return 0;
}


/* Calculate frequency response at f Hz
 * mulitplied by amp
 */
double 
response (double f, double amp)
{
cmplx x, num, den, w;
double u;
int j;

/* exp( j omega T ) */
u = 2.0 * NCEPHES_PI * f /fs;
x.r = cos(u);
x.i = sin(u);

num.r = 1.0;
num.i = 0.0;
den.r = 1.0;
den.i = 0.0;
for( j=0; j<zord; j++ )
	{
	csub( &z[j], &x, &w );
	cmul( &w, &den, &den );
	csub( &z[j+zord], &x, &w );
	cmul( &w, &num, &num );
	}
cdiv( &den, &num, &w );
w.r *= amp;
w.i *= amp;
u = ncephes_cabs( &w );
return(u);
}


