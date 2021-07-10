#pragma once

#include <SFML/System/Vector2.hpp>
#include <utility>

namespace sph
{

class Obstacle
{
  public:
    float bounce = 0.9;

    /**
     * @brief Construct a new Obstacle object
     *
     * @param start
     * @param end
     */
    explicit Obstacle(sf::Vector2f start, sf::Vector2f end);

    /**
     * @brief
     *
     * @param point
     * @return float
     */
    float distance(sf::Vector2f point) const noexcept;

    /**
     * @brief
     *
     * @param incident
     * @return sf::Vector2f
     */
    sf::Vector2f reflect(sf::Vector2f incident) const noexcept;

    /**
     * @brief Get the line coords object
     *
     * @return std::pair<sf::Vector2f, sf::Vector2f>
     */
    std::pair<sf::Vector2f, sf::Vector2f> get_line_coords() const noexcept;

  private:
    sf::Vector2f start_, end_, normal_;
    float length_, theta_, sin_theta_, cos_theta_;

    /**
     * @brief
     *
     * @param point
     * @return sf::Vector2f
     */
    sf::Vector2f project_on_(sf::Vector2f point) const noexcept;

    /**
     * @brief
     *
     * @param point
     * @return sf::Vector2f
     */
    sf::Vector2f inverse_project_on_(sf::Vector2f point) const noexcept;
};

} // namespace sph