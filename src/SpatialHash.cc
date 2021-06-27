#include "SpatialHash.hpp"

#include <cmath>
#include <stdexcept>

namespace sph
{

SpatialHash::SpatialHash(sf::Vector2f domain_size, const float cell_size)
    : cell_size_(cell_size), segments_(std::ceil(domain_size.x / cell_size_),
                                       std::ceil(domain_size.y / cell_size_)),
      domain_size_(domain_size), map_(segments_.x * segments_.y)
{
    if (segments_.x <= 0 or segments_.y <= 0)
        throw std::invalid_argument("Invalid cell size!");
}

void SpatialHash::hash(std::vector<Particle> &particles) noexcept
{
    for (auto &particle : particles)
    {
        int x = particle.s.x / domain_size_.x * segments_.x,
            y = particle.s.y / domain_size_.y * segments_.y;

        if (x < 0 || y < 0 || x >= segments_.x || y >= segments_.y)
            continue;

        bucket &target_bucket = map_[x + y * segments_.x];
        target_bucket.push_back(&particle);
    }
}

void SpatialHash::clear() noexcept
{
    for (auto &bucket : map_)
        bucket.clear();
}

SpatialHash::bucket &SpatialHash::get_bucket(const size_t x,
                                             const size_t y) noexcept
{
    return map_[x + y * segments_.x];
}

const SpatialHash::bucket &
SpatialHash::get_bucket(const size_t x, const size_t y) const noexcept
{
    return map_[x + y * segments_.x];
}

sf::Vector2f SpatialHash::get_domain_size() const noexcept
{
    return domain_size_;
}

sf::Vector2i SpatialHash::get_segment_size() const noexcept
{
    return segments_;
}

float SpatialHash::get_cell_size() const noexcept { return cell_size_; }

} // namespace sph