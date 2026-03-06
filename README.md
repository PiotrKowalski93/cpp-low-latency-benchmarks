# C++ Low Latency Benchmarks

Collection of microbenchmarks exploring performance
characteristics important in low latency trading systems.

Benchmarks include:

- CPU affinity and scheduler migration
- Hyperthreading interference
- Cache line false sharing

## Benchmarks

### CPU Affinity

Measures latency jitter caused by thread migration.

### Hyperthreading Interference

Measures latency impact when threads share the same
physical core vs separate cores.

### False Sharing

Demonstrates performance degradation caused by
cache line contention.

## CPU stress test

Resources data:
```
sudo gnome-system-monitor
```

Create stress for cpu
```
stress-ng --taskset 0,2-3 --cpu 3 --timeout 1m
// --taskset: pin to CPU
// --cpu: instances
// --timeout: stressing time 

stress-ng --cpu 8 --cpu-load 80 --timeout 1m
// --cpu-load: % of loading
```

