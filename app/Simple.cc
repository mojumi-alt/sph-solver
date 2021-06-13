
#include <iostream>
#include <random>

#include "Particle.hpp"
#include "ParticleSystem.hpp"
#include "Visualizer.hpp"

int main()
{
    std::vector<sph::Particle> particles;
    std::mt19937 mt;
    std::uniform_real_distribution<float> dist(-1.0, 1.0);

    float width = 10, height = 10, size = 0.3;

    size_t current_id = 0;

    for (float x = size; x < width - size; x += size)
        for (float y = 8; y < height - size; y += size)
            particles.push_back(sph::Particle{.s = {x, y}});

    particles.push_back(sph::Particle{.s = {5.0, 1.0}});

    sph::ParticleSystem ps(particles, {width, height}, size);

    sph::Visualizer w(ps, 80);
    w.run();
    return 0;
}