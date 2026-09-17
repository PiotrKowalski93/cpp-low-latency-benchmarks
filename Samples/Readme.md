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