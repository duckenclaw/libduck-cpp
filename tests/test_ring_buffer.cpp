#include "core/ring_buffer.hpp"

#include <catch2/catch_test_macros.hpp>

#include <stdexcept>
#include <string>

using core::RingBuffer;

TEST_CASE("RingBuffer rejects zero capacity", "[ring_buffer]") {
  REQUIRE_THROWS_AS(RingBuffer<int>(0), std::invalid_argument);
}

TEST_CASE("RingBuffer starts empty", "[ring_buffer]") {
  const RingBuffer<int> buffer(3);
  CHECK(buffer.empty());
  CHECK_FALSE(buffer.full());
  CHECK(buffer.size() == 0);
  CHECK(buffer.capacity() == 3);
  CHECK(buffer.front() == nullptr);
}

TEST_CASE("RingBuffer is first-in first-out", "[ring_buffer]") {
  RingBuffer<std::string> buffer(3);
  REQUIRE(buffer.push("a"));
  REQUIRE(buffer.push("b"));

  REQUIRE(buffer.front() != nullptr);
  CHECK(*buffer.front() == "a");
  CHECK(buffer.pop() == "a");
  CHECK(buffer.pop() == "b");
  CHECK_FALSE(buffer.pop().has_value());
}

TEST_CASE("RingBuffer refuses pushes when full", "[ring_buffer]") {
  RingBuffer<int> buffer(2);
  REQUIRE(buffer.push(1));
  REQUIRE(buffer.push(2));

  CHECK(buffer.full());
  CHECK_FALSE(buffer.push(3));
  CHECK(buffer.size() == 2);
  CHECK(buffer.pop() == 1);
}

TEST_CASE("RingBuffer wraps around its storage", "[ring_buffer]") {
  RingBuffer<int> buffer(2);
  for (int i = 0; i < 10; ++i) {
    REQUIRE(buffer.push(i));
    REQUIRE(buffer.pop() == i);
  }
  CHECK(buffer.empty());
}
