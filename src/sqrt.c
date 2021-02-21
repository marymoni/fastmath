#include <Rinternals.h>
#include <R.h>
#include <R_ext/Rdynload.h>
#include <inttypes.h>
#include <stddef.h>
#include "fastmath.h"

SEXP fv_sqrt(SEXP x) {

	if(TYPEOF(x) != EXTPTRSXP) error_return("invalid argument type");

	fvector* fv_x = (fvector*) R_ExternalPtrAddr(x);

	fvector* res = fv_malloc(fv_x->r_len);
	if(res == NULL) error_return("could not allocate results vector");

	for(size_t i = 0; i < fv_x->x_len; i++) {
		res->x[i] = _mm_sqrt_ps(fv_x->x[i]);
	}

	return  fv_create(res);
}
