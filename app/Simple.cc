
#include <iostream>
#include <random>

#include "Obstacle.hpp"
#include "Particle.hpp"
#include "ParticleSystem.hpp"
#include "Visualizer.hpp"

int main()
{
    std::vector<sph::Particle> particles;
    std::mt19937 mt;
    std::uniform_real_distribution<float> dist(-1.0, 1.0);

    float width = 10, height = 10, size = 0.20;

    std::vector<sph::Obstacle> obstacles{
        sph::Obstacle({0, 5}, {10, 5}),
    };

    for (float x = 3; x < 7; x += size - 0.01)
        for (float y = 6; y < 10 - size; y += size - 0.01)
            particles.push_back(sph::Particle{.s = {x, y}});

    for (float x = 3; x < 7; x += size - 0.01)
        for (float y = 1; y < 5 - size; y += size - 0.01)
            particles.push_back(sph::Particle{.s = {x, y}});

    sph::ParticleSystem ps(particles, {width, height}, obstacles, size);

    sph::Visualizer w(ps, 80);
    w.run();
    return 0;
}