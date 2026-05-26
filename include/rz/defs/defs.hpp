#pragma once

#include <functional>
#include <expected>
#include <memory>
#include <string>

namespace rz
{
    enum class STATUS
    {
        ERROR = 0,
        SUCCESS,
    };

    using logCB = std::function<void(const std::string&)>;
    inline constexpr auto emptyCB = [](const std::string&) {};

    template <typename T>
    using EXPECTED_UPTR = std::expected<std::unique_ptr<T>, STATUS>;

    template <typename T>
    using EXPECTED_OBJ = std::expected<T, STATUS>;

} // namespace rz