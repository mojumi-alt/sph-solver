#include <visualizer/Window.hpp>

namespace SPH
{
Window::Window(ParticleSystem &ps, const double scale) noexcept
    : scale(scale), ps(ps)
{
    circles.resize(ps.getParticles().size());
    update();

    boundaries.setPrimitiveType(sf::LineStrip);
    boundaries.resize(5);

    double width = ps.getDomainSize()[0], height = ps.getDomainSize()[1];

    boundaries[0].position = sf::Vector2f(0, 0);
    boundaries[1].position = sf::Vector2f(width, 0);
    boundaries[2].position = sf::Vector2f(width, height);
    boundaries[3].position = sf::Vector2f(0, height);
    boundaries[4].position = sf::Vector2f(0, 0);

    for (size_t i = 0; i < 5; ++i)
        boundaries[i].color = sf::Color::Black;
}

void Window::run() noexcept
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(ps.getDomainSize()[0] * scale,
                                          ps.getDomainSize()[1] * scale),
                            "SPH");
    sf::View view(sf::FloatRect(-1.f, -1.f, ps.getDomainSize()[0] + 2,
                                ps.getDomainSize()[0] + 2));
    window.setView(view);
    view.setViewport(sf::FloatRect(0.0f, 0.f, 1.f, 1.f));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        update();
        ps.advance(0.01);

        for (auto &circle : circles)
            window.draw(circle);

        window.draw(boundaries);
        window.display();
    }
}

void Window::update() noexcept
{
    static double max = 0, min = std::numeric_limits<double>::infinity();
    for (auto &p : ps.getParticles())
    {
        max = std::max(p.pressure, max);
        min = std::min(p.pressure, min);
    }

    for (size_t i = 0; i < ps.getParticles().size(); ++i)
    {
        const Particle &p = ps.getParticles()[i];
        circles[i].setOutlineThickness(p.h * 0.2);
        circles[i].setOutlineColor(sf::Color::Black);
        circles[i].setFillColor(
            sf::Color(0, ((p.pressure - min) / (max - min)) * 255, 0, 128));
        circles[i].setRadius(p.h);
        circles[i].setPosition(p.location[0] - p.h, p.location[1] - p.h);
    }
}
} // namespace SPH