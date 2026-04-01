#include <benchmark/benchmark.h>

// Google Benchmark provides its own main(), but we define our own here so we
// can do any global setup/teardown (e.g. seeding RNG, logging, etc.) before
// the benchmark runner takes over.

int main(int argc, char** argv) {
    // Any global setup goes here
    // e.g. seed a global RNG, pre-generate test data, print build info, etc.

    ::benchmark::Initialize(&argc, argv);

    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) {
        return 1;
    }

    ::benchmark::RunSpecifiedBenchmarks();
    ::benchmark::Shutdown();

    return 0;
}