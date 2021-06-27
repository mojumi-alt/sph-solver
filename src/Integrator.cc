#include "Integrator.hpp"

namespace sph
{

void integrate(ParticleSystem &ps, const float dt)
{
    ps.compute_acceleration();
    for (auto &pi : ps.get_particles())
    {
        pi.v += pi.a * (dt / 2.f);
        pi.s += pi.v * dt;
    }
}

} // namespace sph