#include <visualizer/Window.hpp>

#include <random>

int main()
{
    std::vector<SPH::Particle> particles;
    std::mt19937 mt;
    std::uniform_real_distribution dist(-1.0, 1.0);

    double width = 10, height = 10;

    for (double x = 4; x < width - 4; x += 0.2)
        for (double y = 4; y < height - 4; y += 0.2)
            particles.push_back(SPH::Particle(SPH::Vector2d(x, y)));

    SPH::ParticleSystem ps(particles, SPH::Vector2d(width, height));

    SPH::Window w(ps, 80);
    w.run();

    return 0;
}