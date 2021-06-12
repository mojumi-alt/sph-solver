#pragma once

#include "Particle.hpp"
#include <SFML/System/Vector2.hpp>
#include <vector>

namespace sph
{
/**
 * @brief
 *
 */
class SpatialHash
{
  public:
    using bucket = std::vector<Particle *>;

    /**
     * @brief Construct a new Spatial Hash object
     *
     * @param domain_size
     * @param cell_size
     */
    explicit SpatialHash(sf::Vector2f domain_size, const float cell_size);

    /**
     * @brief
     *
     * @param particles
     */
    void hash(std::vector<Particle> &particles) noexcept;

    /**
     * @brief
     *
     */
    void clear() noexcept;

    /**
     * @brief Get the bucket object
     *
     * @param x
     * @param y
     * @return const bucket&
     */
    bucket &get_bucket(const size_t x, const size_t y) noexcept;

    /**
     * @brief Get the bucket object
     *
     * @param x
     * @param y
     * @return const bucket&
     */
    const bucket &get_bucket(const size_t x, const size_t y) const noexcept;

    /**
     * @brief Get the domain size object
     *
     * @return sf::Vector2f
     */
    sf::Vector2f get_domain_size() const noexcept;

    /**
     * @brief Get the segment size object
     *
     * @return sf::Vector2f
     */
    sf::Vector2i get_segment_size() const noexcept;

    /**
     * @brief Get the cell size object
     *
     * @return sf::Vector2f
     */
    float get_cell_size() const noexcept;

  private:
    float cell_size_;
    sf::Vector2i segments_;
    sf::Vector2f domain_size_;
    std::vector<bucket> map_;
};
} // namespace sph
