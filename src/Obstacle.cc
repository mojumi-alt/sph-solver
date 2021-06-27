#include "Obstacle.hpp"

#include <math.h>

namespace sph
{

inline float length(const sf::Vector2f &v)
{
    return std::sqrt(v.x * v.x + v.y * v.y);
}

Obstacle::Obstacle(sf::Vector2f start, sf::Vector2f end)
    : start_(start), end_(end)
{
    normal_ = end - start;
    normal_ = {-normal_.y, normal_.x};
    normal_ /= length(normal_);

    start -= start_;
    end -= start_;
    auto temp = end - start;
    length_ = length(temp);
    theta_ = std::acos((temp.x * length_) / (length_ * length_));
    if (end.y < 0)
        theta_ = 2 * M_PI - theta_;
    cos_theta_ = std::cos(theta_);
    sin_theta_ = std::sin(theta_);
}

float Obstacle::distance(sf::Vector2f point) const noexcept
{
    auto projected = project_on_(point);

    if (projected.x < 0)
        return length(projected);
    else if (projected.x > length_)
        return length({projected.x - length_, projected.y});
    else
        return std::abs(projected.y);
}

sf::Vector2f Obstacle::reflect(sf::Vector2f incident) const noexcept
{
    return incident -
           2 * (incident.x * normal_.x + incident.y * normal_.y) * normal_;
}

sf::Vector2f Obstacle::project_on_(sf::Vector2f point) const noexcept
{
    point -= start_;
    return {point.x * cos_theta_ + point.y * sin_theta_,
            -point.x * sin_theta_ + point.y * cos_theta_};
}

sf::Vector2f Obstacle::inverse_project_on_(sf::Vector2f point) const noexcept
{
    point = {point.x * cos_theta_ - point.y * sin_theta_,
             point.x * sin_theta_ + point.y * cos_theta_};
    return point + start_;
}

std::pair<sf::Vector2f, sf::Vector2f> Obstacle::get_line_coords() const noexcept
{
    return {start_, end_};
}

} // namespace sph