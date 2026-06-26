#pragma once
#include <cmath>
#include <cstddef>
#include <utility>

namespace rz
{
    namespace math
    {

        template <typename T>
        struct Vec2
        {
            T x{}, y{};

            Vec2() = default;

            Vec2(T _x, T _y)
                : x(_x), y(_y)
            {}

            auto operator<=>(const Vec2&) const = default;

            bool isNearlyEqual(const Vec2& b, T epsilon = T{0.00001}) const {
                return std::abs(x - b.x) <= epsilon &&
                    std::abs(y - b.y) <= epsilon;
            }

            template <typename Self>
            decltype(auto) operator[](this Self&& self, std::size_t i) {
                auto* data_ptr = &self.x;
                using ReturnType = decltype((std::forward<Self>(self).x));
                return static_cast<ReturnType>(data_ptr[i]);
            }

            Vec2& operator*=(T scalar) {
                x *= scalar;
                y *= scalar;
                return *this;
            }

            Vec2& operator+=(const Vec2 b) {
                x += b.x;
                y += b.y;
                return *this;
            }

            Vec2& operator-=(const Vec2 b) {
                x -= b.x;
                y -= b.y;
                return *this;
            }

            Vec2& operator/=(T scalar) {
                x /= scalar;
                y /= scalar;
                return *this;
            }

            Vec2 operator-() const {
                return Vec2(-x, -y);
            }

            friend Vec2 operator+(Vec2 a, const Vec2& b) {
                a += b;
                return a;
            }

            friend Vec2 operator-(Vec2 a, const Vec2& b) {
                a -= b;
                return a;
            }

            friend Vec2 operator/(Vec2 a, T scalar) {
                a /= scalar;
                return a;
            }

            friend Vec2 operator*(Vec2 v, T scalar) {
                v *= scalar;
                return v;
            }

            friend Vec2 operator*(T scalar, Vec2 v) {
                v *= scalar;
                return v;
            }

            T dot(const Vec2& b) const {
                return (x * b.x) + (y * b.y);
            }

            T mag() const {
                return std::sqrt((x * x) + (y * y));
            }

            T magSq() const {
                return (x * x) + (y * y);
            }

            Vec2& normalize() {
                T mag = mag();
                if(mag > T{0}) {
                    T invMag = T{1} / mag;
                    *this *= invMag;
                }
                return *this;
            }

            Vec2 normalized() const {
                Vec2 copy = *this;
                copy.normalize();
                return copy;
            }

        };

        template <typename T>
        struct Vec3
        {
            T x{}, y{}, z{};

            Vec3() = default;
            Vec3(T _x, T _y, T _z)
                : x(_x), y(_y), z(_z)
            {}

            explicit Vec3(const Vec2<T>& a, T _z = T{})
                : x(a.x), y(a.y), z(_z)
            {}

            auto operator<=>(const Vec3&) const = default;

            bool isNearlyEqual(const Vec3& b, T epsilon = T{0.00001}) const {
                return std::abs(x - b.x) <= epsilon &&
                    std::abs(y - b.y) <= epsilon &&
                    std::abs(z - b.z) <= epsilon;
            }

            template <typename Self>
            decltype(auto) operator[](this Self&& self, std::size_t i) {
                auto* data_ptr = &self.x;
                using ReturnType = decltype((std::forward<Self>(self).x));
                return static_cast<ReturnType>(data_ptr[i]);
            }

            Vec3& operator*=(T scalar) {
                x *= scalar;
                y *= scalar;
                z *= scalar;
                return *this;
            }

            Vec3& operator+=(const Vec3 b) {
                x += b.x;
                y += b.y;
                z += b.z;
                return *this;
            }

            Vec3& operator-=(const Vec3 b) {
                x -= b.x;
                y -= b.y;
                z -= b.z;
                return *this;
            }

            Vec3& operator/=(T scalar) {
                x /= scalar;
                y /= scalar;
                z /= scalar;
                return *this;
            }

            Vec3 operator-() const {
                return Vec3(-x, -y, -z);
            }

            friend Vec3 operator+(Vec3 a, const Vec3& b) {
                a += b;
                return a;
            }

            friend Vec3 operator-(Vec3 a, const Vec3& b) {
                a -= b;
                return a;
            }

            friend Vec3 operator/(Vec3 a, T scalar) {
                a /= scalar;
                return a;
            }

