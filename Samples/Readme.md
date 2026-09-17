
### Benchmark for AVX2

```bash
Run on (4 X 2808 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 4096 KiB (x1)
Load Average: 0.08, 0.07, 0.12
---------------------------------------------------------------------------------------------------
Benchmark                                         Time             CPU   Iterations UserCounters...
---------------------------------------------------------------------------------------------------
BM_DotProduct/128                               103 ns          103 ns      6275843 items_per_second=1.23791G/s
BM_DotProduct/1024                             1255 ns         1255 ns       531858 items_per_second=815.819M/s
BM_DotProduct/4096                             5305 ns         5305 ns       122713 items_per_second=772.16M/s
BM_DotProduct/16384                           21187 ns        21187 ns        32724 items_per_second=773.306M/s
BM_DotProduct/65536                           84949 ns        84947 ns         8133 items_per_second=771.489M/s
---------------------------------------------------------------------------------------------------
BM_DotProduct_LoopUnrolled/128                  110 ns          110 ns      6486887 items_per_second=1.16032G/s
BM_DotProduct_LoopUnrolled/1024                1276 ns         1276 ns       567415 items_per_second=802.807M/s
BM_DotProduct_LoopUnrolled/4096                5191 ns         5191 ns       127051 items_per_second=789.012M/s
BM_DotProduct_LoopUnrolled/16384              21063 ns        21061 ns        32225 items_per_second=777.941M/s
BM_DotProduct_LoopUnrolled/65536              82938 ns        82936 ns         7580 items_per_second=790.201M/s
---------------------------------------------------------------------------------------------------
BM_DotProduct_LoopUnrolled_Sum_Div/128          102 ns          102 ns      6682692 items_per_second=1.25545G/s
BM_DotProduct_LoopUnrolled_Sum_Div/1024        1257 ns         1257 ns       559252 items_per_second=814.647M/s
BM_DotProduct_LoopUnrolled_Sum_Div/4096        5274 ns         5274 ns       135053 items_per_second=776.696M/s
BM_DotProduct_LoopUnrolled_Sum_Div/16384      20450 ns        20449 ns        33445 items_per_second=801.202M/s
BM_DotProduct_LoopUnrolled_Sum_Div/65536      84979 ns        84977 ns         8202 items_per_second=771.222M/s
---------------------------------------------------------------------------------------------------
BM_DotProduct_AVX2/128                         15.7 ns         15.7 ns     44004234 items_per_second=8.152G/s
BM_DotProduct_AVX2/1024                         143 ns          143 ns      4942365 items_per_second=7.15091G/s
BM_DotProduct_AVX2/4096                         636 ns          636 ns      1064571 items_per_second=6.44106G/s
BM_DotProduct_AVX2/16384                       2666 ns         2666 ns       270999 items_per_second=6.14659G/s
BM_DotProduct_AVX2/65536                      10531 ns        10530 ns        56435 items_per_second=6.22345G/s
```

```bash
Running ./build/dot_product_benchmark
Run on (4 X 2808 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 4096 KiB (x1)
Load Average: 0.41, 0.21, 0.13
----------------------------------------------------------------------------------------------------
Benchmark                                          Time             CPU   Iterations UserCounters...
----------------------------------------------------------------------------------------------------
BM_DotProduct/128                               99.9 ns         99.9 ns      6145510 items_per_second=1.28083G/s
BM_DotProduct/1024                              1277 ns         1275 ns       568997 items_per_second=803.008M/s
BM_DotProduct/4096                              5113 ns         5112 ns       137977 items_per_second=801.209M/s
BM_DotProduct/16384                            20642 ns        20641 ns        35204 items_per_second=793.747M/s
BM_DotProduct/65536                            85208 ns        85197 ns         7687 items_per_second=769.228M/s
----------------------------------------------------------------------------------------------------
BM_DotProduct_AVX2/128                          15.0 ns         15.0 ns     42897624 items_per_second=8.53254G/s
BM_DotProduct_AVX2/1024                          144 ns          144 ns      4934724 items_per_second=7.11112G/s
BM_DotProduct_AVX2/4096                          610 ns          610 ns      1091477 items_per_second=6.71435G/s
BM_DotProduct_AVX2/16384                        2566 ns         2566 ns       247221 items_per_second=6.38495G/s
BM_DotProduct_AVX2/65536                       10211 ns        10210 ns        62474 items_per_second=6.41871G/s
----------------------------------------------------------------------------------------------------
BM_DotProduct_AVX2_One_Accumulator/128          14.0 ns         14.0 ns     49588522 items_per_second=9.15702G/s
BM_DotProduct_AVX2_One_Accumulator/1024          140 ns          140 ns      4219926 items_per_second=7.29224G/s
BM_DotProduct_AVX2_One_Accumulator/4096          604 ns          604 ns      1131366 items_per_second=6.78519G/s
BM_DotProduct_AVX2_One_Accumulator/16384        2569 ns         2569 ns       263852 items_per_second=6.37852G/s
BM_DotProduct_AVX2_One_Accumulator/65536       10435 ns        10435 ns        69189 items_per_second=6.28063G/s
----------------------------------------------------------------------------------------------------
BM_DotProduct_AVX2_Four_Accumulator/128         7.44 ns         7.44 ns     92993350 items_per_second=17.1971G/s
BM_DotProduct_AVX2_Four_Accumulator/1024        62.9 ns         62.9 ns      9851260 items_per_second=16.2826G/s
BM_DotProduct_AVX2_Four_Accumulator/4096         255 ns          255 ns      2862512 items_per_second=16.075G/s
BM_DotProduct_AVX2_Four_Accumulator/16384       1535 ns         1535 ns       443063 items_per_second=10.6743G/s
BM_DotProduct_AVX2_Four_Accumulator/65536       8828 ns         8828 ns        75160 items_per_second=7.42364G/s
```

