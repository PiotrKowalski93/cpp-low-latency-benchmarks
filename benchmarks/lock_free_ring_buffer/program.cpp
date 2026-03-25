#include <chrono>
#include <vector>

#include "queue.h"

using namespace Queue;

int main() {
    
    size_t WARMUP_N_ = 10'000;
    size_t BENCHMARK_N_ = 200'000;

    std::vector<std::chrono::nanoseconds> latencies_;

    // ----------------------------------------
    // Run producer and consumer in different threads
    // pin them to CPU producer CPU(1) Consumer CPU(2)
    // Prodcer saves start_time, consumer saves end_time

    // Producer
    auto start = std::chrono::steady_clock::now();

    // Consumer
    auto end = std::chrono::steady_clock::now();
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    // Warmup

    // Benchmark

    

    // Print out:
    // CPUs GHz
    // min latency
    // avg latency
    // max latency
    // p50
    // p95
    // p99
    // throughput operation per second
    // total operations
    // failed writes

    return 0;
}