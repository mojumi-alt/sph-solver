#pragma once

#include <vector>
#include "core/Particle.hpp"

namespace SPH
{
    class SpatialHash
    {
    public:
        using bucket = std::vector<const Particle *>;

        explicit SpatialHash(const double width, const double height, const size_t segments_x, const size_t segments_y);
        void hash(const std::vector<Particle> &particles) noexcept;
        void clear() noexcept;
        void clean_ids(std::vector<Particle>& particles) noexcept;
        const std::vector<const bucket *> &get_adjacent_particles(const Particle &particle);
        const bucket& get_bucket(const size_t x, const size_t y);

    private:

        std::vector<bucket> map_;
        std::vector<std::vector<const bucket *>> search_map_;
        double width_, height_;
        size_t segments_x_, segments_y_;
    };
}
