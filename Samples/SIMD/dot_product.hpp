#pragma once

#include <cstddef>

float dot_product(const float* a, const float* b, std::size_t n);
float dot_product_noexcept(const float* a, const float* b, std::size_t n) noexcept;
float dot_product_loop_unrolled(const float* a, const float* b, std::size_t n) noexcept;
float dot_product_loop_unrolled_sum_divided(const float* a, const float* b, std::size_t n) noexcept;
float dot_product_avx2(const float* a, const float* b, std::size_t n) noexcept;
float dot_product_avx2_fma_one_accumulator(const float* a, const float* b, std::size_t n) noexcept;
float dot_product_avx2_fma_four_accumulators(const float* a, const float* b, std::size_t n) noexcept;