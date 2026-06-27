#pragma once
#include <numbers>

namespace rz
{
    namespace math
    {

        template <typename T>
        constexpr T radians(T degrees) {
            return degrees * (std::numbers::pi_v<T> / T{180});
        }

    } // namespace math
} // namespace rz
