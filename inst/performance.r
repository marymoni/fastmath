library(fastmath)
library(microbenchmark)

v_regular = rnorm(1e6)
v_fast = as.fvector(v_regular)

microbenchmark(
    exp(v_regular),
    exp(v_fast),
    times = 10
)
