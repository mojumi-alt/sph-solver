#pragma once

namespace sph
{
namespace kernels
{
/**
 * @brief
 *
 * @param r
 * @param h
 * @return float
 */
float poly6(const float r, const float h);

/**
 * @brief
 *
 * @param r
 * @param h
 * @return float
 */
float nabbla_poly6(const float r, const float h);

/**
 * @brief
 *
 * @param r
 * @param h
 * @return float
 */
float laplace_poly6(const float r, const float h);

} // namespace kernels
} // namespace sph