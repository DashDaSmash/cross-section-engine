#include "ParticleData.hpp"
#include "SearchEngine.hpp"
#include <iostream>
#include <chrono>
#include <cassert>

int main()
{
    constexpr std::size_t DATASET_SIZE = 1'000'000;
    constexpr double SEARCH_TARGET = 750'000.5;

    std::cout << " Dataset Size: " << DATASET_SIZE << " energy points\n";
    std::cout << " Target Energy: " << SEARCH_TARGET << " eV\n";

    // Populate ParticleData container in SoA layout
    ParticleData data;
    data.reserve(DATASET_SIZE);

    for (std::size_t i = 0; i < DATASET_SIZE; ++i)
    {
        double energy = static_cast<double>(i);
        double crossSection = static_cast<double>(i) * 0.05;
        data.addEntry(energy, crossSection);
    }

    // Obtain non-owning std::span read view
    std::span<const double> energies = data.energies();

    // Benchmark 1: Scalar Linear Search
    auto startLinear = std::chrono::high_resolution_clock::now();
    auto linearResult = SearchEngine::linearSearch(energies, SEARCH_TARGET);
    auto endLinear = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> linearDuration = endLinear - startLinear;

    // Benchmark 2: Binary Search (std::lower_bound)
    auto startBinary = std::chrono::high_resolution_clock::now();
    auto binaryResult = SearchEngine::binarySearch(energies, SEARCH_TARGET);
    auto endBinary = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> binaryDuration = endBinary - startBinary;

    // Benchmark 3: AVX2 SIMD Vector Search
    auto startSIMD = std::chrono::high_resolution_clock::now();
    auto simdResult = SearchEngine::simdSearch(energies, SEARCH_TARGET);
    auto endSIMD = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> simdDuration = endSIMD - startSIMD;

    // Correctness Verification
    std::cout << "Correctness Check\n";
    if (linearResult && binaryResult && simdResult)
    {
        std::cout << "Linear Search Index : " << *linearResult << "\n";
        std::cout << "Binary Search Index : " << *binaryResult << "\n";
        std::cout << "SIMD Search Index   : " << *simdResult << "\n\n";

        // Verify that all methods arrived at the same exact index
        assert(*linearResult == *binaryResult);
        assert(*linearResult == *simdResult);
        std::cout << "SUCCESS: All 3 algorithms returned identical search results!\n\n";
    }
    else
    {
        std::cout << "ERROR: Search failed to find target index across algorithms.\n\n";
        return 1;
    }

    // Performance Metrics Display
    std::cout << "Execution Timings\n";
    std::cout << "Scalar Linear Search : " << linearDuration.count() << " ms\n";
    std::cout << "AVX2 SIMD Search     : " << simdDuration.count() << " ms\n";
    std::cout << "Binary Search        : " << binaryDuration.count() << " ms\n\n";

    if (simdDuration.count() > 0.0)
    {
        double speedup = linearDuration.count() / simdDuration.count();
        std::cout << "AVX2 SIMD Speedup vs. Scalar Linear: " << speedup << "x\n";
    }

    return 0;
}