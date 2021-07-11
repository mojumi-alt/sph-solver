
#include <iostream>
#include <random>

#include "Inflow.hpp"
#include "Obstacle.hpp"
#include "Particle.hpp"
#include "ParticleSystem.hpp"
#include "Visualizer.hpp"

// int main()
// {
//     std::vector<sph::Particle> particles;
//     std::mt19937 mt;
//     std::uniform_real_distribution<float> dist(-1.0, 1.0);

//     float width = 10, height = 10, size = 0.3;

//     std::vector<sph::Obstacle> obstacles{
//     //    sph::Obstacle({0, 5}, {10, 5}),
//     };

//     for (float x = 3; x < 7; x += size - 0.01)
//         for (float y = 6; y < 10 - size; y += size - 0.01)
//             particles.push_back(sph::Particle{.s = {x, y}});

//     //for (float x = 3; x < 7; x += size - 0.01)
//     //    for (float y = 1; y < 5 - size; y += size - 0.01)
//     //        particles.push_back(sph::Particle{.s = {x, y}});

//     sph::ParticleSystem ps(particles, {width, height}, obstacles, size);

//     sph::Visualizer w(ps, 80);
//     w.run();
//     return 0;
// }

int main()
{
    float width = 10, height = 10, size = 0.25;

    std::vector<sph::Obstacle> obstacles{};

    float interval = 0.2;
    for (float f = 0.0; f < 10.0; f += interval)
    {
        auto funct = [](double pos_x) -> float {
            return 0.2 * (pos_x - 5) * (pos_x - 5);
        };
        obstacles.push_back(sph::Obstacle(
            {f, 10 - funct(f)}, {f + interval, 10 - funct(f + interval)}));
    }

    std::vector<sph::Inflow> inflows{
        sph::Inflow({4.0, 1.0, 2, 1}, 0.1, {0.0, 1.0})};

    inflows[0].end_time = 10;

    sph::ParticleSystem ps({}, {width, height}, obstacles, inflows, size);

    sph::Visualizer w(ps, 80);
    w.run();
}