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

### TEST 2: ???