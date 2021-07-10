#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "CircleMap.hpp"
#include "ColorMap.hpp"
#include "Grid.hpp"
#include "ParticleSystem.hpp"
#include "SpatialHash.hpp"
#include "TileMap.hpp"

namespace sph
{
class Visualizer
{
  public:
    const size_t foreground_color = 0x98C1D9FF, background_color = 0x3D5A80FF,
                 hash_tile_color = 0x00003060;
    const float offset = 1.f;

    /**
     * @brief Construct a new Visualizer object
     *
     * @param ps Particle system to visualize.
     * @param scaling Window scaling.
     */
    explicit Visualizer(ParticleSystem &ps, const float scaling = 1.0) noexcept;

    /**
     * @brief Open and run visualizer window.
     *
     */
    void run() noexcept;

  private:
    ParticleSystem &ps_;
    size_t particle_count_;
    float scaling_, h_;
    ColorMap cmap_;
    sf::Font font_;
    sf::Text stats_;
    sf::VertexArray force_arrows_, obstacles_;
    visualization::CircleMap circles_;
    visualization::Grid boundaries_, hash_grid_;
    visualization::TileMap hash_tiles_;

    /**
     * @brief Compute updates of all visualizer structures by filling in
     * values from particle system.
     *
     */
    void update_() noexcept;

    /**
     * @brief Compute the "optimal" visual particle radius.
     * Sometimes the physical radius is to big so it obscures everything
     * so we may choose one thats a bit smaller.
     *
     * @return The radius estimation.
     */
    float compute_optimal_h_() noexcept;
};
} // namespace sph