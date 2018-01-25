#include "hcephes.h"

#define EPS 1.0e-13
#define EPS2 1.0e-10

#define ETHRESH 1.0e-12

#ifdef _MSC_VER
#if (_MSC_VER <= 1500)
#define round(dbl)                                                             \
  dbl >= 0.0                                                                   \
      ? (int)(dbl + 0.5)                                                       \
      : ((dbl - (double)(int)dbl) <= -0.5 ? (int)dbl : (int)(dbl - 0.5))
#endif
#endif

static double hcephes_hyt2f1(double a, double b, double c, double x,
                             double *loss);
static double hcephes_hys2f1(double a, double b, double c, double x,
                             double *loss);

double hcephes_hyp2f1(double a, double b, double c, double x) {
  double d, d1, d2, e;
  double p, q, r, s, y, ax;
  double ia, ib, ic, id, err;
  int flag, i, aid;

  err = 0.0;
  ax = fabs(x);
  s = 1.0 - x;
  flag = 0;
  ia = round(a); /* nearest integer to a */
  ib = round(b);

  if (a <= 0) {
    if (fabs(a - ia) < EPS) /* a is a negative integer */
      flag |= 1;
  }

  if (b <= 0) {
    if (fabs(b - ib) < EPS) /* b is a negative integer */
      flag |= 2;
  }

  if (ax < 1.0) {
    if (fabs(b - c) < EPS) /* b = c */
    {
      y = pow(s, -a); /* s to the -a power */
      goto hypdon;
    }
    if (fabs(a - c) < EPS) /* a = c */
    {
      y = pow(s, -b); /* s to the -b power */
      goto hypdon;
    }
  }

  if (c <= 0.0) {
    ic = round(c);          /* nearest integer to c */
    if (fabs(c - ic) < EPS) /* c is a negative integer */
    {
      /* check if termination before explosion */
      if ((flag & 1) && (ia > ic))
        goto hypok;
      if ((flag & 2) && (ib > ic))
        goto hypok;
      goto hypdiv;
    }
  }

  if (flag) /* function is a polynomial */
    goto hypok;

  if (ax > 1.0) /* series diverges	*/
    goto hypdiv;

  p = c - a;
  ia = round(p);                           /* nearest integer to c-a */
  if ((ia <= 0.0) && (fabs(p - ia) < EPS)) /* negative int c - a */
    flag |= 4;

  r = c - b;
  ib = round(r);                           /* nearest integer to c-b */
  if ((ib <= 0.0) && (fabs(r - ib) < EPS)) /* negative int c - b */
    flag |= 8;

  d = c - a - b;
  id = round(d); /* nearest integer to d */
  q = fabs(d - id);

  /* Thanks to Christian Burger <BURGER@DMRHRZ11.HRZ.Uni-Marburg.DE>
   * for reporting a bug here.  */
  if (fabs(ax - 1.0) < EPS) /* |x| == 1.0	*/
  {
    if (x > 0.0) {
      if (flag & 12) /* negative int c-a or c-b */
      {
        if (d >= 0.0)
          goto hypf;
        else
          goto hypdiv;
      }
      if (d <= 0.0)
        goto hypdiv;
      y = hcephes_gamma(c) * hcephes_gamma(d) /
          (hcephes_gamma(p) * hcephes_gamma(r));
      goto hypdon;
    }

    if (d <= -1.0)
      goto hypdiv;
  }

  /* Conditionally make d > 0 by recurrence on c
   * AMS55 #15.2.27
   */
  if (d < 0.0) {
    /* Try the power series first */
    y = hcephes_hyt2f1(a, b, c, x, &err);
    if (err < ETHRESH)
      goto hypdon;
    /* Apply the recurrence if power series fails */
    err = 0.0;
    aid = 2 - id;
    e = c + aid;
    d2 = hcephes_hyp2f1(a, b, e, x);
    d1 = hcephes_hyp2f1(a, b, e + 1.0, x);
    q = a + b + 1.0;
    for (i = 0; i < aid; i++) {
      r = e - 1.0;
      y = (e * (r - (2.0 * e - q) * x) * d2 + (e - a) * (e - b) * x * d1) /
          (e * r * s);
      e = r;
      d1 = d2;
      d2 = y;
    }
    goto hypdon;
  }

  if (flag & 12)
    goto hypf; /* negative integer c-a or c-b */

hypok:
  y = hcephes_hyt2f1(a, b, c, x, &err);

hypdon:
  if (err > ETHRESH) {
    hcephes_mtherr("hyp2f1", PLOSS);
    /*	printf( "Estimated err = %.2e\n", err ); */
  }
  return (y);

/* The transformation for c-a or c-b negative integer
 * AMS55 #15.3.3
 */
hypf:
  y = pow(s, d) * hcephes_hys2f1(c - a, c - b, c, x, &err);
  goto hypdon;

/* The alarm exit */
hypdiv:
  hcephes_mtherr("hyp2f1", OVERFLOW);
  return (HUGE_VAL);
}

