#ifndef COLORMAP_H
#define COLORMAP_H

#include <SFML/Graphics/Color.hpp>
#include <array>
#include <cassert>
#include <initializer_list>

namespace SPH
{

class Colormap
{
  private:
    [[nodiscard]] std::array<sf::Color, 256>
    createColorRamp(std::initializer_list<sf::Color> colors,
                    std::initializer_list<int> offsets) const noexcept;

  public:
    const std::array<sf::Color, 256> heat;
    const std::array<sf::Color, 256> redBlue;
    const std::array<sf::Color, 256> rainbow;
    const std::array<sf::Color, 256> grayscale;
    const std::array<sf::Color, 256> viridian;
    const std::array<sf::Color, 256> plasma;

    explicit Colormap();
};

} // namespace EulerFluid

#endif