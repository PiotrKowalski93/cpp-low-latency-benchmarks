#include <chrono>
#include <vector>
#include <thread>
#include <algorithm>
#include <numeric>

#include "queue.h"
#include "thread_utils.h"

using namespace Queue;

// TODO: For Later measure cycles
// #include <x86intrin.h>
// uint64_t t = __rdtsc();

// TODO: Add CPU isolation, CPU pinning might not be enought
// TODO: Add Priority to the thread
// TODO: Add _mm_pause()?
int main() {
    
    size_t WARMUP_N_ = 10'000;
    size_t BENCHMARK_N_ = 200'000;
    
    bool production_finished_ = false;
    size_t failed_write_ = 0;
    size_t failed_read_ = 0;

    std::vector<std::chrono::nanoseconds> latencies_;
    latencies_.reserve(BENCHMARK_N_);
    
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
            messages_queue_.write(msg);

            // Write to buffer
            // if(!messages_queue_.write(msg)){
            //     failed_write_++;
            // }
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
                auto latency = end - msg.start;
                latencies_.push_back(latency);
            }
        }
    };

    // Warmup
    std::cout << "----------- Warmup ------------" << std::endl;
    auto producer_warmup = Common::createAndStartThread(3, "Consumer", consumer_func, true);
    auto consumer_warmup = Common::createAndStartThread(2, "Producer", producer_func, WARMUP_N_);

    producer_warmup->join();
    consumer_warmup->join();

    // Benchmark
    std::cout << "----------- Benchmark -----------" << std::endl;

    production_finished_ = false;
    latencies_.clear();

    auto producer_ = Common::createAndStartThread(3, "Consumer", consumer_func, false);
    auto consumer_ = Common::createAndStartThread(2, "Producer", producer_func, BENCHMARK_N_);

    producer_->join();
    consumer_->join();

    std::cout << "------------ Results -------------" << std::endl;

    sort(latencies_.begin(), latencies_.end());
    auto sum = std::reduce(latencies_.begin(), latencies_.end());
    auto avg_latency = sum / latencies_.size();

    std::cout << "Total processed:" << latencies_.size() << std::endl;
    std::cout << "Failed write:" << failed_write_ << std::endl;

    std::cout << "Min Latency: " << latencies_.front() << std::endl;
    std::cout << "Avg Latency: " << avg_latency << std::endl;
    std::cout << "Max Latency: " << latencies_.back() << std::endl;

    auto p50 = latencies_[BENCHMARK_N_ * 0.5];
    auto p90 = latencies_[BENCHMARK_N_ * 0.9];
    auto p99 = latencies_[BENCHMARK_N_ * 0.99];
    auto p999 = latencies_[BENCHMARK_N_ * 0.999];

    std::cout << std::endl;
    std::cout << "p50: " << p50 << std::endl;
    std::cout << "p90: " << p90 << std::endl;
    std::cout << "p99: " << p99 << std::endl;
    std::cout << "p999: " << p999 << std::endl;

    return 0;
}