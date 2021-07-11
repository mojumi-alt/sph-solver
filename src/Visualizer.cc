#include <Visualizer.hpp>
#include <sstream>

#include "Interact.hpp"

namespace sph
{

inline float length(const sf::Vector2f &v)
{
    return std::sqrt(v.x * v.x + v.y * v.y);
}

inline sf::Vector2u vec_ceil(const sf::Vector2f &vec)
{
    return {static_cast<unsigned int>(std::ceil(vec.x)),
            static_cast<unsigned int>(std::ceil(vec.y))};
}

Visualizer::Visualizer(ParticleSystem &ps, const float scaling) noexcept
    : scaling_(scaling), ps_(ps), h_(compute_optimal_h_()),
      particle_count_(ps.get_particles().size()), cmap_(color_maps::rainbow),
      circles_(particle_count_, h_), boundaries_({2, 2}, ps.get_domain_size()),
      hash_grid_(vec_ceil(ps_.get_domain_size() / ps_.get_particle_size()) +
                     sf::Vector2u{1, 1},
                 {ps_.get_particle_size(), ps_.get_particle_size()}),
      hash_tiles_(vec_ceil(ps_.get_domain_size() / ps_.get_particle_size()),
                  {ps_.get_particle_size(), ps_.get_particle_size()})
{
    font_.loadFromFile("./arial.ttf");
    stats_.setFont(font_);
    stats_.setPosition(0, -0.7);
    stats_.setScale(0.006, 0.006);

    constexpr size_t vertices_per_line = 2;
    force_arrows_.resize(particle_count_ * vertices_per_line);
    force_arrows_.setPrimitiveType(sf::Lines);
    for (size_t i = 0; i < force_arrows_.getVertexCount(); ++i)
        force_arrows_[i].color = sf::Color::Black;

    auto ps_obstacles = ps.get_obstacles();
    obstacles_.resize(ps_obstacles.size() * vertices_per_line);
    obstacles_.setPrimitiveType(sf::Lines);
    for (size_t i = 0; i < ps_obstacles.size(); ++i)
    {
        sf::Vertex *current = &obstacles_[i * vertices_per_line];

        auto [start, end] = ps_obstacles[i].get_line_coords();
        current[0].position = start;
        current[0].color = sf::Color(foreground_color);
        current[1].position = end;
        current[1].color = sf::Color(foreground_color);
    }

    boundaries_.set_color(sf::Color(foreground_color));
    hash_grid_.set_color(sf::Color(0xFFFFFF30));

    update_();
}

void Visualizer::run() noexcept
{

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(ps_.get_domain_size().x * scaling_,
                                          ps_.get_domain_size().y * scaling_),
                            "SPH");
    sf::View view(sf::FloatRect(-offset, -offset,
                                ps_.get_domain_size().x + offset + 1,
                                ps_.get_domain_size().y + offset + 1));
    window.setView(view);
    view.setViewport(sf::FloatRect(0.0f, 0.f, offset, offset));

    sf::Clock clk;
    Interaction interactions(ps_);

    while (window.isOpen())
    {
        clk.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            interactions.set_state(event);
        }
        interactions.interact(window);

        window.clear(sf::Color(background_color));

        ps_.advance(0.05);
        auto update_time = clk.getElapsedTime().asMilliseconds();
        clk.restart();
        update_();

        window.draw(boundaries_);
        window.draw(hash_tiles_);
        window.draw(hash_grid_);
        window.draw(circles_);
        window.draw(obstacles_);
        window.draw(force_arrows_);

        std::stringstream ss;
        ss << "Update time: " << update_time << " [ms]\nDraw time: ";
        ss << clk.getElapsedTime().asMilliseconds() << " [ms]\n";
        ss << "Interactions: " << ps_.interactions;
        stats_.setString(ss.str());
        window.draw(stats_);
        window.display();
    }
}

void Visualizer::update_() noexcept
{

    constexpr size_t vertices_per_line = 2, vertices_per_quad = 4;

    size_t current_ps_count = ps_.get_particles().size();
    if (current_ps_count > particle_count_)
    {
        force_arrows_.resize(current_ps_count * vertices_per_line);
        for (int i = particle_count_; i < current_ps_count; ++i)
        {
            circles_.push(h_);

            sf::Vertex *line = &force_arrows_[i * vertices_per_line];
            line[0].color = sf::Color::Black;
            line[1].color = sf::Color::Black;
        }

        particle_count_ = current_ps_count;
    }

    float vmax = length({ps_.vmax, ps_.vmax}), vmin = 0.0;
    const auto &particles = ps_.get_particles();

    for (size_t i = 0; i < particle_count_; ++i)
    {
        const Particle &particle = particles[i];
        circles_.set_color(
            i,
            cmap_.map[((length(particle.v) - vmin) / (vmax - vmin)) * 255.f]);
        circles_.set_location(i, particle.s);

        auto len = length(particle.a);
        auto dir = particle.a / len * h_;
        if (len < ps_.epsilon)
            dir = {0.f, 0.f};

        sf::Vertex *line = &force_arrows_[i * vertices_per_line];
        line[0].position = particle.s;
        line[1].position = particle.s + dir;
    }

    const auto [x_count, y_count] = ps_.get_spatial_hash().get_segment_size();
    for (size_t y = 0; y < y_count; ++y)
        for (size_t x = 0; x < x_count; ++x)
        {
            auto count = ps_.get_spatial_hash().get_bucket(x, y).size();
            hash_tiles_.set_color(x, y, sf::Color(hash_tile_color * count));
        }
}

float Visualizer::compute_optimal_h_() noexcept
{
    return ps_.get_particle_size() / 2.0;
}
} // namespace sph