# libduck

[![CI](https://github.com/duckenclaw/libduck-cpp/actions/workflows/ci.yml/badge.svg)](https://github.com/duckenclaw/libduck-cpp/actions/workflows/ci.yml)

A small C++20 library of hand-rolled containers, allocators and concurrency primitives, built to learn how the standard library does it.

## Components

| Component | Description | Status |
| --- | --- | --- |
| `Span<T>` / `StringView` | non-owning views over contiguous memory and strings, plus `split` | coming soon |
| `File` | move-only RAII file handle, optionally memory-mapped | coming soon |
| `Vector<T>` | growable array with the strong exception guarantee | coming soon |
| `HashMap<K,V>` | open addressing with linear probing and tombstones | coming soon |
| `Arena` / `Pool` | bump and free-list allocators, usable as `std::pmr::memory_resource` | coming soon |
| `SpscRing<T, N>` | lock-free single-producer/single-consumer ring buffer | coming soon |
| `ThreadPool` | fixed worker pool returning `std::future`s | coming soon |
| `wordfreq` | parallel word-frequency CLI that uses every component | coming soon |

## Building

```bash
cmake --workflow --preset dev
```

Other presets: `release`, `asan` (ASan + UBSan), `tsan` (ThreadSanitizer), `lint` (clang-tidy) and `bench`.

## Benchmarks

Benchmarks use [Google Benchmark](https://github.com/google/benchmark) and are only built in Release:

```bash
cmake --workflow --preset bench
./build/bench/bench/duck_bench
```

CI uploads the results as JSON on every run. Tables will appear here as components land.
