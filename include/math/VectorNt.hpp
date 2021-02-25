#ifndef SPH_VECTORNT_H
#define SPH_VECTORNT_H

#include <array>
#include <cassert>
#include <cmath>
#include <ostream>

namespace SPH
{
template <size_t n, typename T> class VectorNt
{
  public:
    std::array<T, n> data;

    explicit constexpr VectorNt() noexcept;

    template <
        typename... Ts,
        typename = std::enable_if_t<((std::is_same<Ts, T>::value) && ...)>,
        typename = std::enable_if_t<sizeof...(Ts) == n>>
    explicit constexpr VectorNt(const Ts &... values) noexcept;

    explicit constexpr VectorNt(const std::array<T, n> &data) noexcept;

    template <typename U> constexpr VectorNt(VectorNt<n, U> other) noexcept;

    [[nodiscard]] constexpr auto &operator[](const size_t i) noexcept;

    [[nodiscard]] constexpr const auto &operator[](const size_t i) const
        noexcept;

    template <typename U>
    constexpr auto operator==(const VectorNt<n, U> &rhs) noexcept;

    template <typename U>
    constexpr auto &operator+=(const VectorNt<n, U> &rhs) noexcept;

    template <typename U>
    constexpr auto &operator-=(const VectorNt<n, U> &rhs) noexcept;

    template <typename U> constexpr auto &operator*=(const U &rhs) noexcept;

    template <typename U>
    constexpr auto &operator*=(const VectorNt<n, U> &rhs) noexcept;

    template <typename U> constexpr auto &operator/=(const U &rhs);

    template <typename U> constexpr auto &operator/=(const VectorNt<n, U> &rhs);

    template <size_t k, typename U>
    [[nodiscard]] friend constexpr auto min(const VectorNt<k, U> &lhs,
                                            const VectorNt<k, U> &rhs) noexcept;

    template <size_t k, typename U>
    [[nodiscard]] friend constexpr auto max(const VectorNt<k, U> &lhs,
                                            const VectorNt<k, U> &rhs) noexcept;

    template <size_t k, typename U, typename>
    [[nodiscard]] friend constexpr auto
    length2(const VectorNt<k, U> &vector) noexcept;

    template <size_t k, typename U, typename>
    [[nodiscard]] friend constexpr auto
    length(const VectorNt<k, U> &vector) noexcept;

    template <size_t k, typename U, typename>
    [[nodiscard]] friend constexpr auto dot(const VectorNt<k, U> &lhs,
                                            const VectorNt<k, U> &rhs) noexcept;

    template <size_t k, typename U>
    [[nodiscard]] friend constexpr auto
    operator+(VectorNt<k, U> lhs, const VectorNt<k, U> &rhs) noexcept;

    template <size_t k, typename U>
    [[nodiscard]] friend constexpr auto
    operator-(VectorNt<k, U> lhs, const VectorNt<k, U> &rhs) noexcept;

    template <size_t k, typename U>
    [[nodiscard]] friend constexpr auto operator-(VectorNt<k, U> lhs) noexcept;

    template <size_t k, typename U>
    [[nodiscard]] friend constexpr auto operator*(VectorNt<k, U> lhs,
                                                  const U &rhs) noexcept;

    template <size_t k, typename U>
    [[nodiscard]] friend constexpr auto operator/(VectorNt<k, U> lhs,
                                                  const U &rhs);

    template <size_t k, typename U>
    [[nodiscard]] friend constexpr auto
    operator*(VectorNt<k, U> lhs, const VectorNt<k, U> &rhs) noexcept;

    template <size_t k, typename U>
    [[nodiscard]] friend constexpr auto operator/(VectorNt<k, U> lhs,
                                                  const VectorNt<k, U> &rhs);

    template <size_t k, typename U>
    [[nodiscard]] friend constexpr auto &
    operator<<(std::ostream &out, const VectorNt<k, U> &rhs) noexcept;

    template <size_t k, typename U>
    [[nodiscard]] friend constexpr auto &
    operator<<(std::ostream &out, const VectorNt<k, U> &&rhs) noexcept;
};
} // namespace SPH

#include "./../../src/math/VectorNt.cpp"

namespace SPH
{
typedef VectorNt<4, unsigned long> Vector4u;
typedef VectorNt<4, int> Vector4i;
typedef VectorNt<4, float> Vector4f;
typedef VectorNt<4, double> Vector4d;
typedef VectorNt<2, unsigned long> Vector2u;
typedef VectorNt<2, int> Vector2i;
typedef VectorNt<2, float> Vector2f;
typedef VectorNt<2, double> Vector2d;
} // namespace SPH

#endif
