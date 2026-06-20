#pragma once

#include <expected>
#include <functional>
#include <memory>
#include <string>

namespace rz {
enum class STATUS {
  RZ_ERROR = 0,
  RZ_SUCCESS,
};

using logCB = std::function<void(const std::string &)>;
inline constexpr auto emptyCB = [](const std::string &) {};

template <typename T>
using EXPECTED_UPTR = std::expected<std::unique_ptr<T>, STATUS>;

template <typename T>
using EXPECTED_SPTR = std::expected<std::shared_ptr<T>, STATUS>;

template <typename T>
using EXPECTED_PTR = std::expected<T*, STATUS>;

template <typename T> using EXPECTED_OBJ = std::expected<T, STATUS>;

} // namespace rz
