# Cache-Aware High-Speed ENDF Cross-Section Search Engine

A high-performance C++20 application designed to explore low-level hardware optimizations, cache-conscious data layouts, and SIMD vectorization for searching nuclear cross-section data sets.

> **Note:** This is a step-by-step learning repository created to master single-node CPU optimization techniques, cache locality, and modern modern C++ memory views (`std::span`).

---

## Optimization Goals
- **Structure-of-Arrays (SoA) Layout:** Replaces traditional Array-of-Structures (AoS) to maximize L1 cache line efficiency and eliminate structure padding overhead.
- **Zero-Copy Views:** Uses C++20 `std::span` for non-owning access to contiguous memory buffers without dynamic allocation overhead.
- **SIMD Vectorization:** Leverages hardware vector instructions (AVX2 / `march=native`) for sequential search scanning.

---

## Directory Structure
```text
cross_section_engine/
├── CMakeLists.txt         # Cross-platform build configuration
├── include/
│   ├── ParticleData.hpp   # SoA data container class
│   └── SearchEngine.hpp   # Vectorized search algorithms
└── src/
    ├── SearchEngine.cpp   # Implementation of search routines
    └── main.cpp           # Driver application and benchmark suite