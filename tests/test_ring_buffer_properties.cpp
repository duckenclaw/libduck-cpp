// Property-based test: drive RingBuffer with random operation sequences and compare every step
// against a trivially-correct reference model (std::deque plus a capacity check).
//
// The per-case seeds come from Catch2's RNG, so a failure is reproducible with:
//   unit_tests "[property]" --rng-seed <seed printed in the failure header>

#include "core/ring_buffer.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>

#include <cstddef>
#include <cstdint>
#include <deque>
#include <optional>
#include <random>

namespace {

class ReferenceQueue {
public:
  explicit ReferenceQueue(std::size_t capacity) : capacity_(capacity) {}

  bool push(int value) {
    if (items_.size() == capacity_) {
      return false;
    }
    items_.push_back(value);
    return true;
  }

  std::optional<int> pop() {
    if (items_.empty()) {
      return std::nullopt;
    }
    const int value = items_.front();
    items_.pop_front();
    return value;
  }

  [[nodiscard]] const std::deque<int>& items() const { return items_; }
  [[nodiscard]] bool full() const { return items_.size() == capacity_; }

private:
  std::size_t capacity_;
  std::deque<int> items_;
};

} // namespace

TEST_CASE("RingBuffer behaves like a bounded FIFO reference model", "[ring_buffer][property]") {
  constexpr int operation_count = 500;

  const auto seed = GENERATE(take(100, random<std::uint32_t>(0, UINT32_MAX)));
  INFO("case seed: " << seed);

  std::mt19937 rng(seed);
  std::uniform_int_distribution<std::size_t> capacity_dist(1, 8);
  std::uniform_int_distribution<int> op_dist(0, 2);
  std::uniform_int_distribution<int> value_dist(-1000, 1000);

  const std::size_t capacity = capacity_dist(rng);
  INFO("capacity: " << capacity);

  core::RingBuffer<int> actual(capacity);
  ReferenceQueue expected(capacity);

  for (int step = 0; step < operation_count; ++step) {
    INFO("step: " << step);
    switch (op_dist(rng)) {
    case 0:
    case 1: { // bias towards pushes so the buffer regularly fills up
      const int value = value_dist(rng);
      REQUIRE(actual.push(value) == expected.push(value));
      break;
    }
    default:
      REQUIRE(actual.pop() == expected.pop());
      break;
    }

    REQUIRE(actual.size() == expected.items().size());
    REQUIRE(actual.empty() == expected.items().empty());
    REQUIRE(actual.full() == expected.full());
    if (expected.items().empty()) {
      REQUIRE(actual.front() == nullptr);
    } else {
      REQUIRE(actual.front() != nullptr);
      REQUIRE(*actual.front() == expected.items().front());
    }
  }
}
