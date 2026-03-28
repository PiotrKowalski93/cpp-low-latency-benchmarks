### Cache information

```
:~$ lscpu | grep "cache"

L1d cache:                               192 KiB (6 instances)
L1i cache:                               192 KiB (6 instances)
L2 cache:                                1.5 MiB (6 instances)
L3 cache:                                12 MiB (1 instance)
```



### Numa and CPU

```
:~$ numactl --hardware

available: 1 nodes (0)
node 0 cpus: 0 1 2 3 4 5 6 7 8 9 10 11
node 0 size: 15871 MB
node 0 free: 8724 MB
```

### RAM Info

```

```


### Test 1: Single thread micro benchmark

```
------------ Results -------------
Total processed:1000000
Failed write:0
Min Latency: 57ns
Avg Latency: 71ns
Max Latency: 15142ns

p50: 63ns
p90: 87ns
p99: 102ns
p999: 1181ns
```


### TEST 2: Producer & Consumer with CPU Affinity

What was done:

1. Producer Pinned to CPU 2
2. Consumer Pinned to CPU 3
3. I used std::this_thread::yield(); in busy-waiting loops

```
------------ Results -------------
Total processed:1000000
Failed write:0
Min Latency: 308ns
Avg Latency: 7222098ns
Max Latency: 13654964ns

p50: 7'709'850ns
p90: 13'434'037ns
p99: 13'623'069ns
p999: 13'653'354ns
```

### TEST 3: CPU Affinity + Smaller size of a Queue

After checking L3 cache and running tests for different sizes:

```
run_two_threads_benchmark(1000);
run_two_threads_benchmark(4000);
run_two_threads_benchmark(16000);
run_two_threads_benchmark(64000);
run_two_threads_benchmark(256000);
run_two_threads_benchmark(1'000'000);
```

I see that CPU can transfer data between them on L3 cache.

