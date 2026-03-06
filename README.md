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