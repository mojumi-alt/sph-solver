#include "CircleMap.hpp"

namespace sph::visualization
{

CircleMap::CircleMap(const size_t count, const float radius) noexcept
    : circles_(count)
{
    for (auto &circle : circles_)
    {
        circle.setOrigin(sf::Vector2f(radius, radius));
        circle.setRadius(radius);
    }
}

void CircleMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    for (auto &circle : circles_)
        target.draw(circle, states);
}

std::vector<sf::CircleShape> &CircleMap::get_circles() noexcept
{
    return circles_;
}

void CircleMap::set_color(const size_t i, sf::Color color) noexcept
{
    circles_[i].setFillColor(color);
}

void CircleMap::set_location(const size_t i, sf::Vector2f location) noexcept
{
    circles_[i].setPosition(location);
}

/**
 * @brief
 *
 */
void CircleMap::push(const float radius) noexcept
{
    sf::CircleShape circle;
    circle.setOrigin(sf::Vector2f(radius, radius));
    circle.setRadius(radius);
    circles_.push_back(circle);
}

} // namespace sph::visualization