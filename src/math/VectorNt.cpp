#include <math/VectorNt.hpp>

namespace SPH
{
template <size_t n, typename T> constexpr VectorNt<n, T>::VectorNt() noexcept
{
    std::fill(data.begin(), data.end(), T());
}

template <size_t n, typename T>
template <typename... Ts, typename, typename>
constexpr VectorNt<n, T>::VectorNt(const Ts &... values) noexcept
{
    data = {values...};
}

template <size_t n, typename T>
constexpr VectorNt<n, T>::VectorNt(const std::array<T, n> &data) noexcept
    : data(data)
{
}

template <size_t n, typename T>
template <typename U>
constexpr VectorNt<n, T>::VectorNt(VectorNt<n, U> other) noexcept
{
    for (size_t i = 0; i < n; ++i)
        data[i] = static_cast<T>(other.data[i]);
}

template <size_t n, typename T>
constexpr auto &VectorNt<n, T>::operator[](const size_t i) noexcept
{
    assert((i < n));
    return data[i];
}

template <size_t n, typename T>
[[nodiscard]] constexpr const auto &VectorNt<n, T>::
operator[](const size_t i) const noexcept
{
    assert((i < n));
    return data[i];
}

template <size_t n, typename T>
template <typename U>
constexpr auto VectorNt<n, T>::operator==(const VectorNt<n, U> &rhs) noexcept
{
    for (size_t i = 0; i < n; ++i)
        if (data[i] != rhs.data[i])
            return false;

    return true;
}

template <size_t n, typename T>
template <typename U>
constexpr auto &VectorNt<n, T>::operator+=(const VectorNt<n, U> &rhs) noexcept
{
    for (size_t i = 0; i < n; ++i)
        data[i] += rhs[i];

    return *this;
}

template <size_t n, typename T>
template <typename U>
constexpr auto &VectorNt<n, T>::operator-=(const VectorNt<n, U> &rhs) noexcept
{
    for (size_t i = 0; i < n; ++i)
        data[i] -= rhs[i];

    return *this;
}

template <size_t n, typename T>
template <typename U>
constexpr auto &VectorNt<n, T>::operator*=(const U &rhs) noexcept
{
    for (size_t i = 0; i < n; ++i)
        data[i] *= rhs;

    return *this;
}

template <size_t n, typename T>
template <typename U>
constexpr auto &VectorNt<n, T>::operator*=(const VectorNt<n, U> &rhs) noexcept
{
    for (size_t i = 0; i < n; ++i)
        data[i] *= rhs[i];

    return *this;
}

template <size_t n, typename T>
template <typename U>
constexpr auto &VectorNt<n, T>::operator/=(const U &rhs)
{
    for (size_t i = 0; i < n; ++i)
        data[i] /= rhs;

    return *this;
}

template <size_t n, typename T>
template <typename U>
constexpr auto &VectorNt<n, T>::operator/=(const VectorNt<n, U> &rhs)
{
    for (size_t i = 0; i < n; ++i)
        data[i] /= rhs[i];

    return *this;
}

template <size_t n, typename T>
[[nodiscard]] constexpr auto min(const VectorNt<n, T> &lhs,
                                 const VectorNt<n, T> &rhs) noexcept
{
    VectorNt<n, T> result;

    for (size_t i = 0; i < n; ++i)
        result[i] = std::min(lhs[i], rhs[i]);

    return result;
}

template <size_t n, typename T>
[[nodiscard]] constexpr auto max(const VectorNt<n, T> &lhs,
                                 const VectorNt<n, T> &rhs) noexcept
{
    VectorNt<n, T> result;

    for (size_t i = 0; i < n; ++i)
        result[i] = std::max(lhs[i], rhs[i]);

    return result;
}

template <size_t n, typename T,
          typename =
              std::enable_if_t<std::is_nothrow_default_constructible<T>::value>>
[[nodiscard]] constexpr auto length2(const VectorNt<n, T> &vector) noexcept
{
    T accumulator = T();
    for (auto &i : vector.data)
        accumulator += i * i;

    return accumulator;
}

template <size_t n, typename T,
          typename = std::enable_if_t<std::is_arithmetic<T>::value>>
[[nodiscard]] constexpr auto length(const VectorNt<n, T> &vector) noexcept
{
    return std::sqrt(length2(vector));
}

template <size_t k, typename U,
          typename =
              std::enable_if_t<std::is_nothrow_default_constructible<U>::value>>
[[nodiscard]] constexpr auto dot(const VectorNt<k, U> &lhs,
                                 const VectorNt<k, U> &rhs) noexcept
{
    U acc = U();

    for (size_t i = 0; i < k; ++i)
        acc += lhs[i] * rhs[i];

    return acc;
}

template <size_t n, typename T>
[[nodiscard]] constexpr auto operator+(VectorNt<n, T> lhs,
                                       const VectorNt<n, T> &rhs) noexcept
{
    lhs += rhs;
    return lhs;
}

template <size_t n, typename T>
[[nodiscard]] constexpr auto operator-(VectorNt<n, T> lhs,
                                       const VectorNt<n, T> &rhs) noexcept
{
    lhs -= rhs;
    return lhs;
}

template <size_t n, typename T>
[[nodiscard]] constexpr auto operator-(VectorNt<n, T> lhs) noexcept
{
    for (size_t i = 0; i < n; ++i)
        lhs[i] = -lhs[i];

    return lhs;
}

template <size_t n, typename T>
[[nodiscard]] constexpr auto operator*(VectorNt<n, T> lhs,
                                       const T &rhs) noexcept
{
    lhs *= rhs;
    return lhs;
}

template <size_t n, typename T>
[[nodiscard]] constexpr auto operator/(VectorNt<n, T> lhs, const T &rhs)
{
    lhs /= rhs;
    return lhs;
}

template <size_t n, typename T>
[[nodiscard]] constexpr auto operator*(VectorNt<n, T> lhs,
                                       const VectorNt<n, T> &rhs) noexcept
{
    lhs *= rhs;
    return lhs;
}

template <size_t n, typename T>
[[nodiscard]] constexpr auto operator/(VectorNt<n, T> lhs,
                                       const VectorNt<n, T> &rhs)
{
    lhs /= rhs;
    return lhs;
}

template <size_t n, typename T>
[[nodiscard]] constexpr auto &operator<<(std::ostream &out,
                                         const VectorNt<n, T> &rhs) noexcept
{
    out << "[ ";
    for (size_t i = 0; i < n; ++i)
        out << rhs.data[i] << " ";
    return out << "]";
}

template <size_t n, typename T>
[[nodiscard]] constexpr auto &operator<<(std::ostream &out,
                                         const VectorNt<n, T> &&rhs) noexcept
{
    return out << rhs;
}
} // namespace SPH
