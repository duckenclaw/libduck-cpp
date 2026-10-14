#include "core/stats.hpp"

#include <algorithm>
#include <numeric>
#include <vector>

namespace core {

std::optional<double> mean(std::span<const double> values) {
  if (values.empty()) {
    return std::nullopt;
  }
  const double sum = std::accumulate(values.begin(), values.end(), 0.0);
  return sum / static_cast<double>(values.size());
}

std::optional<double> median(std::span<const double> values) {
  if (values.empty()) {
    return std::nullopt;
  }
  std::vector<double> sorted(values.begin(), values.end());
  std::ranges::sort(sorted);
  const auto mid = sorted.size() / 2;
  if (sorted.size() % 2 == 1) {
    return sorted[mid];
  }
  return (sorted[mid - 1] + sorted[mid]) / 2.0;
}

} // namespace core
