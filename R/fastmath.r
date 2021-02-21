#' @useDynLib fastmath, .registration = TRUE
NULL

.onLoad = function(libname, pkgname) {
    
    cpu_info = cpu_info_get()
    if (!cpu_info$sse4_1_support) stop("SSE 4.1 is not supported by CPU, fastmath package cannot be used")
}

#' @export
cpu_info_get = function() {

    cpu_data = .Call(R_cpu_info_get)
    
    list(
        sse_support = cpu_data[4] & bitwShiftL(1, 25),
        sse_2_support = cpu_data[4] & bitwShiftL(1, 26),
        sse_3_support = cpu_data[3] & 1,
        sse4_1_support = cpu_data[3] & bitwShiftL(1, 19),
        sse4_2_support = cpu_data[3] & bitwShiftL(1, 20)
    )
}
