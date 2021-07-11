#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "ParticleSystem.hpp"

namespace sph
{

class Interaction
{

  public:
    explicit Interaction(ParticleSystem &ps);

    void interact(const sf::RenderWindow &window);
    void set_state(const sf::Event &event);

  private:
    bool is_active_ = false;
    ParticleSystem &ps_;
};

} // namespace sph