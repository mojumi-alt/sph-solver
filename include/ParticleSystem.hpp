#pragma once

#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <vector>

#include "Particle.hpp"
#include "SpatialHash.hpp"

namespace sph
{
/**
 * @brief
 *
 */
class ParticleSystem
{
  public:
    size_t interactions = 0;
    float k = 0.5, p_rest = 1800, mu = 0.3, sigma = 0.5, epsilon = 0.00001;
    sf::Vector2f gravity{0, 0.3};

    /**
     * @brief Construct a new Particle System object
     *
     * @param initial_state
     * @param domain_size
     */
    explicit ParticleSystem(std::vector<Particle> initial_state,
                            sf::Vector2f domain_size,
                            const float h = 0.3) noexcept;

    /**
     * @brief Get the particles object
     *
     * @return const std::vector<Particle>&
     */
    const std::vector<Particle> &get_particles() const noexcept;

    /**
     * @brief Get the particles object
     *
     * @return std::vector<Particle>&
     */
    std::vector<Particle> &get_particles() noexcept;

    /**
     * @brief Get the domain size object
     *
     * @return sf::Vector2f
     */
    sf::Vector2f get_domain_size() const noexcept;

    /**
     * @brief Get the spatial hash object
     *
     * @return const SpatialHash&
     */
    const SpatialHash &get_spatial_hash() const noexcept;

    /**
     * @brief
     *
     * @param dt
     */
    void advance(const float dt) noexcept;

    /**
     * @brief
     *
     */
    void compute_acceleration() noexcept;

    /**
     * @brief Get the particle size object
     *
     * @return float
     */
    float get_particle_size() const noexcept;

  private:
    float h_;
    SpatialHash hash_;
    sf::Vector2f domain_size_;
    std::vector<Particle> particles_;

    /**
     * @brief
     *
     * @param p
     */
    void apply_boundaries_(Particle &p) noexcept;

    /**
     * @brief
     *
     */
    void calculate_forces_() noexcept;
};
} // namespace sph
