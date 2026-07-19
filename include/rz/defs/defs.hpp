#pragma once

#include <expected>
#include <functional>
#include <memory>
#include <string_view>
#include <print>
#include <cstdio>

namespace rz {
enum class STATUS {
  RZ_ERROR = 0,
  RZ_SUCCESS,
};

using logCB = std::function<void(std::string_view)>;
inline constexpr auto emptyCB = [](std::string_view) {};
inline constexpr auto stdoutCB = [](std::string_view _log) { std::println("{}", _log); };
inline constexpr auto stderrCB = [](std::string_view _log) { std::println(stderr, "{}", _log); };

template <typename T>
using EXPECTED_UPTR = std::expected<std::unique_ptr<T>, STATUS>;

template <typename T>
using EXPECTED_SPTR = std::expected<std::shared_ptr<T>, STATUS>;

template <typename T>
using EXPECTED_PTR = std::expected<T*, STATUS>;

template <typename T> using EXPECTED_OBJ = std::expected<T, STATUS>;

} // namespace rz
