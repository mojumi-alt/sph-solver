#ifndef SPH_PARTICLE
#define SPH_PARTICLE

#include <math/VectorNt.hpp>

namespace SPH
{
class Particle
{
  public:
    Vector2d location = Vector2d(0.0, 0.0);
    Vector2d velocity = Vector2d(0.0, 0.0);
    Vector2d acceleration = Vector2d(0.0, 0.0);
    double rho = 0, mass = 1, h = 0.3, pressure = 0;
    Vector2d pressureForce = Vector2d(0.0, 0.0);
    Vector2d viscosityForce = Vector2d(0.0, 0.0);
    Vector2d surfaceForce = Vector2d(0.0, 0.0);
    Vector2d surfaceNormal = Vector2d(0.0, 0.0);
    double kappa = 0;

    Particle(const Vector2d location) noexcept;
};
} // namespace SPH

#endif