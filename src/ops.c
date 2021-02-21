#include <Rinternals.h>
#include <R.h>
#include <R_ext/Rdynload.h>
#include <inttypes.h>
#include <stddef.h>
#include "fastmath.h"

SEXP fv_add(SEXP x, SEXP y) {

    if(TYPEOF(x) != EXTPTRSXP) error_return("invalid x argument type");
    if(TYPEOF(y) != EXTPTRSXP) error_return("invalid y argument type");

    fvector* fv_x = (fvector*) R_ExternalPtrAddr(x);
    fvector* fv_y = (fvector*) R_ExternalPtrAddr(y);

    fvector* res = fv_malloc(fv_x->r_len);
    if(!res) error_return("could not allocate results vector");

    for(size_t i = 0; i < fv_x->x_len; i++) {
        res->x[i] = fv_x->x[i] + fv_y->x[i];
    }

    return fv_create(res);
}

SEXP fv_sub(SEXP x, SEXP y) {

    if(TYPEOF(x) != EXTPTRSXP) error_return("invalid x argument type");
    if(TYPEOF(y) != EXTPTRSXP) error_return("invalid y argument type");

    fvector* fv_x = (fvector*) R_ExternalPtrAddr(x);
    fvector* fv_y = (fvector*) R_ExternalPtrAddr(y);

    fvector* res = fv_malloc(fv_x->r_len);
    if(!res) error_return("could not allocate results vector");

    for(size_t i = 0; i < fv_x->x_len; i++) {
        res->x[i] = fv_x->x[i] - fv_y->x[i];
    }

    return fv_create(res);
}

SEXP fv_mul(SEXP x, SEXP y) {

    if(TYPEOF(x) != EXTPTRSXP) error_return("invalid x argument type");
    if(TYPEOF(y) != EXTPTRSXP) error_return("invalid y argument type");

    fvector* fv_x = (fvector*) R_ExternalPtrAddr(x);
    fvector* fv_y = (fvector*) R_ExternalPtrAddr(y);

    fvector* res = fv_malloc(fv_x->r_len);
    if(!res) error_return("could not allocate results vector");

    for(size_t i = 0; i < fv_x->x_len; i++) {
        res->x[i] = fv_x->x[i] * fv_y->x[i];
    }

    return fv_create(res);
}

SEXP fv_div(SEXP x, SEXP y) {

    if(TYPEOF(x) != EXTPTRSXP) error_return("invalid x argument type");
    if(TYPEOF(y) != EXTPTRSXP) error_return("invalid y argument type");

    fvector* fv_x = (fvector*) R_ExternalPtrAddr(x);
    fvector* fv_y = (fvector*) R_ExternalPtrAddr(y);

    fvector* res = fv_malloc(fv_x->r_len);
    if(!res) error_return("could not allocate results vector");

    for(size_t i = 0; i < fv_x->x_len; i++) {
        res->x[i] = fv_x->x[i] / fv_y->x[i];
    }

    return fv_create(res);
}
