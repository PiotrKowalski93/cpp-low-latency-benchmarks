#pragma once

#include <vector>
#include <stdint.h>
#include <iostream>
#include <fstream>

namespace Common{
    auto save_latencies(const std::vector<uint64_t>& latencies, const std::string& filename) -> void{
        std::ofstream out(filename, std::ios::binary);

        out.write(reinterpret_cast<const char*>(latencies.data()), latencies.size() * sizeof(uint64_t));
    }
}