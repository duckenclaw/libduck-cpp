#pragma once

#include <cstddef>
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>

namespace core {

template <typename T>
class RingBuffer {
public:
  explicit RingBuffer(std::size_t capacity) : slots_(capacity) {
    if (capacity == 0) {
      throw std::invalid_argument("RingBuffer capacity must be greater than zero");
    }
  }

  [[nodiscard]] bool push(T value) {
    if (full()) {
      return false;
    }
    slots_[(head_ + size_) % capacity()] = std::move(value);
    ++size_;
    return true;
  }

  [[nodiscard]] std::optional<T> pop() {
    if (empty()) {
      return std::nullopt;
    }
    T value = std::move(slots_[head_]);
    head_ = (head_ + 1) % capacity();
    --size_;
    return value;
  }

  [[nodiscard]] const T* front() const { return empty() ? nullptr : &slots_[head_]; }

  [[nodiscard]] std::size_t size() const { return size_; }
  [[nodiscard]] std::size_t capacity() const { return slots_.size(); }
  [[nodiscard]] bool empty() const { return size_ == 0; }
  [[nodiscard]] bool full() const { return size_ == capacity(); }

private:
  std::vector<T> slots_;
  std::size_t head_ = 0;
  std::size_t size_ = 0;
};

} // namespace core
