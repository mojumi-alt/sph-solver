#ifndef SPH_PARTICLE_SYSTEM
#define SPH_PARTICLE_SYSTEM

#include <cmath>
#include <core/Particle.hpp>
#include <vector>

namespace SPH
{
class ParticleSystem
{
  public:
    double stiffness = 0.1;
    double restDensity = 1000;
    double mu = 0.1;
    double sigma = 100;
    Vector2d gravity = Vector2d(0.0, 0.0);

    explicit ParticleSystem(std::vector<Particle> initialState,
                            Vector2d domainSize) noexcept;

    const std::vector<Particle> &getParticles() const noexcept;
    std::vector<Particle> &getParticles() noexcept;
    const Vector2d getDomainSize() const noexcept;
    void advance(const double dt) noexcept;

  private:
    Vector2d domainSize;
    std::vector<Particle> particles;

    void applyBoundaries(Particle &p) noexcept;
    void calculateForces() noexcept;
};
} // namespace SPH

#endif
