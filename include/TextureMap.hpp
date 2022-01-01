#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

namespace sph
{
namespace visualization
{
/**
 * @brief
 *
 */
class TextureMap : public sf::Drawable, public sf::Transformable
{
  public:
    /**
     * @brief Construct a new TextureMap object
     *
     * @param size
     * @param cell_size
     */
    explicit TextureMap(sf::Vector2u size);

    /**
     * @brief Set the scale object
     * 
     * @param factor 
     */
    void set_scale(const sf::Vector2f& factor) noexcept;

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
     * @param x
     * @param y
     * @param color
     */
    void set_color(const size_t x, const size_t y, sf::Color color) noexcept;

    /**
     * @brief Get the size object
     *
     * @return sf::Vector2i
     */
    sf::Vector2u get_size() const noexcept;

    /**
     * @brief 
     * 
     */
    void update() noexcept;

  private:
    sf::Vector2u size_;
    sf::Sprite sprite_;
    sf::Texture texture_;
    std::shared_ptr<sf::Uint8> raw_data_;
};
} // namespace visualization
} // namespace sph