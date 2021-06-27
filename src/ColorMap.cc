#include "ColorMap.hpp"

#include <SFML/System/Vector3.hpp>
#include <stdexcept>

namespace sph
{

ColorMap::ColorMap(std::vector<sf::Color> colors, std::vector<uint8_t> offsets)
{
    if (colors.size() != offsets.size())
        throw std::invalid_argument("Number of colors != number of offsets!");

    if (offsets.size() == 0)
        throw std::invalid_argument("Can not make empty color map!");

    if (offsets.back() != 255 or offsets.size() > 255)
        throw std::invalid_argument("Requested map does not cover 255 points!");

    if (offsets.size() == 1)
        for (auto &v : map)
            v = colors[0];

    for (size_t i = 0; i < offsets.size() - 1; ++i)
    {
        float x0 = offsets[i], x1 = offsets[i + 1];
        sf::Vector3f y0(colors[i].r, colors[i].g, colors[i].b),
            y1(colors[i + 1].r, colors[i + 1].g, colors[i + 1].b);

        sf::Vector3f m = (y1 - y0) / (x1 - x0);
        sf::Vector3f t = y0 - m * x0;

        for (size_t x = offsets[i]; x <= offsets[i + 1]; ++x)
        {
            sf::Vector3f current(m * (float)x + t);
            map[x] = sf::Color(current.x, current.y, current.z, 255);
        }
    }
}

} // namespace sph
