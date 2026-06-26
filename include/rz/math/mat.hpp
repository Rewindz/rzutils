#pragma once
#include <array>
#include <cstddef>
#include <utility>

namespace rz
{
    namespace math
    {

        template <typename T>
        struct Mat4
        {
            std::array<T, 16> arr{};

            Mat4() = default;

            template <typename Self>
            decltype(auto) operator[](this Self&& self, std::size_t idx) {
                return std::forward<Self>(self).arr[idx];
            }

            template <typename Self>
            decltype(auto) at(this Self&& self, std::size_t idx) {
                return std::forward<Self>(self).arr.at(idx);
            }

            template <typename Self>
            decltype(auto) operator()(this Self&& self, std::size_t row, std::size_t col) {
                return std::forward<Self>(self).arr[row * 4 + col];
            }

            static Mat4 Identity() {
                Mat4 res;
                res[0]  = T{1};
                res[5]  = T{1};
                res[10] = T{1};
                res[15] = T{1};
                return res;
            };

            Mat4 Transposed() const {
                Mat4 res;
                for(std::size_t r = 0; r < 4; r++) {
                    for(std::size_t c = 0; c < 4; c++) {
                        res[c * 4 + r] = *this[r * 4 + c];
                    }
                }
                return res;
            }

            Mat4& Transpose() {
                *this = this->Transposed();
                return *this;
            }

        };

        using Mat4f = Mat4<float>;
    } // namespace math
} // namespace rz
