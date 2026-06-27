#pragma once
#include "vec.hpp"

namespace rz
{
    namespace math
    {

        template <typename T>
        struct Quaternion
        {
            T x{}, y{}, z{};
            T w{T{1}};

            Quaternion() = default;

            Quaternion(T _x, T _y, T _z, T _w)
                : x(_x), y(_y), z(_z), w(_w)
            {}

            Quaternion(T scalar, const Vec3<T>& vector)
                : x(vector.x), y(vector.y), z(vector.z), w(scalar)
            {}

            Vec3<T> vec() const{
                return Vec3(x, y, z);
            }

            Quaternion& copyVec(const Vec3<T>& v) {
                x = v.x;
                y = v.y;
                z = v.z;
                return *this;
            }

            auto operator<=>(const Quaternion&) const = default;

            friend Quaternion operator*(const Quaternion& a, const Quaternion& b) {
                return Quaternion(
                    a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
                    a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
                    a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w,
                    a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z
                );
            }

            Quaternion& operator*=(const Quaternion& b) {
                *this = *this * b;
                return *this;
            }

            static Quaternion angleAxis(T angleRads, const Vec3<T>& normalizedAxis) {
                T halfAngle = angleRads / T{2};
                T s = std::sin(halfAngle);
                T c = std::cos(halfAngle);

                return Quaternion(
                    normalizedAxis.x * s,
                    normalizedAxis.y * s,
                    normalizedAxis.z * s,
                    c
                );
            }

        };

        using Quatf = Quaternion<float>;

    } // namespace math
} // namespace rz
