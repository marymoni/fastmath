#include <Rinternals.h>
#include <R.h>
#include <R_ext/Rdynload.h>
#include <inttypes.h>
#include <stddef.h>
#include "fastmath.h"

SEXP fv_slice(SEXP x, SEXP ind) {

	if(TYPEOF(x) != EXTPTRSXP) error_return("invalid x argument type");
    if(TYPEOF(ind) != INTSXP) error_return("invalid ind argument type");

	fvector* fv_x = (fvector*) R_ExternalPtrAddr(x);

	fvector* res = fv_malloc(length(ind));
	if (!res) error_return("could not allocate results vector");

    float * res_x = (float *) res->x;
    const float * f_x = (float *) fv_x->x;

	for(size_t i = 0; i < length(ind); i++) {
        int pos = INTEGER(ind)[i] - 1;
        if (pos < 0) error_return("Negative or zero subscripts are not supported");
        if (pos > fv_x->r_len) error_return("Subscript out of bounds");
		res_x[i] = f_x[pos];
	}

	return fv_create(res);
}
