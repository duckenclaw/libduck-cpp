#include "core/stats.hpp"

#include <charconv>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <iterator>
#include <optional>
#include <string>
#include <system_error>
#include <vector>

namespace {

std::optional<double> parse_number(const std::string& text) {
  double value = 0.0;
  const char* const first = text.data();
  const char* const last = std::next(first, std::ssize(text));
  const auto [ptr, ec] = std::from_chars(first, last, value);
  if (ec != std::errc{} || ptr != last) {
    return std::nullopt;
  }
  return value;
}

// reads numbers from stdin and prints their mean and median.
int run() {
  std::vector<double> values;
  for (std::string token; std::cin >> token;) {
    const auto value = parse_number(token);
    if (!value) {
      std::cerr << "not a number: " << token << '\n';
      return EXIT_FAILURE;
    }
    values.push_back(*value);
  }

  const auto avg = core::mean(values);
  const auto mid = core::median(values);
  if (!avg || !mid) {
    std::cerr << "usage: echo 1 2 3 | app\n";
    return EXIT_FAILURE;
  }

  std::cout << "count:  " << values.size() << '\n'
            << "mean:   " << *avg << '\n'
            << "median: " << *mid << '\n';
  return EXIT_SUCCESS;
}

} // namespace

int main() {
  try {
    return run();
  } catch (const std::exception& e) {
    static_cast<void>(std::fputs(e.what(), stderr));
    return EXIT_FAILURE;
  } catch (...) {
    return EXIT_FAILURE;
  }
}
