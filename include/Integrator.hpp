#pragma once

#include "ParticleSystem.hpp"

namespace sph
{
void integrate(ParticleSystem &ps, const float dt, const float vmax);
}