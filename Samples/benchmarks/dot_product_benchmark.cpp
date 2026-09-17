#include <benchmark/benchmark.h>

#include "../SIMD/dot_product.hpp"

#include <random>
#include <vector>

static void BM_DotProduct(benchmark::State& state)
{
    const std::size_t n = state.range(0);

    std::vector<float> a(n);
    std::vector<float> b(n);

    std::mt19937 rng(12345);
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    for (std::size_t i = 0; i < n; ++i) {
        a[i] = dist(rng);
        b[i] = dist(rng);
    }

    for (auto _ : state) {
        float result = dot_product(a.data(), b.data(), n);

        // Zapobiega usunięciu obliczenia przez optymalizator.
        benchmark::DoNotOptimize(result);
    }

    state.SetItemsProcessed(
        static_cast<int64_t>(state.iterations()) *
        static_cast<int64_t>(n)
    );
}

static void BM_DotProduct_Noexcept(benchmark::State& state)
{
    const std::size_t n = state.range(0);

    std::vector<float> a(n);
    std::vector<float> b(n);

    std::mt19937 rng(12345);
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    for (std::size_t i = 0; i < n; ++i) {
        a[i] = dist(rng);
        b[i] = dist(rng);
    }

    for (auto _ : state) {
        float result = dot_product_noexcept(a.data(), b.data(), n);

        // Zapobiega usunięciu obliczenia przez optymalizator.
        benchmark::DoNotOptimize(result);
    }

    state.SetItemsProcessed(
        static_cast<int64_t>(state.iterations()) *
        static_cast<int64_t>(n)
    );
}

static void BM_DotProduct_LoopUnrolled(benchmark::State& state)
{
    const std::size_t n = state.range(0);

    std::vector<float> a(n);
    std::vector<float> b(n);

    std::mt19937 rng(12345);
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    for (std::size_t i = 0; i < n; ++i) {
        a[i] = dist(rng);
        b[i] = dist(rng);
    }

    for (auto _ : state) {
        float result = dot_product_loop_unrolled(a.data(), b.data(), n);

        benchmark::DoNotOptimize(result);
    }

    state.SetItemsProcessed(
        static_cast<int64_t>(state.iterations()) *
        static_cast<int64_t>(n)
    );
}

static void BM_DotProduct_LoopUnrolled_Sum_Div(benchmark::State& state)
{
    const std::size_t n = state.range(0);

    std::vector<float> a(n);
    std::vector<float> b(n);

    std::mt19937 rng(12345);
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    for (std::size_t i = 0; i < n; ++i) {
        a[i] = dist(rng);
        b[i] = dist(rng);
    }

    for (auto _ : state) {
        float result = dot_product_loop_unrolled(a.data(), b.data(), n);

        benchmark::DoNotOptimize(result);
    }

    state.SetItemsProcessed(
        static_cast<int64_t>(state.iterations()) *
        static_cast<int64_t>(n)
    );
}

static void BM_DotProduct_AVX2(benchmark::State& state)
{
    const std::size_t n = state.range(0);

    std::vector<float> a(n);
    std::vector<float> b(n);

    std::mt19937 rng(12345);
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    for (std::size_t i = 0; i < n; ++i) {
        a[i] = dist(rng);
        b[i] = dist(rng);
    }

    for (auto _ : state) {
        float result = dot_product_avx2(a.data(), b.data(), n);

        benchmark::DoNotOptimize(result);
    }

    state.SetItemsProcessed(
        static_cast<int64_t>(state.iterations()) *
        static_cast<int64_t>(n)
    );
}

BENCHMARK(BM_DotProduct)
    ->Arg(128)
    ->Arg(1024)
    ->Arg(4096)
    ->Arg(16384)
    ->Arg(65536);

BENCHMARK(BM_DotProduct_Noexcept)
    ->Arg(128)
    ->Arg(1024)
    ->Arg(4096)
    ->Arg(16384)
    ->Arg(65536);

BENCHMARK(BM_DotProduct_LoopUnrolled)
    ->Arg(128)
    ->Arg(1024)
    ->Arg(4096)
    ->Arg(16384)
    ->Arg(65536);

BENCHMARK(BM_DotProduct_LoopUnrolled_Sum_Div)
    ->Arg(128)
    ->Arg(1024)
    ->Arg(4096)
    ->Arg(16384)
    ->Arg(65536);

BENCHMARK(BM_DotProduct_AVX2)
    ->Arg(128)
    ->Arg(1024)
    ->Arg(4096)
    ->Arg(16384)
    ->Arg(65536);

BENCHMARK_MAIN();
