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
    const size_t N = 1'000'000;
    //const size_t N = 100;
    std::vector<uint64_t> latencies_;
    latencies_.reserve(N);
    
    int prev_cpu = sched_getcpu();
    size_t migrations = 0;

    timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 1000; // 1 µs

    auto worker = [&]() {

        for(size_t i = 0; i < N; i++)
        {
            auto start = rdtsc();

            // Work simulation
            for(int j = 0; j < 200; j++)
            {
                asm volatile("");
            }
            nanosleep(&ts, nullptr);

            auto end = rdtsc();

            latencies_.push_back(end - start);

            int cpu = sched_getcpu();
            if(cpu != prev_cpu)
            {
                migrations++;
                prev_cpu = cpu;
            }
        }
    };

    // Test 1) Without pinning
    std::cout << "Test 1) Unpinned" << std::endl;
    auto t = Common::createAndStartThread(-1 /*scheduler migration, -1 == do not pin*/, "latency_worker", worker);
    t->join();

    std::cout << "CPU migrations: " << migrations << std::endl;
    Common::save_latencies(latencies_, "cpu_work_unpinned.bin");

    // Clear metrics
    latencies_.clear();
    prev_cpu = sched_getcpu();
    migrations = 0;

    // Test 2) With pinning
    std::cout << "Test 2) Pinned" << std::endl;
    auto t2 = Common::createAndStartThread(2, "latency_worker_2", worker);
    t2->join();

    std::cout << "CPU migrations: " << migrations << std::endl;
    Common::save_latencies(latencies_, "cpu_work_pinned.bin");
}