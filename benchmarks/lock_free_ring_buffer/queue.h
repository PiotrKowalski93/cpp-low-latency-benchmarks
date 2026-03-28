#include <cstdint>
#include <iostream>
#include <cstddef>
#include <vector>
#include <atomic>
#include <chrono>

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

    struct Message { // 16 b
        std::chrono::steady_clock::time_point start;    // 8B
        int data;                                       // 4B + 4B padding
    };

    //SPSC Lock Free Queue
    template<typename T>
    class LockFreeQueue {
        public:
            LockFreeQueue(size_t buffer_size){
                buffer_size_ = buffer_size;
                buffer_.reserve(buffer_size);
            }

            bool read(T& element) noexcept {
                size_t read_index = read_i.load(std::memory_order_relaxed);

                if(read_index == write_i.load(std::memory_order_acquire)){
                    return false;
                }

                element = buffer_[read_index];
                read_i.store((read_index + 1) % buffer_size_, std::memory_order_release);

                return true;
            }

            bool write(const T& element) noexcept {
                size_t write_index = write_i.load(std::memory_order_relaxed);
                size_t new_write_index = (write_index + 1) % buffer_size_;

                if(new_write_index == read_i.load(std::memory_order_acquire)){ // acquire <--- getting data
                    // can't save, we don't want to override
                    return false;
                }
                
                buffer_[write_index] = element;
                write_i.store(new_write_index, std::memory_order_release); // release <-- data is ready to use

                return true;
            }


            bool is_empty() noexcept {
                size_t read_index = read_i.load(std::memory_order_acquire);

                if(read_index == write_i.load(std::memory_order_acquire)){
                    return true;
                }
                return false;
            }

        private:
            // vector => Cache line friendly
            std::vector<T> buffer_;

            std::size_t buffer_size_;

            std::atomic<size_t> read_i{0};
            std::atomic<size_t> write_i{0};
    };
}