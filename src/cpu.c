#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>
#include <R_ext/Visibility.h>
#include <intrin.h>

SEXP cpu_info_get() {

    int cpudata[4];

    __cpuid(&cpudata, 1);

    SEXP r_cpudata = PROTECT(allocVector(INTSXP, 4));

    INTEGER(r_cpudata)[0] = cpudata[0];
    INTEGER(r_cpudata)[1] = cpudata[1];
    INTEGER(r_cpudata)[2] = cpudata[2];
    INTEGER(r_cpudata)[3] = cpudata[3];

    UNPROTECT(1);    
    return r_cpudata;   
}