#include <vector>
#include <x86intrin.h>
#include <iostream>

#include "thread_utils.h"
#include "file_utils.h"

inline uint64_t rdtsc() {
    return __rdtsc();
}

int main(){

    // Prepare vector for latencies
    const size_t N = 10'000'000;
    //const size_t N = 100;
    std::vector<uint64_t> latencies_;
    latencies_.reserve(N);
    
    auto worker = [&]() {

        for(size_t i = 0; i < N; i++)
        {
            auto start = rdtsc();

            volatile int x = 1;
            x = x * 4 + 2;

            auto end = rdtsc();

            //std::cout << i << ": " << end - start << std::endl;
            latencies_.push_back(end - start);
        }
    };

    // Test 1) Without pinning
    std::cout << "Test 1) Unpinned" << std::endl;
    auto t = Common::createAndStartThread(-1 /*scheduler migration, -1 == do not pin*/, "latency_worker", worker);
    t->join();
    
    Common::save_latencies(latencies_, "cpu_work_unpinned.bin");
    latencies_.clear();

    // Test 2) With pinning
    std::cout << "Test 2) Pinned" << std::endl;
    auto t2 = Common::createAndStartThread(2, "latency_worker_2", worker);
    t2->join();

    Common::save_latencies(latencies_, "cpu_work_pinned.bin");
}