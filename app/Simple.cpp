#include <visualizer/Window.hpp>

#include <random>
#include <iostream>

#include <core/SpatialHash.hpp>

int main()
{
    std::vector<SPH::Particle> particles;
    std::mt19937 mt;
    std::uniform_real_distribution dist(-1.0, 1.0);

    double width = 10, height = 10;

    size_t current_id = 0;

    /*
    for (double x = 0; x < width; x += 0.3)
        for (double y = 8; y < height; y += 0.3)
            particles.push_back(
                SPH::Particle{.id = current_id++,
                              .location = SPH::Vector2d{x, y}});*/


    particles.push_back(
                SPH::Particle{.id = current_id++,
                              .location = SPH::Vector2d{0.1, 0.0}});

     particles.push_back(
                SPH::Particle{.id = current_id++,
                              .location = SPH::Vector2d{0.1, 0.1}});

    /*
    SPH::SpatialHash hash(10, 10, 20);

    hash.hash(particles);

    auto buckets = hash.get_adjacent_particles(particles[0]);

    std::cout << buckets.size() << "\n";
    std::cout << buckets[0][0][0]->id << "\n";

    exit(0); */

    SPH::ParticleSystem ps(particles, SPH::Vector2d(width, height));

    SPH::Window w(ps, 80);
    w.run();

    return 0;
}