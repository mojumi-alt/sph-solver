#pragma once

#include <SFML/System/Vector2.hpp>
#include <cstddef>

namespace sph
{
/**
 * @brief
 *
 */
struct Particle
{
    float p = 0, m = 1, P = 0;
    sf::Vector2f s, v, a, f;
};
} // namespace sph
