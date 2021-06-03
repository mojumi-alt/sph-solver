#include <visualizer/Window.hpp>

#include <iostream>
#include <sstream>

namespace SPH
{
    Window::Window(ParticleSystem &ps, const double scale) noexcept
        : scale(scale), ps(ps)
    {
        circles.resize(ps.getParticles().size());
        lines.setPrimitiveType(sf::Lines);
        lines.resize(ps.getParticles().size() * 2);
        font.loadFromFile("./arial.ttf");
        stats.setFont(font);
        stats.setPosition(0, -0.7);
        stats.setScale(0.006, 0.006);

        boundaries.setPrimitiveType(sf::LineStrip);
        boundaries.resize(5);

        double width = ps.getDomainSize()[0], height = ps.getDomainSize()[1];
        auto cellsize = 10 / 33.0;

        boundaries[0].position = sf::Vector2f(0, 0);
        boundaries[1].position = sf::Vector2f(width, 0);
        boundaries[2].position = sf::Vector2f(width, height);
        boundaries[3].position = sf::Vector2f(0, height);
        boundaries[4].position = sf::Vector2f(0, 0);
        

        for (auto& circle: circles)
            circle.setOrigin(sf::Vector2f(0.3, 0.3));        

        for (size_t i = 0; i < 5; ++i)
            boundaries[i].color = sf::Color(0x98C1D9FF);

        tiles.resize(33 * 33 * 4);
        tiles.setPrimitiveType(sf::Quads);

        for (int x = 0; x < 33; ++x)
            for (int y = 0; y < 33; ++y)
            {
                sf::Vertex *quad = &tiles[(x + y * 33) * 4];
                quad[0].position = sf::Vector2f(x * cellsize, y * cellsize);
                quad[1].position = sf::Vector2f((x + 1) * cellsize, y * cellsize);
                quad[2].position =
                    sf::Vector2f((x + 1) * cellsize, (y + 1) * cellsize);
                quad[3].position = sf::Vector2f(x * cellsize, (y + 1) * cellsize);

                quad[0].color = sf::Color(0x3D5A80FF);
                quad[1].color = sf::Color(0x3D5A80FF);
                quad[2].color = sf::Color(0x3D5A80FF);
                quad[3].color = sf::Color(0x3D5A80FF);
            }

        hash_lines.setPrimitiveType(sf::Lines);
        hash_lines.resize(66 * 2);
        std::cout << cellsize << "\n";
        for (float x = 0; x < 33; x++)
        {
            sf::Vertex *line = &hash_lines[x * 2];
            line[0].position = sf::Vector2f(x * cellsize, 0);
            line[1].position = sf::Vector2f(x * cellsize, height);
            line[0].color = sf::Color(0x98C1D9FF);
            line[1].color = sf::Color(0x98C1D9FF);

            line = &hash_lines[(x + 33) * 2];
            line[0].position = sf::Vector2f(0, x * cellsize);
            line[1].position = sf::Vector2f(height, x * cellsize);
            line[0].color = sf::Color(0x98C1D9FF);
            line[1].color = sf::Color(0x98C1D9FF);
        }    


        update();
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

        sf::Clock clk;
        bool interact = false;
         ps.advance(0.03);

        while (window.isOpen())
        {
            clk.restart();
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    interact = true;
                }

                if (event.type == sf::Event::MouseButtonReleased)
                {
                    interact = false;
                }
            }

            window.clear(sf::Color(0x3D5A80FF));

            if (interact)
            {
                auto sf_location = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                auto location = Vector2d((float)sf_location.x - 0.3, (float)sf_location.y - 0.3);
                sf::CircleShape marker;
                marker.setPosition(sf_location.x - 0.3, sf_location.y - 0.3);
                marker.setFillColor(sf::Color(0, 0, 0, 128));
                marker.setRadius(0.3);
                window.draw(marker);
                for (auto &pi : ps.getParticles())
                {
                    auto dir = pi.location - location;
                    auto len = length(dir);

                    if (len == 0 or len > 0.3)
                        continue;
                    std::cout << len << "\n";

                    pi.external = dir / len * 1000.0;
                }
            }
            ps.interactions = 0;
            ps.advance(0.03);
            auto update_time = clk.getElapsedTime().asMilliseconds();
            clk.restart();
            update();

            window.draw(tiles);
            window.draw(hash_lines);

            for (auto &circle : circles)
                window.draw(circle);

            window.draw(lines);

            window.draw(boundaries);
            
            std::stringstream ss;
            ss << "Update time: " << update_time << " [ms]\nDraw time: ";
            ss << clk.getElapsedTime().asMilliseconds() << " [ms]\n";
            ss << "Interactions: " << ps.interactions;
            stats.setString(ss.str());
            window.draw(stats);
            window.display();
        }
    }

    void Window::update() noexcept
    {
        double max = 0, min = std::numeric_limits<double>::infinity();
        for (auto &p : ps.getParticles())
        {
            max = std::max(p.rho, max);
            min = std::min(p.rho, min);
            //std::cout << p.location << " " << p.surfaceNormal << "\n";
        }

        for (size_t i = 0; i < ps.getParticles().size(); ++i)
        {
            const Particle &p = ps.getParticles()[i];
            //circles[i].setOutlineThickness(p.h * 0.05);
            //circles[i].setOutlineColor(sf::Color::Black);
            circles[i].setFillColor(cmap.rainbow[((p.rho - min) / (max - min)) * 255]);
            circles[i].setRadius(0.3);
            circles[i].setPosition(p.location[0], p.location[1]);

            auto len = length(p.acceleration);
            auto dir = p.acceleration / len * 0.3;
            if (len > 0)
            {
                lines[i * 2].position = sf::Vector2f((float)p.location[0], (float)p.location[1]);
                lines[i * 2 + 1].position = sf::Vector2f((float)p.location[0] + dir[0], (float)p.location[1] + dir[1]);
                lines[i * 2].color = sf::Color::Black;
                lines[i * 2 + 1].color = sf::Color::Black;
            }
        }

    
        for (int x = 0; x < 33; ++x)
            for (int y = 0; y < 33; ++y)
            {
                const SpatialHash::bucket& bucket = ps.hash_.get_bucket(x, y);
                auto count = bucket.size();
                sf::Vertex *quad = &tiles[(x + y * 33) * 4];
                //if (count > 0)
                // std::cout << x << " " << y << "\n";

                quad[0].color = sf::Color(0x3D5A80FF + 0x60000000 * count);
                quad[1].color = sf::Color(0x3D5A80FF + 0x60000000 * count);
                quad[2].color = sf::Color(0x3D5A80FF + 0x60000000 * count);
                quad[3].color = sf::Color(0x3D5A80FF + 0x60000000 * count);
            }
    }
} // namespace SPH