/* Apply transformations for |x| near 1
 * then call the power series
 */
static double hcephes_hyt2f1(double a, double b, double c, double x,
                             double *loss) {
  double p, q, r, s, t, y, d, err, err1;
  double ax, id, d1, d2, e, y1;
  int i, aid;

  err = 0.0;
  s = 1.0 - x;
  if (x < -0.5) {
    if (b > a)
      y = pow(s, -a) * hcephes_hys2f1(a, c - b, c, -x / s, &err);

    else
      y = pow(s, -b) * hcephes_hys2f1(c - a, b, c, -x / s, &err);

    goto done;
  }

  d = c - a - b;
  id = round(d); /* nearest integer to d */

  if (x > 0.9) {
    if (fabs(d - id) > EPS) /* test for integer c-a-b */
    {
      /* Try the power series first */
      y = hcephes_hys2f1(a, b, c, x, &err);
      if (err < ETHRESH)
        goto done;
      /* If power series fails, then apply AMS55 #15.3.6 */
      q = hcephes_hys2f1(a, b, 1.0 - d, s, &err);
      q *= hcephes_gamma(d) / (hcephes_gamma(c - a) * hcephes_gamma(c - b));
      r = pow(s, d) * hcephes_hys2f1(c - a, c - b, d + 1.0, s, &err1);
      r *= hcephes_gamma(-d) / (hcephes_gamma(a) * hcephes_gamma(b));
      y = q + r;

      q = fabs(q); /* estimate cancellation error */
      r = fabs(r);
      if (q > r)
        r = q;
      err += err1 + (HCEPHES_MACHEP * r) / y;

      y *= hcephes_gamma(c);
      goto done;
    } else {
      /* Psi function expansion, AMS55 #15.3.10, #15.3.11, #15.3.12 */
      if (id >= 0.0) {
        e = d;
        d1 = d;
        d2 = 0.0;
        aid = id;
      } else {
        e = -d;
        d1 = 0.0;
        d2 = d;
        aid = -id;
      }

      ax = log(s);

      /* sum for t = 0 */
      y = hcephes_psi(1.0) + hcephes_psi(1.0 + e) - hcephes_psi(a + d1) -
          hcephes_psi(b + d1) - ax;
      y /= hcephes_gamma(e + 1.0);

      p = (a + d1) * (b + d1) * s / hcephes_gamma(e + 2.0); /* Poch for t=1 */
      t = 1.0;
      do {
        r = hcephes_psi(1.0 + t) + hcephes_psi(1.0 + t + e) -
            hcephes_psi(a + t + d1) - hcephes_psi(b + t + d1) - ax;
        q = p * r;
        y += q;
        p *= s * (a + t + d1) / (t + 1.0);
        p *= (b + t + d1) / (t + 1.0 + e);
        t += 1.0;
      } while (fabs(q / y) > EPS);

      if (id == 0.0) {
        y *= hcephes_gamma(c) / (hcephes_gamma(a) * hcephes_gamma(b));
        goto psidon;
      }

      y1 = 1.0;

      if (aid == 1)
        goto nosum;

      t = 0.0;
      p = 1.0;
      for (i = 1; i < aid; i++) {
        r = 1.0 - e + t;
        p *= s * (a + t + d2) * (b + t + d2) / r;
        t += 1.0;
        p /= t;
        y1 += p;
      }
    nosum:
      p = hcephes_gamma(c);
      y1 *= hcephes_gamma(e) * p /
            (hcephes_gamma(a + d1) * hcephes_gamma(b + d1));

      y *= p / (hcephes_gamma(a + d2) * hcephes_gamma(b + d2));
      if ((aid & 1) != 0)
        y = -y;

      q = pow(s, id); /* s to the id power */
      if (id > 0.0)
        y *= q;
      else
        y1 *= q;

      y += y1;
    psidon:
      goto done;
    }
  }

  /* Use defining power series if no special cases */
  y = hcephes_hys2f1(a, b, c, x, &err);

done:
  *loss = err;
  return (y);
}

/* Defining power series expansion of Gauss hypergeometric function */

static double hcephes_hys2f1(double a, double b, double c, double x,
                             double *loss) {
  double f, g, h, k, m, s, u, umax;
  int i;

  i = 0;
  umax = 0.0;
  f = a;
  g = b;
  h = c;
  s = 1.0;
  u = 1.0;
  k = 0.0;
  do {
    if (fabs(h) < EPS) {
      *loss = 1.0;
      return (HUGE_VAL);
    }
    m = k + 1.0;
    u = u * ((f + k) * (g + k) * x / ((h + k) * m));
    s += u;
    k = fabs(u); /* remember largest term summed */
    if (k > umax)
      umax = k;
    k = m;
    if (++i > 10000) /* should never happen */
    {
      *loss = 1.0;
      return (s);
    }
  } while (fabs(u / s) > HCEPHES_MACHEP);

  /* return estimated relative error */
  *loss = (HCEPHES_MACHEP * umax) / fabs(s) + (HCEPHES_MACHEP * i);

  return (s);
}
