#pragma once

#include <vector>
#include <span>
#include <cstddef>

class ParticleData
{
private:
    std::vector<double> energies_;
    std::vector<double> crossSections_;

public:
    ParticleData() = default;
    ~ParticleData() = default;

    void reserve(std::size_t capacity)
    {
        energies_.reserve(capacity);
        crossSections_.reserve(capacity);
    }

    void addEntry(double energy, double crossSection)
    {
        energies_.push_back(energy);
        crossSections_.push_back(crossSection);
    }

    std::size_t size() const
    {
        return energies_.size();
    }

    std::span<const double> energies() const
    {
        return energies_;
    }

    std::span<const double> crossSections() const
    {
        return crossSections_;
    }
};
