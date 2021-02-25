#ifndef SPH_WINDOW_H
#define SPH_WINDOW_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <core/ParticleSystem.hpp>

namespace SPH
{
class Window
{
  public:
    double scale;
    explicit Window(ParticleSystem &ps, const double scale = 10) noexcept;

    void run() noexcept;

  private:
    std::vector<sf::CircleShape> circles;
    sf::VertexArray boundaries;
    ParticleSystem &ps;

    void update() noexcept;
};
} // namespace SPH

#endif