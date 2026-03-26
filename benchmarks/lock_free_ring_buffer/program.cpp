#include <chrono>
#include <vector>
#include <thread>

#include "queue.h"

using namespace Queue;

// TODO: For Later measure cycles
// #include <x86intrin.h>
// uint64_t t = __rdtsc();

int main() {
    
    size_t WARMUP_N_ = 10'000;
    size_t BENCHMARK_N_ = 200'000;
    bool production_finished_ = false;
    size_t failed_write_ = 0;
    size_t failed_read_ = 0;

    std::vector<std::chrono::nanoseconds> latencies_;
    
    Queue::LockFreeQueue<Queue::Message> messages_queue_(BENCHMARK_N_);

    // ----------------------------------------
    // Run producer and consumer in different threads
    // pin them to CPU producer CPU(1) Consumer CPU(2)
    // Prodcer saves start_time, consumer saves end_time

    bool is_warmup = true;

    // Producer
    auto producer_func = [&](size_t n){
        for(auto i = 0; i < n; ++i){
            // Create msg
            Message msg;
            msg.data = 1;
            msg.start = std::chrono::steady_clock::now();

            // Write to buffer
            if(!messages_queue_.write(msg)){
                failed_write_++;
            }
        }

        production_finished_ = true;
    };

    // Consumer
    auto consumer_func = [&](bool is_warmup){
        while (!production_finished_ || !messages_queue_.is_empty())
        {
            // Consume 
            Message msg;
            auto result = messages_queue_.read(msg);

            if(result){
                // Count latency and save it
                auto end = std::chrono::steady_clock::now();

                if(!is_warmup){
                    auto latency = end - msg.start;
                    latencies_.push_back(latency);
                }
            }
        }
    };

    // Warmup
    std::thread consumer_warmup(consumer_func, true);
    std::thread producer_warmup(producer_func, WARMUP_N_);

    producer_warmup.join();
    consumer_warmup.join();

    // Benchmark
    std::thread consumer_(consumer_func, false);
    std::thread producer_(producer_func, BENCHMARK_N_);

    producer_.join();
    producer_.join();
    
    std::cout << "Finished benchmark" << std::endl;
    std::cout << "Results:" << std::endl;

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