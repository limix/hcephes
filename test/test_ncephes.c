#include "ncephes/ncephes.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef WIN32
#ifndef NAN
static const unsigned long __nan[2] = {0xffffffff, 0x7fffffff};
#define NAN (*(const float *)__nan)
#endif
#endif

#ifdef _MSC_VER
#if (_MSC_VER <= 1500)
#define isnan(x) _isnan(x)
#endif
#endif

#define SUCCESS EXIT_SUCCESS
#define FAIL EXIT_FAILURE
int test_bdtr() {
  double eps = 1e-4;

  if (fabs(ncephes_bdtr(4, 5, 0.25) - 0.9990234375000000) > eps)
    return FAIL;
  // assert_almost_equal(cprob.bdtr(4, 5, 0.25), 0.9990234375000000)
  // assert_almost_equal(cprob.bdtrc(4, 5, 0.25), 0.0009765625000000)
  // assert_almost_equal(cprob.bdtri(4, 5, 0.25), 0.9440875112949020)
  return SUCCESS;
}

int main() {
  if (test_bdtr() == FAIL)
    return FAIL;

  return SUCCESS;
}
