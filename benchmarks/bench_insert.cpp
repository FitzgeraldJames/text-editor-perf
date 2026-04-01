// benchmarks/bench_insert.cpp
#include <benchmark/benchmark.h>
#include "naive_array.h"

// Templated benchmark so you write it once per scenario
template <typename T>
static void BM_InsertAtBeginning(benchmark::State& state) {
    for (auto _ : state) {
        T editor;
        for (int i = 0; i < state.range(0); ++i) {
            editor.insert("hello ");
        }
    }
}

template <typename T>
static void BM_InsertAtEnd(benchmark::State& state) {
    for (auto _ : state) {
        T editor;
        for (int i = 0; i < state.range(0); ++i) {
            editor.insert("hello ");
        }
    }
}

// Register each implementation with a range of input sizes
BENCHMARK_TEMPLATE(BM_InsertAtBeginning, NaiveArray)->Range(64, 1<<14);

BENCHMARK_TEMPLATE(BM_InsertAtEnd, NaiveArray)->Range(64, 1<<14);
