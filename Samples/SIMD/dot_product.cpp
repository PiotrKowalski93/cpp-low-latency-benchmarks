#include "dot_product.hpp"

#include <immintrin.h>
#include <iostream>

// Naive version - baseline for mesurement
float dot_product(const float* a, const float* b, std::size_t n)
{
    float sum = 0.0f;

    for (std::size_t i = 0; i < n; ++i) {
        sum += a[i] * b[i];
    }

    return sum;
}

float dot_product_noexcept(const float* a, const float* b, std::size_t n) noexcept
{
    float sum = 0.0f;

    for (std::size_t i = 0; i < n; ++i) {
        sum += a[i] * b[i];
    }

    return sum;
}

// Will it be faster done by hand?
float dot_product_loop_unrolled(const float* a, const float* b, std::size_t n) noexcept
{
    float sum = 0.0f;

    std::size_t i = 0;

    for (; i + 3 < n; i += 4) {
        sum += a[i]     * b[i];
        sum += a[i + 1] * b[i + 1];
        sum += a[i + 2] * b[i + 2];
        sum += a[i + 3] * b[i + 3];
    }

    for (; i < n; ++i) {
        sum += a[i] * b[i];
    }

    return sum;
}

float dot_product_loop_unrolled_sum_divided(const float* a, const float* b, std::size_t n) noexcept
{
    float sum0 = 0.0f;
    float sum1 = 0.0f;
    float sum2 = 0.0f;
    float sum3 = 0.0f;

    std::size_t i = 0;

    for (; i + 3 < n; i += 4) {
        sum0 += a[i]     * b[i];
        sum1 += a[i + 1] * b[i + 1];
        sum2 += a[i + 2] * b[i + 2];
        sum3 += a[i + 3] * b[i + 3];
    }

    float sum = sum0 + sum1 + sum2 + sum3;

    for (; i < n; ++i) {
        sum += a[i] * b[i];
    }

    return sum;
}

float dot_product_avx2(const float* a, const float* b, std::size_t n) noexcept
{
    __m256 sum = _mm256_setzero_ps();

    std::size_t i = 0;

    for (; i + 8 <= n; i += 8) {
        __m256 va = _mm256_loadu_ps(a + i);
        __m256 vb = _mm256_loadu_ps(b + i);

        sum = _mm256_add_ps(sum, _mm256_mul_ps(va, vb));
    }

    // Moves result to table 
    float result[8];
    _mm256_storeu_ps(result, sum);

    float total = 0.0f;

    // Compiler takes care of unrolling it
    // we need to sum product of simd
    for (int j = 0; j < 8; ++j) {
        total += result[j];
    }

    for (; i < n; ++i) {
        total += a[i] * b[i];
    }

    return total;
}
