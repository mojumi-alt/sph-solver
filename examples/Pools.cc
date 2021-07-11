#include "Inflow.hpp"
#include "Obstacle.hpp"
#include "Particle.hpp"
#include "ParticleSystem.hpp"
#include "Visualizer.hpp"

int main()
{
    float width = 10, height = 10, size = 0.25;

    std::vector<sph::Obstacle> obstacles{
        sph::Obstacle({0.5, 0.5}, {5.0, 0.5}),
        sph::Obstacle({0.5, 0.5}, {0.5, 3.5}),
        sph::Obstacle({0.5, 3.5}, {5.0, 3.5}),
        sph::Obstacle({5.0, 3.5}, {5.0, 2.5}),
        sph::Obstacle({5.0, 0.5}, {5.0, 1.0}),

        sph::Obstacle({4.0, 7.0}, {10.0, 7.0}),
        sph::Obstacle({4.0, 7.0}, {4.0, 5.5}),
        sph::Obstacle({4.0, 3.5}, {4.0, 4.0}),
    };

    std::vector<sph::Inflow> inflows{
        sph::Inflow({1.0, 1.0, 2, 2}, 0.2, {0.0, 0.0})};

    inflows[0].end_time = 200;

    sph::ParticleSystem ps({}, {width, height}, obstacles, inflows, size);

    sph::Visualizer w(ps, 80);
    w.run();
}