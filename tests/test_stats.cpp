#include "core/stats.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <array>

using Catch::Matchers::WithinAbs;

TEST_CASE("mean of empty input is nullopt", "[stats]") {
  CHECK_FALSE(core::mean({}).has_value());
}

TEST_CASE("mean averages the values", "[stats]") {
  constexpr std::array values{1.0, 2.0, 3.0, 4.0};
  const auto result = core::mean(values);
  REQUIRE(result.has_value());
  CHECK_THAT(result.value_or(0.0), WithinAbs(2.5, 1e-12));
}

TEST_CASE("median of empty input is nullopt", "[stats]") {
  CHECK_FALSE(core::median({}).has_value());
}

TEST_CASE("median picks the middle value", "[stats]") {
  SECTION("odd count, unsorted input") {
    constexpr std::array values{5.0, 1.0, 3.0};
    CHECK(core::median(values) == 3.0);
  }
  SECTION("even count averages the two middle values") {
    constexpr std::array values{4.0, 1.0, 3.0, 2.0};
    CHECK(core::median(values) == 2.5);
  }
}
