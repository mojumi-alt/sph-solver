#include "visualizer/Colormap.hpp"
#include <iostream>
namespace SPH
{

struct Vec4
{
    double x, y, z, w;

    explicit Vec4(const sf::Color &c) : x(c.r), y(c.g), z(c.b), w(c.a) {}

    operator sf::Color() const { return sf::Color(x, y, z, w); }

    friend Vec4 operator/(Vec4 lhs, const double rhs)
    {
        lhs.x /= rhs;
        lhs.y /= rhs;
        lhs.z /= rhs;
        lhs.w /= rhs;
        return lhs;
    }

    friend Vec4 operator*(Vec4 lhs, const double rhs)
    {
        lhs.x *= rhs;
        lhs.y *= rhs;
        lhs.z *= rhs;
        lhs.w *= rhs;
        return lhs;
    }

    friend Vec4 operator-(Vec4 lhs, const Vec4 &rhs)
    {
        lhs.x -= rhs.x;
        lhs.y -= rhs.y;
        lhs.z -= rhs.z;
        lhs.w -= rhs.w;
        return lhs;
    }

    friend Vec4 operator+(Vec4 lhs, const Vec4 &rhs)
    {
        lhs.x += rhs.x;
        lhs.y += rhs.y;
        lhs.z += rhs.z;
        lhs.w += rhs.w;
        return lhs;
    }
};

sf::Color operator/(const sf::Color &lhs, const double rhs)
{
    return sf::Color(lhs.r / rhs, lhs.g / rhs, lhs.b / rhs, lhs.a / rhs);
}

sf::Color operator*(const sf::Color &lhs, const double rhs)
{
    return sf::Color(lhs.r * rhs, lhs.g * rhs, lhs.b * rhs, lhs.a * rhs);
}

std::array<sf::Color, 256>
Colormap::createColorRamp(std::initializer_list<sf::Color> colors,
                          std::initializer_list<int> offsets) const noexcept
{
    assert((colors.size() == offsets.size()));

    std::array<sf::Color, 256> ramp;

    for (unsigned int i = 0; i < offsets.size() - 1; ++i)
    {
        double x0 = *(offsets.begin() + i), x1 = *(offsets.begin() + i + 1);
        Vec4 y0 = Vec4(*(colors.begin() + i)),
             y1 = Vec4(*(colors.begin() + i + 1));

        Vec4 m = (y1 - y0) / (x1 - x0);
        Vec4 t = y0 - m * x0;

        for (unsigned int x = x0; x <= x1; ++x)
            ramp[x] = m * x + t;
    }

    return ramp;
}

Colormap::Colormap()
    : heat(createColorRamp({sf::Color(0, 20, 255), sf::Color(0, 128, 255),
                            sf::Color(0, 0, 0), sf::Color(255, 128, 0),
                            sf::Color(255, 20, 0)},
                           {0, 64, 128, 192, 255})),
      redBlue(createColorRamp({sf::Color(0, 0, 255), sf::Color(255, 255, 255),
                               sf::Color(255, 0, 0)},
                              {0, 128, 255})),
      rainbow(createColorRamp({sf::Color(255, 0, 255), sf::Color(0, 0, 255),
                               sf::Color(0, 255, 128), sf::Color(0, 255, 0),
                               sf::Color(255, 255, 0), sf::Color(255, 128, 0),
                               sf::Color(255, 0, 0)},
                              {0, 42, 84, 126, 168, 210, 255})),
      grayscale(createColorRamp({sf::Color(0, 0, 0), sf::Color(255, 255, 255)},
                                {0, 255})),
      viridian(createColorRamp({sf::Color(20, 0, 255), sf::Color(128, 0, 255),
                                sf::Color(0, 128, 200), sf::Color(32, 200, 64),
                                sf::Color(0, 255, 128), sf::Color(0, 255, 0)},
                               {0, 51, 102, 153, 204, 255})),
      plasma(createColorRamp({sf::Color(255, 0, 20), sf::Color(255, 0, 128),
                              sf::Color(200, 64, 128), sf::Color(128, 64, 200),
                              sf::Color(64, 128, 255), sf::Color(0, 255, 255)},
                             {0, 51, 102, 153, 204, 255}))
{
}

} // namespace EulerFluid
