#include "Inflow.hpp"
#include "Obstacle.hpp"
#include "Particle.hpp"
#include "ParticleSystem.hpp"
#include "Visualizer.hpp"


int main()
{
    float width = 10, height = 10, size = 0.2;

    std::vector<sph::Obstacle> obstacles{
        sph::Obstacle({3.7, 0.7}, {6.3, 0.7}),
        sph::Obstacle({3.7, 0.7}, {3.4, 3.0}),
        sph::Obstacle({6.3, 0.7}, {6.6, 3.0}),
    };

    std::vector<sph::Inflow> inflows{
        sph::Inflow({4.0, 1.0, 2, 1}, 0.1, {0.0, 1.0})};

    inflows[0].end_time = 50;

    sph::ParticleSystem ps({}, {width, height}, obstacles, inflows,
                           size);

    sph::Visualizer w(ps, 80);
    w.run();
}