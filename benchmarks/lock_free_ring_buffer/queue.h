#include <cstdint>
#include <iostream>
#include <cstddef>
#include <vector>
#include <atomic>

namespace Queue {
    enum class Side {
        INVALID = 0,
        SELL = 1,
        BUY = 2
    };

    //TODO: allign data for cache
    struct MarketDataMessage{
            uint32_t price_;
            uint64_t timestamp_;
            uint32_t symbol_id_;
            uint32_t quantity_;
            Side side_;
        };

    //SPSC Lock Free Queue
    template<typename T>
    class LockFreeQueue {
        public:

            LockFreeQueue(size_t buffer_size){
                buffer_.reserve(buffer_size);
            }

            bool read(T& element) noexcept;
            bool write(const T& element) noexcept;

        private:
            // vector => Cache line friendly
            std::vector<T> buffer_;

            std::atomic<size_t> read_i{0};
            std::atomic<size_t> write_i{0};
    };
}