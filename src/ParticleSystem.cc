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
                               sf::Vector2f domain_size,
                               std::vector<Obstacle> obstacles,
                               const float h) noexcept
    : h_(h), hash_(domain_size, h), domain_size_(domain_size),
      particles_(initial_state), obstacles_(obstacles)
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

    apply_obstacles_();

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
            int right = std::min(width, x + 2),
                bottom = std::min(height, y + 2);

            // Actually we only have to not consider all the top
            // left neighbours either.
            int left = x;

            // Compute interactions with neighbours.
            for (int i = y; i < bottom; ++i)
            {
                for (int j = left; j < right; ++j)
                {

                    // Get other search bucket.
                    auto &other_bucket = hash_.get_bucket(j, i);

                    // Do not consider empty buckets.
                    if (other_bucket.size() == 0)
                        continue;

                    // Finally compute new forces between contents
                    // of 2 buckets.
                    for (auto &pi : bucket)
                        for (auto &pj : other_bucket)
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

                            // Compute pressure force
                            auto f_pressure =
                                direction *
                                (pj->m * ((pi->P + pj->P) / (2 * pj->p)) *
                                 kernels::nabbla_poly6(l, h_));

                            // Compute viscosity force
                            auto f_viscosity =
                                direction *
                                (pj->m * (length(pi->v - pj->v) / pj->p) *
                                 kernels::laplace_poly6(l, h_)) *
                                mu;

                            // Compute surface normal.
                            auto surface_normal =
                                direction * (pj->m * (1 / pj->p) *
                                             kernels::nabbla_poly6(l, h_));

                            sf::Vector2f f_surface;
                            auto n = length(surface_normal);

                            // Check if actual surface.
                            if (n >= epsilon)
                            {

                                // Compute surface curvature.
                                auto kappa = (pj->m * (1 / pj->p) *
                                              kernels::laplace_poly6(l, h_));

                                // Compute surface force.
                                f_surface +=
                                    (surface_normal / n) * kappa * sigma;
                            }

                            // Compute total force.
                            auto f_total = f_pressure + f_viscosity + f_surface;
                            pi->f += f_total;

                            // For now we only avoid double computation for not
                            // identity buckets.
                            if (i != y or j != x)
                                pj->f -= f_total;
                        }
                }

                left = std::max(0, x - 1);
            }
        }
}

float ParticleSystem::get_particle_size() const noexcept { return h_; }

void ParticleSystem::apply_boundaries_(Particle &p) noexcept
{
    if (p.s.x > domain_size_.x - h_)
    {
        p.s.x = domain_size_.x - h_;
        p.v.x = -p.v.x * 0.5;
    }

    if (p.s.y > domain_size_.y - h_)
    {
        p.s.y = domain_size_.y - h_;
        p.v.y = -p.v.y * 0.5;
    }

    if (p.s.x < h_)
    {
        p.s.x = h_;
        p.v.x = -p.v.x * 0.5;
    }

    if (p.s.y < h_)
    {
        p.s.y = h_;
        p.v.y = -p.v.y * 0.5;
    }
}

void ParticleSystem::apply_obstacles_() noexcept
{
    for (auto &obstacle : obstacles_)
        for (auto &particle : particles_)
        {
            interactions++;
            auto distance = obstacle.distance(particle.s);

            if (distance >= h_)
                continue;

            auto len = length(particle.v);
            auto dir = particle.v / len;

            auto n = dir * (h_ - distance);
            particle.s -= n;
            particle.v = obstacle.bounce * obstacle.reflect(dir) * len;
        }
}

std::vector<Obstacle> &ParticleSystem::get_obstacles() noexcept
{
    return obstacles_;
}

} // namespace sph
