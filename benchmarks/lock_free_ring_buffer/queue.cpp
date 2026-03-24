#include "queue.h"

namespace Queue{

    template<typename T>
    bool LockFreeQueue<T>::write(const T& element) noexcept {

        size_t write_index = write_i.load(std::memory_order_relaxed);
        size_t new_write_index = (write_index + 1) % 2;

        if(new_write_index == read_i.load(std::memory_order_acquire)){ // acquire <--- getting data
            // can't save, we don't want to override
            return false;
        }
        
        buffer_[write_index] = element;
        write_i.store(new_write_index, std::memory_order_release) // release <-- data is ready to use

        return true;
    }

    template<typename T>
    bool LockFreeQueue<T>::read(T& element) noexcept {
        size_t read_index = read_i.load(std::memory_order_relaxed);

        if(read_index == write_i.load(std::memory_order_acquire)){
            return false;
        }

        element = buffer_[read_index];
        read_i.store((read_index + 1) % 2, std::memory_order_release);
    }
}