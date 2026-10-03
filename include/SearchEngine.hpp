#pragma once

#include <span>
#include <optional>
#include <cstddef>

class SearchEngine
{
public:
    SearchEngine() = delete;

    [[nodiscard]] static std::optional<std::size_t> linearSearch(std::span<const double> energies, double targetEnergy);

    [[nodiscard]] static std::optional<std::size_t> binarySearch(std::span<const double> energies, double targetEnergy);

    [[nodiscard]] static std::optional<std::size_t> simdSearch(std::span<const double> energies, double targetEnergy);
};