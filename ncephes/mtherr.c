#include "mconf.h"
#include <stdio.h>

int merror = 0;

/* Notice: the order of appearance of the following
 * messages is bound to the error codes defined
 * in mconf.h.
 */
static char *ermsg[7] = {"unknown",     /* error code 0 */
                         "domain",      /* error code 1 */
                         "singularity", /* et seq.      */
                         "overflow",
                         "underflow",
                         "total loss of precision",
                         "partial loss of precision"};

int ncephes_mtherr(char *name, int code) {

    /* Display string passed by calling program,
     * which is supposed to be the name of the
     * function in which the error occurred:
     */
    printf("\n%s ", name);

    /* Set global error message word */
    merror = code;

    /* Display error message defined
     * by the code argument.
     */
    if ((code <= 0) || (code >= 7))
        code = 0;
    printf("%s error\n", ermsg[code]);

    /* Return to calling
     * program
     */
    return (0);
}
