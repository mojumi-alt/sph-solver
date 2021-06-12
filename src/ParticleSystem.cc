#include "ParticleSystem.hpp"
#include "Integrator.hpp"
#include "Kernels.hpp"

#include <algorithm>

namespace sph
{

inline float length(const sf::Vector2f &v)
{
    return std::sqrt(v.x * v.x + v.y * v.y);
}

ParticleSystem::ParticleSystem(std::vector<Particle> initial_state,
                               sf::Vector2f domain_size, const float h) noexcept
    : h_(h), hash_(domain_size, h), domain_size_(domain_size),
      particles_(initial_state)
{
}

const std::vector<Particle> &ParticleSystem::get_particles() const noexcept
{
    return particles_;
}

std::vector<Particle> &ParticleSystem::get_particles() noexcept
{
    return particles_;
}

sf::Vector2f ParticleSystem::get_domain_size() const noexcept
{
    return domain_size_;
}

const SpatialHash &ParticleSystem::get_spatial_hash() const noexcept
{
    return hash_;
}

void ParticleSystem::advance(const float dt) noexcept
{
    interactions = 0;
    integrate(*this, dt);

    for (auto &particle : particles_)
        apply_boundaries_(particle);
}

void ParticleSystem::compute_acceleration() noexcept
{
    calculate_forces_();
    for (auto &pi : particles_)
        pi.a = gravity + (pi.f / pi.p);
}

void ParticleSystem::calculate_forces_() noexcept
{
    hash_.clear();
    hash_.hash(particles_);

    for (auto &pi : particles_)
    {
        // Reset force and density.
        pi.p = 0;
        pi.f = sf::Vector2f(0, 0);

        for (auto &pj : particles_)
        {
            // Compute local density.
            pi.p += pj.m * kernels::poly6(length(pj.s - pi.s), h_);
        }

        // Compute pressure from density.
        pi.P = k * (pi.p - p_rest);
    }

    // Get spatial hash dimensions
    const auto [width, height] = hash_.get_segment_size();

    // Iterate all buckets.
    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x)
        {

            // Get current bucket.
            auto &bucket = hash_.get_bucket(x, y);

            // Skip empty buckets.
            if (bucket.size() == 0)
                continue;

            // Cell size matches up with kernel radius, so we 
            // have to only consider direct neighbours.
            int top = std::max(0, y - 1), left = std::max(0, x - 1),
                right = std::min(width, x + 2),
                bottom = std::min(height, y + 2);

            // Compute interactions with neighbours.
            for (int i = top; i < bottom; ++i)
                for (int j = left; j < right; ++j)
                {

                    // Get other search bucket.
                    const auto &other_bucket = hash_.get_bucket(j, i);

                    // Finally compute new forces between contents 
                    // of 2 buckets.
                    for (auto &pi : bucket)
                        for (const auto &pj : other_bucket)
                        {
                            // Just for funnsies.
                            interactions++;

                            // Compute distance and direction between particles.
                            auto direction = pj->s - pi->s;
                            auto l = length(direction);

                            // Particles "identical" position.
                            if (l < epsilon)
                                continue;

                            // Normalize direction.
                            direction /= l;
                            interactions++;

                            // Compute pressure force
                            pi->f += direction *
                                     (pj->m * ((pi->P + pj->P) / (2 * pj->p)) *
                                      kernels::nabbla_poly6(l, h_));

                            // Compute viscosity force
                            pi->f += direction *
                                     (pj->m * (length(pi->v - pj->v) / pj->p) *
                                      kernels::laplace_poly6(l, h_)) *
                                     mu;

                            // Compute surface normal.
                            auto surface_normal =
                                direction * (pj->m * (1 / pj->p) *
                                             kernels::nabbla_poly6(l, h_));
                            auto n = length(surface_normal);

                            // Check if actual surface.
                            if (n < epsilon)
                                continue;

                            // Compute surface curvature.
                            auto kappa = (pj->m * (1 / pj->p) *
                                          kernels::laplace_poly6(l, h_));

                            // Compute surface force.
                            pi->f += (surface_normal / n) * kappa * sigma;
                        }
                }
        }
}

float ParticleSystem::get_particle_size() const noexcept { return h_; }

void ParticleSystem::apply_boundaries_(Particle &p) noexcept
{
    if (p.s.x > domain_size_.x - h_)
    {
        p.s.x = domain_size_.x - h_;
        p.v.x = -p.v.x * 0.0;
        p.a.x = 0;
    }

    if (p.s.y > domain_size_.y - h_)
    {
        p.s.y = domain_size_.y - h_;
        p.v.y = -p.v.y * 0.1;
        p.a.y = 0;
    }

    if (p.s.x < h_)
    {
        p.s.x = h_;
        p.v.x = -p.v.x * 0.0;
        p.a.x = 0;
    }

    if (p.s.y < h_)
    {
        p.s.y = h_;
        p.v.y = -p.v.y * 0.1;
        p.a.y = 0;
    }
}

} // namespace sph
