#include <Rinternals.h>
#include <R.h>
#include <R_ext/Rdynload.h>
#include <inttypes.h>
#include <stddef.h>
#include "fastmath.h"

SEXP fv_slice(SEXP x, SEXP ind) {

	if(TYPEOF(x) != EXTPTRSXP) error_return("invalid x argument type");

	fvector* fv_x = (fvector*) R_ExternalPtrAddr(x);

	fvector* res = fv_malloc(length(ind));
	if (res == NULL) error_return("could not allocate results vector");

	for(size_t i = 0; i < length(ind); i++) {
		res->x[i] = fv_x->x[i];
	}

	return fv_create(res);
}
