#pragma once

#include <initializer_list>
#include <string_view>
#include <algorithm>
#include <cctype>
#include <span>

namespace rz
{
    namespace string
    {

        inline bool iequal(const std::string_view a, const std::string_view b)
        {
            using uchar = unsigned char;
            return std::ranges::equal(a, b, [](char ca, char cb) {
                return std::tolower(uchar(ca)) == std::tolower(uchar(cb));
            });
        }

        inline bool iequal_many(const std::string_view a, std::span<const std::string_view> b)
        {
            return std::ranges::any_of(b, [a](const std::string_view i) {
                return iequal(a, i);
            });
        }

        inline bool iequal_many(const std::string_view a, std::initializer_list<std::string_view> b)
        {
            return iequal_many(a, std::span<const std::string_view>(b));
        }

    } // namespace string
} // namespace rz
