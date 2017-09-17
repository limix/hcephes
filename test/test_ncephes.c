#include "ncephes/ncephes.h"

#include <math.h>
#include <stdlib.h>

#define SUCCESS EXIT_SUCCESS
#define FAIL EXIT_FAILURE

#define assert_close(x, y)                                                     \
    if (fabs((x) - (y)) > 1e-7)                                                \
        return FAIL;

int main() {
    assert_close(ncephes_bdtr(4, 5, 0.25), 0.9990234375000000);
    assert_close(ncephes_bdtrc(4, 5, 0.25), 0.0009765625000000);
    assert_close(ncephes_bdtri(4, 5, 0.25), 0.9440875112949020);
    assert_close(ncephes_beta(6.3, 2.9), 0.005947104834350);
    assert_close(ncephes_btdtr(4, 5, 0.25), 0.1138153076171875);
    assert_close(ncephes_chdtr(4, 5), 0.7127025048163542);
    assert_close(ncephes_chdtrc(4, 5), 0.2872974951836458);
    assert_close(ncephes_chdtri(4, 0.3), 4.8784329665604087);
    assert_close(ncephes_cosm1(0.9), -0.378390031729);
    assert_close(ncephes_ellie(-5.3, 0.12), -5.12290521194);
    assert_close(ncephes_ellik(-5.3, 0.12), -5.48607395126);
    assert_close(ncephes_ellpe(0.12), 1.522555369217904);

    // assert_close(ncephes_ellpk(0.12), 2.492635323239716);

    // assert_close(ncephes_erf(1.3), 0.9340079449406524);
    // assert_close(ncephes_erfc(0.3), 0.671373240541);
    // assert_close(ncephes_expm1(0.5), 0.6487212707);
    // assert_close(ncephes_expx2(1, 2), 2.7182818284590451);
    // assert_close(ncephes_fdtr(4, 5, 0.3), 0.1333536247071635);
    // assert_close(ncephes_fdtrc(4, 5, 0.3), 0.8666463752928364);
    // assert_close(ncephes_fdtri(4, 5, 0.3), 1.6286329978911640);
    // assert_close(ncephes_gamma(1.5), 0.8862269254527579);
    // assert_close(ncephes_gdtr(1, 2, 0.1), 0.0046788401604445);
    // assert_close(ncephes_gdtrc(1, 2, 0.1), 0.9953211598395555);
    // assert_close(ncephes_igam(1, 2), 0.8646647167633873);
    // assert_close(ncephes_igamc(2, 1), 0.7357588823428847);
    // assert_close(ncephes_incbet(1., 3., 0.3), 0.657);
    // assert_close(ncephes_incbi(1., 3., 0.3), 0.1120959982573993);
    // assert_close(ncephes_kolmogi(0.24), 1.02920479826);
    // assert_close(ncephes_kolmogorov(2), 0.00067092525578);
    // assert_close(ncephes_lbeta(10, 3), -6.4922398350204711);
    // assert_close(ncephes_lgam(3.4), 1.0923280598027414);
    // assert_close(ncephes_log1p(0.1), 0.0953101798043);
    // assert_close(ncephes_nbdtr(1, 3, 0.5), 0.3125);
    // assert_close(ncephes_nbdtrc(1, 3, 0.5), 0.6875);
    // assert_close(ncephes_nbdtri(1, 3, 0.5), 0.614272431868);
    // assert_close(ncephes_ndtr(0.3), 0.617911422189);
    // assert_close(ncephes_ndtri(0.6), 0.253347103136);
    // assert_close(ncephes_pdtr(2, 0.15), 0.999497137624);
    // assert_close(ncephes_pdtrc(2, 0.15), 0.000502862376402);
    // assert_close(ncephes_pdtri(2, 0.15), 4.72305156339);
    // assert_close(ncephes_smirnov(2, 0.3), 0.61);
    // assert_close(ncephes_smirnovi(2, 0.3), 0.474679434488);
    // assert_close(ncephes_stdtr(2, 3), 0.952267016867);
    // assert_close(ncephes_stdtri(5, 0.1), -1.47588404882);

    return SUCCESS;
}
