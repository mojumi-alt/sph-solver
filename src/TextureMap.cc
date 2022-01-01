#include "TextureMap.hpp"

#include <cstring>
#include <exception>
#include <iostream>

namespace sph::visualization
{

TextureMap::TextureMap(sf::Vector2u size)
    : size_(size)
{
    if (size_.x * size_.y == 0)
        throw std::invalid_argument("TextureMap must not have length 0!");

    constexpr size_t bpp = 4;
    texture_.create(size.x, size.y);
    raw_data_ = std::shared_ptr<sf::Uint8>(
        new sf::Uint8[size.x * size.y * bpp],
        std::default_delete<sf::Uint8>()
    );
    sprite_.setTexture(texture_);
    texture_.setSmooth(true);
}

void TextureMap::set_scale(const sf::Vector2f& factor) noexcept 
{
    sprite_.setScale(factor);    
}

void TextureMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite_, states);
}

void TextureMap::set_color(const size_t x, const size_t y,
                        sf::Color color) noexcept
{
    constexpr size_t bpp = 4;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    const auto color_int = _byteswap_ulong(color.toInteger());
#else
    const auto color_int = __builtin_bswap32(color.toInteger());
#endif

    std::memcpy(&raw_data_.get()[(x * bpp) + (y * size_.x * bpp)],
        &color_int,
        sizeof(color_int)
    );
}

sf::Vector2u TextureMap::get_size() const noexcept { return size_; }

void TextureMap::update() noexcept
{
    texture_.update(raw_data_.get());
}

} // namespace sph::visualization