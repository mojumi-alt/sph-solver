#pragma once

#include <SFML/Graphics/Color.hpp>
#include <array>
#include <cstdint>
#include <vector>

namespace sph
{
/**
 * @brief
 *
 */
class ColorMap
{
  public:
    std::array<sf::Color, 256> map;

    /**
     * @brief Construct a new ColorMap object
     *
     * @param colors
     * @param offsets
     */
    explicit ColorMap(std::vector<sf::Color> colors,
                      std::vector<uint8_t> offsets);
};

namespace color_maps
{
const ColorMap heat({sf::Color(0, 20, 255), sf::Color(0, 128, 255),
                     sf::Color(0, 0, 0), sf::Color(255, 128, 0),
                     sf::Color(255, 20, 0)},
                    {0, 64, 128, 192, 255});

const ColorMap red_blue({sf::Color(0, 0, 255), sf::Color(255, 255, 255),
                         sf::Color(255, 0, 0)},
                        {0, 128, 255});

const ColorMap rainbow({sf::Color(255, 0, 255), sf::Color(0, 0, 255),
                        sf::Color(0, 255, 128), sf::Color(0, 255, 0),
                        sf::Color(255, 255, 0), sf::Color(255, 128, 0),
                        sf::Color(255, 0, 0)},
                       {0, 42, 84, 126, 168, 210, 255});

const ColorMap rainbow_to_white({sf::Color(255, 0, 255), sf::Color(0, 0, 255),
                                 sf::Color(0, 255, 128), sf::Color(0, 255, 0),
                                 sf::Color(255, 255, 0), sf::Color(255, 128, 0),
                                 sf::Color(255, 0, 0),
                                 sf::Color(255, 255, 255)},
                                {0, 42, 84, 126, 168, 210, 245, 255});

const ColorMap white_to_rainbow({sf::Color(255, 255, 255),
                                 sf::Color(255, 0, 255), sf::Color(0, 0, 255),
                                 sf::Color(0, 255, 128), sf::Color(0, 255, 0),
                                 sf::Color(255, 255, 0), sf::Color(255, 128, 0),
                                 sf::Color(255, 0, 0)},
                                {0, 10, 42, 84, 126, 168, 210, 255});

const ColorMap grayscale({sf::Color(0, 0, 0), sf::Color(255, 255, 255)},
                         {0, 255});

const ColorMap viridian({sf::Color(20, 0, 255), sf::Color(128, 0, 255),
                         sf::Color(0, 128, 200), sf::Color(32, 200, 64),
                         sf::Color(0, 255, 128), sf::Color(0, 255, 0)},
                        {0, 51, 102, 153, 204, 255});

const ColorMap plasma({sf::Color(255, 0, 20), sf::Color(255, 0, 128),
                       sf::Color(200, 64, 128), sf::Color(128, 64, 200),
                       sf::Color(64, 128, 255), sf::Color(0, 255, 255)},
                      {0, 51, 102, 153, 204, 255});
} // namespace color_maps
} // namespace sph
