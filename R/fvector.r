#' Converts Numeric Vector to FastMath Vector
#'
#' @export
as.fvector = function(x) {
    .Call(R_fv_asfvector, x)
}

#' Converts FastMath Vector to Numeric Vector
#'
#' @export
as.double.fvector = function(x) {
    .Call(R_fv_asdouble, x)
}

#' Print FastMath Vector Values
#'
#' @export
print.fvector = function(x) {
    print.default(as.double(x))
}

#' Slice FastMath Vector
#'
#' @export
`[.fvector` = function(x, i) {
    .Call(R_fv_slice, x, i)
}

#' Slice FastMath Vector
#'
#' @export
`[[.fvector` = function(x, i) {
    if (length(i) != 1) stop("")
    .Call(R_fv_slice, x, i)
}

#' Add Two FastMath Vectors
#'
#' @export
`+.fvector` = function(a, b) {
    .Call(R_fv_add, a, b)
}

#' Subtract Two FastMath Vectors
#'
#' @export
`-.fvector` = function(a, b) {
    .Call(R_fv_sub, a, b)
}

#' Multiply Two FastMath Vectors
#'
#' @export
`*.fvector` = function(a, b) {
    .Call(R_fv_mul, a, b)
}

#' Divide Two FastMath Vectors
#'
#' @export
`/.fvector` = function(a, b) {
    .Call(R_fv_div, a, b)
}

#' Exponent From FastMath Vector
#'
#' @export
exp.fvector = function(x) {
    .Call(R_fv_exp, x)
}

#' Natural Logarithm From FastMath Vector
#'
#' @export
log.fvector = function(x) {
    .Call(R_fv_log, x)
}

#' Square Root From FastMath Vector
#'
#' @export
sqrt.fvector = function(x) {
    .Call(R_fv_sqrt, x)
}
