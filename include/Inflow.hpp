#pragma once

#include <SFML/System/Vector2.hpp>
#include <random>
#include <tuple>
#include <vector>

#include "Particle.hpp"

namespace sph
{
class Inflow
{
  public:
    double start_time = 0.0, end_time = -1.0;
    explicit Inflow(std::tuple<float, float, float, float> volume,
                    double rate) noexcept;
    explicit Inflow(std::tuple<float, float, float, float> volume, double rate,
                    sf::Vector2f initial_velocity) noexcept;

    void advance(std::vector<Particle> &particles, const double dt) noexcept;

  private:
    std::tuple<float, float, float, float> volume_;
    double current_time_, rate_, total_time;
    sf::Vector2f initial_velocity_;
    std::default_random_engine engine_;
    std::uniform_real_distribution<float> x_distr_, y_distr_;
    float current_x_, current_y_, offset_ = 0.2;
};
} // namespace sph