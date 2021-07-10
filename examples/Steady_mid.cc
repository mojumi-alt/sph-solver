#include "Particle.hpp"
#include "ParticleSystem.hpp"
#include "Visualizer.hpp"

int main()
{
    std::vector<sph::Particle> particles;
    
    float width = 10, height = 10, size = 0.2;
    
    for (float x = 3; x < 7; x += size - 0.01)
        for (float y = 6; y < 10 - size; y += size - 0.01)
            particles.push_back(sph::Particle{.s = {x, y}});

    sph::ParticleSystem ps(particles, {width, height}, {}, {}, size);

    sph::Visualizer w(ps, 80);
    w.run();
}