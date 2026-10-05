#include "SearchEngine.hpp"
#include <algorithm>
#include <iterator>
#include <immintrin.h>

#if defined(_MSC_VER)
#include <intrin.h>
#endif

static inline unsigned long countTrailingZeros(unsigned int mask)
{
#if defined(_MSC_VER)
    unsigned long index;
    _BitScanForward(&index, mask);
    return index;
#else
    return static_cast<unsigned long>(__builtin_ctz(mask));
#endif
}

std::optional<std::size_t> SearchEngine::linearSearch(std::span<const double> energies, double targetEnergy)
{
    if (energies.empty())
        return std::nullopt;

    for (std::size_t index = 0; index < energies.size(); index++)
    {
        if (energies[index] >= targetEnergy)
        {
            return index;
        }
    }
    return std::nullopt;
}

std::optional<std::size_t> SearchEngine::binarySearch(std::span<const double> energies, double targetEnergy)
{
    if (energies.empty())
        return std::nullopt;

    auto it = std::lower_bound(energies.begin(), energies.end(), targetEnergy);

    if (it == energies.end())
    {
        return std::nullopt;
    }

    return static_cast<std::size_t>(std::distance(energies.begin(), it));
}

std::optional<std::size_t> SearchEngine::simdSearch(std::span<const double> energies, double targetEnergy)
{
    if (energies.empty())
        return std::nullopt;

    const std::size_t size = energies.size();
    std::size_t index = 0;

    __m256d vecTarget = _mm256_set1_pd(targetEnergy);

    for (; index + 3 < size; index += 4)
    {
        __m256d vecData = _mm256_loadu_pd(&energies[index]);

        __m256d vecCmp = _mm256_cmp_pd(vecData, vecTarget, _CMP_GE_OQ);

        int mask = _mm256_movemask_pd(vecCmp);

        if (mask != 0)
        {
            unsigned long lane = countTrailingZeros(static_cast<unsigned int>(mask));
            return index + static_cast<std::size_t>(lane);
        }
    }

    for (; index < size; ++index)
    {
        if (energies[index] >= targetEnergy)
        {
            return index;
        }
    }

    return std::nullopt;
}