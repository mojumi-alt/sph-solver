#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace sph
{
namespace visualization
{
/**
 * @brief
 *
 */
class CircleMap : public sf::Drawable, public sf::Transformable
{
  public:
    /**
     * @brief Construct a new CircleMap object
     *
     * @param size
     * @param cell_size
     */
    explicit CircleMap(const size_t count, const float radius) noexcept;

    /**
     * @brief
     *
     * @param target
     * @param states
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    /**
     * @brief Get the circles object
     *
     * @return std::vector<sf::CircleShape>&
     */
    std::vector<sf::CircleShape> &get_circles() noexcept;

    /**
     * @brief Set the color object
     *
     * @param i
     * @param color
     */
    void set_color(const size_t i, sf::Color color) noexcept;

    /**
     * @brief Set the location object
     *
     * @param i
     * @param location
     */
    void set_location(const size_t i, sf::Vector2f location) noexcept;

  private:
    std::vector<sf::CircleShape> circles_;
};
} // namespace visualization
} // namespace sph