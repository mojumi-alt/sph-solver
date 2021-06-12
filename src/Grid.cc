#include "Grid.hpp"

#include <exception>

namespace sph::visualization
{

Grid::Grid(sf::Vector2u size, sf::Vector2f cell_size)
    : size_(size), cell_size_(cell_size)
{
    if (size_.x * size_.y == 0)
        throw std::invalid_argument("Grid must not have length 0!");

    constexpr size_t vertices_per_line = 2;
    vertices_.resize((size_.x + size_.y) * vertices_per_line);
    vertices_.setPrimitiveType(sf::Lines);

    for (size_t i = 0; i < size_.x; ++i)
    {
        sf::Vertex *line = &vertices_[i * vertices_per_line];

        line[0].position = sf::Vector2f(i * cell_size_.x, 0);
        line[1].position =
            sf::Vector2f(i * cell_size_.x, cell_size_.y * (size_.y - 1));
    }

    for (size_t i = 0; i < size_.y; ++i)
    {
        sf::Vertex *line =
            &vertices_[size_.x * vertices_per_line + i * vertices_per_line];

        line[0].position = sf::Vector2f(0, i * cell_size_.y);
        line[1].position =
            sf::Vector2f((size_.x - 1) * cell_size_.x, i * cell_size_.y);
    }
}

void Grid::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(vertices_, states);
}

void Grid::set_color(sf::Color color) noexcept
{
    for (size_t i = 0; i < vertices_.getVertexCount(); ++i)
        vertices_[i].color = color;
}

sf::Vector2u Grid::get_size() const noexcept { return size_; }

sf::Vector2f Grid::get_cell_size() const noexcept { return cell_size_; }

} // namespace sph::visualization