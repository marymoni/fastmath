#include <Rinternals.h>
#include <R.h>
#include <R_ext/Rdynload.h>
#include <inttypes.h>
#include <stddef.h>
#include "fastmath.h"

vsf log_ps(vsf x) {

    vsf invalid_mask = _mm_cmple_ps(x, _mm_setzero_ps());

    x = _mm_max_ps(x, (vsf) _mm_set1_epi32(0x00800000));

    vsi e = (vsi) _mm_srli_epi32((vsl) x, 23);

    e -= (vsi) _mm_set1_epi32(126);

    x = _mm_and_ps(x, (vsf) (_mm_set1_epi32(~0x7f800000)));

    x = _mm_or_ps(x, _mm_set1_ps(0.5f));

    vsf mask = _mm_cmplt_ps(x, _mm_set1_ps(0.707106781186547524f));

    e += (vsi) mask;

    x += _mm_and_ps(x, mask);

    x -= _mm_set1_ps(1.0f);

    vsf xx = x*x;

    vsf y = (((((((( _mm_set1_ps(7.0376836292E-2f) * x
        + _mm_set1_ps(-1.1514610310E-1f)) * x
        + _mm_set1_ps(1.1676998740E-1f)) * x
        + _mm_set1_ps(-1.2420140846E-1f)) * x
        + _mm_set1_ps(1.4249322787E-1f)) * x
        + _mm_set1_ps(-1.6668057665E-1f)) * x
        + _mm_set1_ps(2.0000714765E-1f)) * x
        + _mm_set1_ps(-2.4999993993E-1f)) * x
        + _mm_set1_ps(3.3333331174E-1f)) * x * xx
        - _mm_set1_ps(0.5f) * xx;

    vsf exp = _mm_cvtepi32_ps((vsl) e);
    vsf mant = x;

    y = _mm_or_ps(y, invalid_mask);

    y += exp * _mm_set1_ps(-2.12194440e-4f);
    y += mant;
    y += exp * _mm_set1_ps(0.693359375f);

    return y;
}

SEXP fv_log(SEXP x) {

	if(TYPEOF(x) != EXTPTRSXP) error_return("invalid argument type");

	fvector* sfv = (fvector*) R_ExternalPtrAddr(x);

	fvector* res = fv_malloc(sfv->r_len);
	if(res == NULL) error_return("could not allocate results vector");

	for(size_t i = 0; i < sfv->x_len; i++) {
		res->x[i] = log_ps(sfv->x[i]);
	}

	return fv_create(res);
}
