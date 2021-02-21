#include <Rinternals.h>
#include <R.h>
#include <R_ext/Rdynload.h>
#include <inttypes.h>
#include <stddef.h>
#include "fastmath.h"

size_t fv_size(size_t r_len) {

	size_t x_len = ((r_len + (VSF_LEN - 1)) & ~(VSF_LEN - 1)) / VSF_LEN;
	return sizeof(fvector) + sizeof(vsf) * x_len;
}

fvector* fv_malloc(size_t r_len) {

	fvector* sfv = (fvector*) malloc(fv_size(r_len) * sizeof(vsf));
	if (sfv == NULL) return(sfv);

	sfv->r_len = r_len;
	sfv->x_len = ((r_len + (VSF_LEN - 1)) & ~(VSF_LEN - 1)) / VSF_LEN;

	return(sfv);
}

void fv_free(fvector* sfv) {

	free(sfv);
}

SEXP fv_create(fvector* sfv) {

	SEXP res;
	PROTECT(res = R_MakeExternalPtr(sfv, R_NilValue, R_NilValue));
	R_RegisterCFinalizerEx(res, fv_destroy, 1);

	SEXP res_class;
	PROTECT(res_class = ScalarString(mkChar("fvector")));
	setAttrib(res, R_ClassSymbol, res_class);

	UNPROTECT(2);
	return(res);
}

void fv_destroy(SEXP sfv_ptr) {

	fvector* sfv = (fvector*) R_ExternalPtrAddr(sfv_ptr);
	if (sfv == NULL) {
		warning("fvector external pointer is null");
		return;
	}

	fv_free(sfv);
	R_ClearExternalPtr(sfv_ptr);
}

SEXP fv_asfvector(SEXP x_data) {

	SEXP data = PROTECT(coerceVector(x_data, REALSXP));

	fvector* res_ptr = fv_malloc(LENGTH(data));
	if (res_ptr == NULL) error_return("could not allocate memory for sfvector data buffer");

	float* res_float = (float*) res_ptr->x;

	for(size_t i = 0; i < res_ptr->r_len; i++) {
		res_float[i] = REAL(data)[i];
	}

	SEXP res = fv_create(res_ptr);

	UNPROTECT(1);
	return res;
}

SEXP fv_asdouble(SEXP x) {

	if(TYPEOF(x) != EXTPTRSXP) error_return("invalid argument type");

	fvector* sfv = (fvector*) R_ExternalPtrAddr(x);

	SEXP res = PROTECT(allocVector(REALSXP, sfv->r_len));

	const float* sfv_float = (const float*)sfv->x;

	for(size_t i = 0; i < sfv->r_len; i++) {
		REAL(res)[i] = sfv_float[i];
	}

	UNPROTECT(1);
	return res;
}
