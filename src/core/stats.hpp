#pragma once

#include <optional>
#include <span>

namespace core {

// Arithmetic mean, or std::nullopt for an empty input.
[[nodiscard]] std::optional<double> mean(std::span<const double> values);

// Median (average of the two middle values for even sizes), or std::nullopt for an empty input.
[[nodiscard]] std::optional<double> median(std::span<const double> values);

} // namespace core
