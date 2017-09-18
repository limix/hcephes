#include "hcephes/hcephes.h"


#include <stdio.h>
#include <stdlib.h>

#define SUCCESS EXIT_SUCCESS
#define FAIL EXIT_FAILURE

#define assert_close(x, y)                                                     \
    if (fabs((x) - (y)) > 1e-7)                                                \
        return FAIL;

int main() {
    double num = 5;
    double den = 15;
    int sign = -1;

    assert_close(hcephes_bdtr(4, 5, 0.25), 0.9990234375000000);
    assert_close(hcephes_bdtrc(4, 5, 0.25), 0.0009765625000000);
    assert_close(hcephes_bdtri(4, 5, 0.25), 0.9440875112949020);
    assert_close(hcephes_beta(6.3, 2.9), 0.005947104834350);
    assert_close(hcephes_btdtr(4, 5, 0.25), 0.1138153076171875);
    assert_close(hcephes_chdtr(4, 5), 0.7127025048163542);
    assert_close(hcephes_chdtrc(4, 5), 0.2872974951836458);
    assert_close(hcephes_chdtri(4, 0.3), 4.8784329665604087);
    assert_close(hcephes_cosm1(0.9), -0.378390031729);
    assert_close(hcephes_ellie(-5.3, 0.12), -5.12290521194);
    assert_close(hcephes_ellik(-5.3, 0.12), -5.48607395126);
    assert_close(hcephes_ellpe(0.12), 1.522555369217904);
    assert_close(hcephes_ellpk(0.12), 1.621393137980658);
    assert_close(hcephes_euclid(&num, &den), 5);
    assert_close(hcephes_expm1(0.5), 0.6487212707);
    assert_close(hcephes_expx2(2.1, 1), 82.269463504201681);
    assert_close(hcephes_fdtr(4, 5, 0.3), 0.1333536247071635);
    assert_close(hcephes_fdtrc(4, 5, 0.3), 0.8666463752928364);
    assert_close(hcephes_fdtri(4, 5, 0.3), 0.56493190151185757);
    assert_close(hcephes_gamma(1.5), 0.8862269254527579);
    assert_close(hcephes_gdtr(1, 2, 0.1), 0.0046788401604445);
    assert_close(hcephes_gdtrc(1, 2, 0.1), 0.9953211598395555);
    assert_close(hcephes_igam(1, 2), 0.8646647167633873);
    assert_close(hcephes_igamc(2, 1), 0.7357588823428847);
    assert_close(hcephes_igami(2, 0.3), 2.439216483280204);
    assert_close(hcephes_incbet(1., 3., 0.3), 0.65699999999999992);
    assert_close(hcephes_incbi(1., 3., 0.3), 0.1120959982573993);
    assert_close(hcephes_kolmogi(0.24), 1.02920479826);
    assert_close(hcephes_kolmogorov(2), 0.00067092525578);
    assert_close(hcephes_lbeta(10, 3), -6.4922398350204711);
    assert_close(hcephes_lgam(3.4), 1.0923280598027414);
    assert_close(hcephes_lgam_sgn(0.3, &sign), 1.09579799481807560468);
    assert_close(hcephes_log1p(0.1), 0.0953101798043);
    assert_close(hcephes_nbdtr(1, 3, 0.5), 0.3125);
    assert_close(hcephes_nbdtrc(1, 3, 0.5), 0.6875);
    assert_close(hcephes_nbdtri(1, 3, 0.5), 0.61427243186761038);
    assert_close(hcephes_ndtr(0.3), 0.61791142218895256);
    assert_close(hcephes_ndtri(0.6), 0.25334710313579972);
    assert_close(hcephes_pdtr(2, 0.15), 0.99949713762359838);
    assert_close(hcephes_pdtrc(2, 0.15), 0.00050286237640162121);
    assert_close(hcephes_pdtri(2, 0.15), 4.7230515633946668);
    assert_close(hcephes_smirnov(2, 0.3), 0.60999999999999999);
    assert_close(hcephes_smirnovi(2, 0.3), 0.4746794344877307);
    assert_close(hcephes_stdtr(2, 3), 0.95226701686664539);
    assert_close(hcephes_stdtri(5, 0.1), -1.4758840487820271);

    return SUCCESS;
}
