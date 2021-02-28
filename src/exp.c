#include <Rinternals.h>
#include <R.h>
#include <R_ext/Rdynload.h>
#include <inttypes.h>
#include <stddef.h>
#include "fastmath.h"

vsf exp_ps(vsf x) {

	x = _mm_max_ps(x, _mm_set1_ps(-88.37f));
	x = _mm_min_ps(x, _mm_set1_ps(+88.38f));

	const vsf n = _mm_round_ps(_mm_set1_ps(LOG2EF) * x, _MM_FROUND_TO_NEAREST_INT);
	x -= n * _mm_set1_ps(0.693359375f - 2.12194440e-4f);

	const vsf z = (((((_mm_set1_ps(1.9875691500E-4f) * x
		+ _mm_set1_ps(1.3981999507E-3f)) * x
		+ _mm_set1_ps(8.3334519073E-3f)) * x
		+ _mm_set1_ps(4.1665795894E-2f)) * x
		+ _mm_set1_ps(1.6666665459E-1f)) * x
		+ _mm_set1_ps(5.0000001201E-1f)) * x * x
		+ x
		+ _mm_set1_ps(1.0f);

    vsi ps2i = (vsi) _mm_cvttps_epi32(n);
	ps2i += (vsi) _mm_set1_epi32(127);
	vsf nn = (vsf) _mm_slli_epi32((__m128i) ps2i, 23);

	return z * nn;
}

SEXP fv_exp(SEXP x) {

	if(TYPEOF(x) != EXTPTRSXP) error_return("invalid argument type");

	fvector* sfv = (fvector*) R_ExternalPtrAddr(x);

	fvector* res = fv_malloc(sfv->r_len);
	if(res == NULL) error_return("could not allocate results vector");

	for(size_t i = 0; i < sfv->x_len; i++) {
		res->x[i] = exp_ps(sfv->x[i]);
	}

	return fv_create(res);
}
