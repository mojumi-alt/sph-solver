#include "Obstacle.hpp"
#include "Particle.hpp"
#include "ParticleSystem.hpp"
#include "Visualizer.hpp"

int main()
{
    std::vector<sph::Particle> particles;
    std::vector<sph::Obstacle> obstacles {
        sph::Obstacle({0, 5}, {10, 10}),
    };
    
    float width = 10, height = 10, size = 0.3;
    
    for (float x = size; x < 4; x += size - 0.01)
        for (float y = size; y < 5 - size; y += size - 0.01)
            particles.push_back(sph::Particle{.s = {x, y}});

    sph::ParticleSystem ps(particles, {width, height}, obstacles, {}, size);

    sph::Visualizer w(ps, 80);
    w.run();
}