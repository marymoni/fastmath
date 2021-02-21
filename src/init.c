#include <Rinternals.h>
#include <R.h>
#include <R_ext/Rdynload.h>
#include "fastmath.h"

R_CallMethodDef callMethods[] = {
    {"R_cpu_info_get", (DL_FUNC) &cpu_info_get, 0},
    {"R_fv_asfvector", (DL_FUNC) &fv_asfvector, 1},
    {"R_fv_asdouble", (DL_FUNC) &fv_asdouble, 1},
    {"R_fv_exp", (DL_FUNC) &fv_exp, 1},
    {"R_fv_sqrt", (DL_FUNC) &fv_sqrt, 1},
    {"R_fv_add", (DL_FUNC) &fv_add, 2},
    {"R_fv_sub", (DL_FUNC) &fv_sub, 2},
    {"R_fv_mul", (DL_FUNC) &fv_mul, 2},
    {"R_fv_div", (DL_FUNC) &fv_div, 2},
    {"R_fv_slice", (DL_FUNC) &fv_slice, 2},
    {NULL, NULL, 0}
};

void R_init_fastmath(DllInfo *info) {

    R_registerRoutines(info, NULL, callMethods, NULL, NULL);
    R_useDynamicSymbols(info, FALSE);
}
