#pragma once

#include <string_view>
#include <ranges>
#include <algorithm>
#include <cctype>

namespace rz
{
    namespace string
    {

        inline bool iequal(std::string_view a, std::string_view b)
        {
            using uchar = unsigned char;
            return std::ranges::equal(a, b, [](char ca, char cb) {
                return std::tolower(uchar(ca)) == std::tolower(uchar(cb));
            });
        }

    } // namespace string
} // namespace rz
