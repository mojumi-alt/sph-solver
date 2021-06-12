#pragma once

#include <SFML/Graphics.hpp>

namespace sph
{
namespace visualization
{
/**
 * @brief
 *
 */
class Grid : public sf::Drawable, public sf::Transformable
{
  public:
    /**
     * @brief Construct a new Grid object
     *
     * @param size
     * @param cell_size
     */
    explicit Grid(sf::Vector2u size, sf::Vector2f cell_size);

    /**
     * @brief
     *
     * @param target
     * @param states
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    /**
     * @brief Set the color object
     *
     * @param color
     */
    void set_color(sf::Color color) noexcept;

    /**
     * @brief Get the size object
     *
     * @return sf::Vector2i
     */
    sf::Vector2u get_size() const noexcept;

    /**
     * @brief Get the cell size object
     *
     * @return sf::Vector2f
     */
    sf::Vector2f get_cell_size() const noexcept;

  private:
    sf::Vector2u size_;
    sf::Vector2f cell_size_;
    sf::VertexArray vertices_;
};
} // namespace visualization
} // namespace sph