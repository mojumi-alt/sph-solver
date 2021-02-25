#include "core/ParticleSystem.hpp"

#include <iostream>

namespace SPH
{
ParticleSystem::ParticleSystem(std::vector<Particle> initialState,
                               Vector2d domainSize) noexcept
    : domainSize(domainSize), particles(initialState)
{
}

const std::vector<Particle> &ParticleSystem::getParticles() const noexcept
{
    return particles;
}

std::vector<Particle> &ParticleSystem::getParticles() noexcept
{
    return particles;
}

const Vector2d ParticleSystem::getDomainSize() const noexcept
{
    return domainSize;
}

double wpoly6(const double r, const double h)
{
    return 315 / (64 * M_PI * std::pow(h, 9)) *
           (r <= h ? std::pow(h * h - r * r, 3) : 0);
}

double nabblaWpoly6(const double r, const double h)
{
    return 315 / (64 * M_PI * std::pow(h, 9)) *
           (r <= h ? std::pow(h * h - r * r, 2) * 6 * r : 0);
}

double laplaceWpoly6(const double r, const double h)
{
    auto k = h * h - r * r;
    return 315 / (64 * M_PI * std::pow(h, 9)) *
           (r <= h ? 6 * k * k + 24 * r * r * k : 0);
}

void ParticleSystem::advance(const double dt) noexcept
{
    calculateForces();
    for (auto &pi : particles)
    {
        pi.velocity += pi.acceleration * (dt / 2.0);
        pi.location += pi.velocity * dt;
    }

    calculateForces();
    for (auto &pi : particles)
    {
        pi.velocity += pi.acceleration * (dt / 2.0);
        applyBoundaries(pi);
    }
}

void ParticleSystem::applyBoundaries(Particle &p) noexcept
{
    if (p.location[0] > domainSize[0] - p.h)
    {
        p.location[0] = domainSize[0] - p.h;
        p.velocity[0] = -p.velocity[0] * 0.8;
        p.acceleration[0] = 0;
    }

    if (p.location[1] > domainSize[1] - p.h)
    {
        p.location[1] = domainSize[1] - p.h;
        p.velocity[1] = -p.velocity[1] * 0.8;
        p.acceleration[1] = 0;
    }

    if (p.location[0] < p.h)
    {
        p.location[0] = p.h;
        p.velocity[0] = -p.velocity[0] * 0.8;
        p.acceleration[0] = 0;
    }

    if (p.location[1] < p.h)
    {
        p.location[1] = p.h;
        p.velocity[1] = -p.velocity[1] * 0.8;
        p.acceleration[1] = 0;
    }
}

void ParticleSystem::calculateForces() noexcept
{
    for (auto &pi : particles)
    {
        pi.rho = 0;
        pi.pressureForce = Vector2d(0.0, 0.0);
        pi.viscosityForce = Vector2d(0.0, 0.0);
        pi.surfaceForce = Vector2d(0.0, 0.0);
        pi.kappa = 0;
        pi.surfaceNormal = Vector2d(0.0, 0.0);

        for (auto &pj : particles)
        {
            pi.rho += pj.mass * wpoly6(length(pj.location - pi.location), pi.h);
            pi.pressure = stiffness * (pi.rho - restDensity);
        }
    }

    for (auto &pi : particles)
    {
        for (auto &pj : particles)
        {
            auto direction = pj.location - pi.location;
            auto l = length(direction);
            if (l == 0)
                continue;
            direction /= l;

            pi.pressureForce +=
                direction *
                (pj.mass * ((pi.pressure + pj.pressure) / (2 * pj.rho)) *
                 nabblaWpoly6(l, pi.h));
            pi.viscosityForce +=
                direction *
                (pj.mass * (length(pi.velocity - pj.velocity) / pj.rho) *
                 laplaceWpoly6(l, pi.h));

            pi.surfaceNormal +=
                direction * (pj.mass * (1 / pj.rho) * nabblaWpoly6(l, pi.h));

            auto n = length(pi.surfaceNormal);
            if (n < 0.001)
                continue;

            pi.kappa = (pj.mass * (1 / pj.rho) * laplaceWpoly6(l, pi.h));
            pi.surfaceForce = (pi.surfaceNormal / n) * pi.kappa;
        }
        pi.pressureForce = -pi.pressureForce;
        pi.viscosityForce *= mu;
        pi.surfaceForce = -pi.surfaceForce * sigma;
    }

    for (auto &pi : particles)
    {
        pi.acceleration = Vector2d(0.0, 0.0);

        Vector2d forces =
            pi.pressureForce + pi.viscosityForce + pi.surfaceForce;
        pi.acceleration += forces / pi.rho;
    }
}
} // namespace SPH
