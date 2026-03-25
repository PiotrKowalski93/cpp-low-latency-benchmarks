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

    struct MarketDataMessageV1{
        uint32_t price_;            // 4 byte
        uint64_t timestamp_send_;   // 8 byte
        Side side_;                 // 4 byte
        uint32_t symbol_id_;        // 4 byte
        uint32_t quantity_;         // 4 byte      
    };
    
    struct MarketDataMessageV2{
        uint64_t timestamp_send_;   // 8 byte
        uint32_t price_;            // 4 byte
        uint32_t symbol_id_;        // 4 byte
        uint32_t quantity_;         // 4 byte
        Side side_;                 // 4 byte
    };

    #pragma pack(push, 1)
    struct MarketDataMessagePacked{
        uint64_t timestamp_;    // 8 byte
        uint32_t price_;        // 4 byte
        uint32_t symbol_id_;    // 4 byte
        uint32_t quantity_;     // 4 byte
        Side side_;             // 4 byte
    };
    #pragma pack(pop)

    struct Message {
        std::chrono::steady_clock::time_point start;
        int data;
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