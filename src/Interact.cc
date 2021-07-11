#include "Interact.hpp"
#include "iostream"

namespace sph
{
inline float length(const sf::Vector2f &v)
{
    return std::sqrt(v.x * v.x + v.y * v.y);
}

Interaction::Interaction(ParticleSystem &ps) : ps_(ps) {}

void Interaction::interact(const sf::RenderWindow &window)
{
    if (is_active_)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {

            auto sf_location =
                window.mapPixelToCoords(sf::Mouse::getPosition(window));
            for (auto &pi : ps_.get_particles())
            {
                auto dir = pi.s - sf_location;
                auto len = length(dir);

                if (len == 0 or len > 1.0)
                    continue;

                pi.v = dir / len * 0.7f;
            }
        }
    }
}

void Interaction::set_state(const sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed)
        is_active_ = true;
    else if (event.type == sf::Event::MouseButtonReleased)
        is_active_ = false;
}
} // namespace sph