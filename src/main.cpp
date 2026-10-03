#include <ParticleData.hpp>

#include <iostream>
#include <span>

int main()
{
    ParticleData particleData;
    particleData.reserve(3);
    particleData.addEntry(1.0, 2.5);
    particleData.addEntry(2.0, 3.5);
    particleData.addEntry(3.0, 4.5);

    const std::span<const double> energies = particleData.energies();
    const std::span<const double> crossSections = particleData.crossSections();

    for (std::size_t index = 0; index < energies.size(); ++index)
    {
        std::cout << "Energy: " << energies[index]
                  << ", cross section: " << crossSections[index] << '\n';
    }

    return 0;
}
