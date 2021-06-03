#include "core/SpatialHash.hpp"

#include <iostream>

namespace SPH
{
    SpatialHash::SpatialHash(const double width, const double height,
                             const size_t segments_x, const size_t segments_y)
        : map_(segments_x * segments_y),
          width_(width), height_(height), segments_x_(segments_x), segments_y_(segments_y)
    {
    }

    void SpatialHash::hash(const std::vector<Particle> &particles) noexcept
    {
        // map_[0].push_back(&particles[0]);
        // std::cout << map_.size() << "\n";
        search_map_.resize(particles.size());
        for (const auto &particle : particles)
        {
            int left = (particle.location[0] - particle.h) / width_ * segments_x_,
                top = (particle.location[1] - particle.h) / height_ * segments_y_;
            size_t right = (particle.location[0] + particle.h) / width_ * segments_x_ + 1,
                   bottom = (particle.location[1] + particle.h) / height_ * segments_y_ + 1;

            //std::cout << particle.id << " " << particle.location[0] << " " <<  (particle.location[0] + particle.h) / width_ * segments_x_ << "\n";
            //std::cout << segments_x_ << "\n";
            for (size_t x = std::max(0, left); x < std::min(segments_x_, right); ++x)
                for (size_t y = std::max(0, top); y < std::min(segments_y_, bottom); ++y)
                {
                    //std::cout << x << "  " << y << "\n";
                    bucket &target_bucket = map_[x + y * segments_x_];
                    target_bucket.push_back(&particle);
                    search_map_[particle.id].push_back(&target_bucket);
                }
        }
    }

    void SpatialHash::clear() noexcept
    {
        for (auto &bucket : map_)
            bucket.clear();

        search_map_.clear();
    }

    void clean_ids(std::vector<Particle> &particles) noexcept
    {
        for (size_t i = 0; i < particles.size(); ++i)
            particles[i].id = i;
    }

    const std::vector<const SpatialHash::bucket *> &
    SpatialHash::get_adjacent_particles(const Particle &particle)
    {
        return search_map_[particle.id];
    }

    const SpatialHash::bucket &SpatialHash::get_bucket(const size_t x, const size_t y)
    {
        return map_[x + y * segments_x_];
    }

}