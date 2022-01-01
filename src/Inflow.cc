#include "Inflow.hpp"

#include <cmath>

namespace sph
{

Inflow::Inflow(std::tuple<float, float, float, float> volume,
               double rate) noexcept
    : volume_(volume), rate_(rate), x_distr_(-0.05, 0.05),
      y_distr_(std::get<1>(volume_),
               std::get<1>(volume_) + std::get<3>(volume_))
{
    current_x_ = std::get<0>(volume_);
    current_y_ = std::get<1>(volume_);
}

Inflow::Inflow(std::tuple<float, float, float, float> volume, double rate,
               sf::Vector2f initial_velocity) noexcept
    : volume_(volume), rate_(rate), initial_velocity_(initial_velocity),
      x_distr_(-0.05, 0.05),
      y_distr_(std::get<1>(volume_),
               std::get<1>(volume_) + std::get<3>(volume_))
{
    current_x_ = std::get<0>(volume_);
    current_y_ = std::get<1>(volume_);
}

void Inflow::advance(std::vector<Particle> &particles, const double dt) noexcept
{
    if (end_time > 0 and total_time >= end_time)
        return;

    if (total_time >= start_time)
    {

        size_t spawn_nmbr = std::floor(current_time_ / rate_);
        current_time_ -= rate_ * spawn_nmbr;

        for (size_t i = 0; i < spawn_nmbr; ++i)
        {

            particles.push_back(Particle{.s = {current_x_, current_y_},
                                         .v = initial_velocity_});
            current_x_ += offset_;

            if (current_x_ >= std::get<0>(volume_) + std::get<2>(volume_))
                current_x_ = std::get<0>(volume_) + x_distr_(engine_);
            current_y_ = y_distr_(engine_);
        }
        current_time_ += dt;
    }

    total_time += dt;
}

} // namespace sph