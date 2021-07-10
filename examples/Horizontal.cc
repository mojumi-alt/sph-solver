#include "Obstacle.hpp"
#include "Particle.hpp"
#include "ParticleSystem.hpp"
#include "Visualizer.hpp"
#include "Inflow.hpp"

int main()
{
    std::vector<sph::Particle> particles;
    std::vector<sph::Obstacle> obstacles{
        sph::Obstacle({0, 3}, {8, 3}),
        sph::Obstacle({10, 6}, {2, 6}),
        sph::Obstacle({0, 9}, {8, 9}),
    };

    std::vector<sph::Inflow> inflows{
        sph::Inflow({0.1, 0.1, 2, 2}, 1.0, {0.0, 1.0})};

    float width = 10, height = 10, size = 0.25;


    sph::ParticleSystem ps(particles, {width, height}, obstacles, inflows, size);

    sph::Visualizer w(ps, 80);
    w.run();
}