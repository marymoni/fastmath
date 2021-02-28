#ifndef _FASTMATH_H_
#define _FASTMATH_H_

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>
#include <R_ext/Visibility.h>
#include <x86intrin.h>

typedef __v4sf vsf;
typedef __v4si vsi;
typedef __m128i vsl;

typedef struct {
	size_t r_len;
	size_t x_len;
	vsf x[];
} fvector;

#define VSF_LEN (sizeof(vsf) / sizeof(float))
#define VSI_LEN (sizeof(vsi) / sizeof(int))

SEXP cpu_info_get();
fvector* fv_malloc(size_t r_len);
size_t fv_size(size_t r_len);
SEXP fv_create(fvector* sfv);
void fv_destroy(SEXP fv_ptr);
SEXP fv_asfvector(SEXP x_data);
SEXP fv_asdouble(SEXP x);
SEXP fv_add(SEXP x, SEXP y);
SEXP fv_sub(SEXP x, SEXP y);
SEXP fv_mul(SEXP x, SEXP y);
SEXP fv_div(SEXP x, SEXP y);
SEXP fv_sqrt(SEXP x);
SEXP fv_slice(SEXP x, SEXP ind);
SEXP fv_exp(SEXP x);
SEXP fv_log(SEXP x);

#define LOG2EF 1.44269504088896341f

#endif
