#ifndef SPH_WINDOW_H
#define SPH_WINDOW_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <core/ParticleSystem.hpp>
#include <visualizer/Colormap.hpp>

namespace SPH
{
class Window
{
  public:
    double scale;
    explicit Window(ParticleSystem &ps, const double scale = 10) noexcept;

    void run() noexcept;

  private:
    Colormap cmap;
    sf::Font font;
    sf::Text stats;
    std::vector<sf::CircleShape> circles;
    sf::VertexArray lines;
    sf::VertexArray boundaries;
    sf::VertexArray tiles;
    sf::VertexArray hash_lines;
    ParticleSystem &ps;

    void update() noexcept;
};
} // namespace SPH

#endif