            friend Vec3 operator*(Vec3 v, T scalar) {
                v *= scalar;
                return v;
            }

            friend Vec3 operator*(T scalar, Vec3 v) {
                v *= scalar;
                return v;
            }

            T dot(const Vec3& b) const {
                return (x * b.x) + (y * b.y) + (z * b.z);
            }

            Vec3 cross(const Vec3& b) const {
                return {
                    y * b.z - z * b.y,
                    z * b.x - x * b.z,
                    x * b.y - y * b.x
                };
            }

            T mag() const {
                return std::sqrt((x * x) + (y * y) + (z * z));
            }

            T magSq() const {
                return (x * x) + (y * y) + (z * z);
            }

            Vec3& normalize() {
                T m = mag();
                if(m > T{0}) {
                    T invMag = T{1} / m;
                    *this *= invMag;
                }
                return *this;
            }

            Vec3 normalized() const {
                Vec3 copy = *this;
                copy.normalize();
                return copy;
            }

        };

        template <typename T>
        struct Vec4
        {
            T x{}, y{}, z{}, w{};

            Vec4() = default;
            Vec4(T _x, T _y, T _z, T _w)
                : x(_x), y(_y), z(_z), w(_w)
            {}

            explicit Vec4(const Vec3<T>& a, T _w = T{})
                : x(a.x), y(a.y), z(a.z), w(_w)
            {}
            explicit Vec4(const Vec2<T>& a, const Vec2<T>& b)
                : x(a.x), y(a.y), z(b.x), w(b.y)
            {}

            auto operator<=>(const Vec4&) const = default;

            bool isNearlyEqual(const Vec4& b, T epsilon = T{0.00001}) const {
                return std::abs(x - b.x) <= epsilon &&
                    std::abs(y - b.y) <= epsilon &&
                    std::abs(z - b.z) <= epsilon &&
                    std::abs(w - b.w) <= epsilon;
            }

            template <typename Self>
            decltype(auto) operator[](this Self&& self, std::size_t i) {
                auto* data_ptr = &self.x;
                using ReturnType = decltype((std::forward<Self>(self).x));
                return static_cast<ReturnType>(data_ptr[i]);
            }

            Vec4& operator*=(T scalar) {
                x *= scalar;
                y *= scalar;
                z *= scalar;
                w *= scalar;
                return *this;
            }

            Vec4& operator+=(const Vec4 b) {
                x += b.x;
                y += b.y;
                z += b.z;
                w += b.w;
                return *this;
            }

            Vec4& operator-=(const Vec4 b) {
                x -= b.x;
                y -= b.y;
                z -= b.z;
                w -= b.w;
                return *this;
            }

            Vec4& operator/=(T scalar) {
                x /= scalar;
                y /= scalar;
                z /= scalar;
                w /= scalar;
                return *this;
            }

            Vec4 operator-() const {
                return Vec4(-x, -y, -z, -w);
            }

            friend Vec4 operator+(Vec4 a, const Vec4& b) {
                a += b;
                return a;
            }

            friend Vec4 operator-(Vec4 a, const Vec4& b) {
                a -= b;
                return a;
            }

            friend Vec4 operator/(Vec4 a, T scalar) {
                a /= scalar;
                return a;
            }

            friend Vec4 operator*(Vec4 v, T scalar) {
                v *= scalar;
                return v;
            }

            friend Vec4 operator*(T scalar, Vec4 v) {
                v *= scalar;
                return v;
            }

            T dot(const Vec4& b) const {
                return (x * b.x) + (y * b.y) + (z * b.z) + (w * b.w);
            }

            T mag() const {
                return std::sqrt((x * x) + (y * y) + (z * z) + (w * w));
            }

            T magSq() const {
                return (x * x) + (y * y) + (z * z) + (w * w);
            }

            Vec4& normalize() {
                T mag = mag();
                if(mag > T{0}) {
                    T invMag = T{1} / mag;
                    *this *= invMag;
                }
                return *this;
            }

            Vec4 normalized() const {
                Vec4 copy = *this;
                copy.normalize();
                return copy;
            }
        };

        using Vec2f = Vec2<float>;
        using Vec3f = Vec3<float>;
        using Vec4f = Vec4<float>;

        using Vec2i = Vec2<int>;
        using Vec3i = Vec3<int>;
        using Vec4i = Vec4<int>;

    } // namespace math
} // namespace rz
