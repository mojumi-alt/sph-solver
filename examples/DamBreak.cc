#include "Particle.hpp"
#include "ParticleSystem.hpp"
#include "Visualizer.hpp"

int main()
{
    std::vector<sph::Particle> particles;

    float width = 10, height = 10, size = 0.3;

    for (float x = size; x < width / 2; x += size - 0.01)
        for (float y = 6; y < width - size; y += size - 0.01)
            particles.push_back(sph::Particle{.s = {x, y}});

    sph::ParticleSystem ps(particles, {width, height}, {}, {}, size);

    sph::Visualizer w(ps, 80);
    w.run();
}