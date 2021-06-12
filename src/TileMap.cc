#include "TileMap.hpp"

#include <exception>

namespace sph::visualization
{

TileMap::TileMap(sf::Vector2u size, sf::Vector2f cell_size)
    : size_(size), cell_size_(cell_size)
{
    if (size_.x * size_.y == 0)
        throw std::invalid_argument("TileMap must not have length 0!");

    constexpr size_t vertices_per_tile = 4;
    vertices_.resize((size_.x * size_.y) * vertices_per_tile);
    vertices_.setPrimitiveType(sf::Quads);

    for (size_t y = 0; y < size.y; ++y)
        for (size_t x = 0; x < size.x; ++x)
        {
            sf::Vertex *tile = &vertices_[(x + y * size.x) * vertices_per_tile];
            tile[0].position = sf::Vector2f(x * cell_size_.x, y * cell_size_.y);
            tile[1].position =
                sf::Vector2f((x + 1) * cell_size_.x, y * cell_size_.y);
            tile[2].position =
                sf::Vector2f((x + 1) * cell_size_.x, (y + 1) * cell_size_.y);
            tile[3].position =
                sf::Vector2f(x * cell_size_.x, (y + 1) * cell_size_.y);
        }
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(vertices_, states);
}

void TileMap::set_color(const size_t x, const size_t y,
                        sf::Color color) noexcept
{
    constexpr size_t vertices_per_tile = 4;
    sf::Vertex *tile = &vertices_[(x + y * size_.x) * vertices_per_tile];
    for (char i = 0; i < 4; ++i)
        tile[i].color = color;
}

sf::Vector2u TileMap::get_size() const noexcept { return size_; }

sf::Vector2f TileMap::get_cell_size() const noexcept { return cell_size_; }

} // namespace sph::visualization