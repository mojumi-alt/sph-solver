#include "Integrator.hpp"

namespace sph
{

inline float length(const sf::Vector2f &v)
{
    return std::sqrt(v.x * v.x + v.y * v.y);
}

inline sf::Vector2f vector_clip(sf::Vector2f vec, const float max)
{
    return {std::max(std::min(vec.x, max), -max),
            std::max(std::min(vec.y, max), -max)};
}

void integrate(ParticleSystem &ps, const float dt, const float vmax)
{
    ps.compute_acceleration();
    for (auto &pi : ps.get_particles())
    {
        pi.v += pi.a * (dt / 2.f);
        pi.v = vector_clip(pi.v, vmax);
        pi.s += pi.v * dt;
    }
}

} // namespace sph