#include "Kernels.hpp"

#include <cmath>

namespace sph::kernels
{

float poly6(const float r, const float h)
{
    return 315 / (64 * M_PI * std::pow(h, 9)) *
           (r <= h ? std::pow(h * h - r * r, 3) : 0);
}

float nabbla_poly6(const float r, const float h)
{
    return 315 / (64 * M_PI * std::pow(h, 9)) *
           (r <= h ? std::pow(h * h - r * r, 2) * 6 * r : 0);
}

float laplace_poly6(const float r, const float h)
{
    auto k = h * h - r * r;
    return 315 / (64 * M_PI * std::pow(h, 9)) *
           (r <= h ? 6 * k * k + 24 * r * r * k : 0);
}

} // namespace sph::kernels