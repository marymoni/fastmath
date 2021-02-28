library(fastmath)
library(testthat)

a = c(1, 2, 3)
b = c(4, 5, 6)

fa = as.fvector(a)
fb = as.fvector(b)

expect_equal(as.double(fa + fb), a + b, tolerance = 1e-7)

expect_equal(as.double(fa - fb), a - b, tolerance = 1e-7)

expect_equal(as.double(fa * fb), a * b, tolerance = 1e-7)

expect_equal(as.double(fa / fb), a / b, tolerance = 1e-7)

expect_equal(as.double(sqrt(fa)), sqrt(a), tolerance = 1e-7)

expect_equal(as.double(exp(fa)), exp(a), tolerance = 1e-7)

expect_equal(as.double(log(fa)), log(a), tolerance = 1e-7)

