# cpp-ci-template

[![CI](https://github.com/duckenclaw/cpp-ci-template/actions/workflows/ci.yml/badge.svg)](https://github.com/duckenclaw/cpp-ci-template/actions/workflows/ci.yml)

Starter for C++ pet projects: CMake presets, Catch2 v3 + CTest, clang-format, clang-tidy,
ASan/UBSan, ccache, and a GitHub Actions matrix on Linux, macOS and Windows.

## Quick start

```bash
cmake --workflow --preset dev
```

After the first build, `ctest --preset dev` re-runs the tests on their own. Built trees land in `build/<preset>/`.

## Tooling

macOS:

```bash
brew install cmake ninja ccache pipx
pipx install clang-format==22.1.8 && pipx install clang-tidy==22.1.8
```

The pinned clang-format/clang-tidy versions match CI (see `env:` in
[`.github/workflows/ci.yml`](.github/workflows/ci.yml)), so local results equal CI results.

```bash
clang-format -i $(git ls-files '*.cpp' '*.hpp')
cmake --workflow --preset lint
```

ccache is picked up automatically when it is on `PATH`.

## Layout

```
src/core/       library code (header-only RingBuffer, stats.cpp)
src/main.cpp    small CLI linked against core: `echo 1 2 3 | build/dev/src/app`
tests/          Catch2 tests; every TEST_CASE is registered with CTest
cmake/          warnings, sanitizers, ccache, clang-tidy helpers
```

## Tests

- **Example-based tests**: `tests/test_ring_buffer.cpp`, `tests/test_stats.cpp`.
- **Property-based test**: `tests/test_ring_buffer_properties.cpp` drives `RingBuffer` with
  random operation sequences and compares every step against a `std::deque` reference model.
  When it fails, the output shows `Randomness seeded to: N`. Reproduce it with:

  ```bash
  ./build/dev/tests/unit_tests "[property]" --rng-seed N
  ```

## CI

`.github/workflows/ci.yml` runs on every push and pull request:

| Job           | Runs on                                                       |
|---------------|---------------------------------------------------------------|
| clang-format  | Ubuntu                                                        |
| clang-tidy    | Ubuntu, Clang (`lint` preset)                                 |
| build-test    | Linux GCC, Linux Clang, macOS AppleClang, Windows MSVC (`dev`) |
| ASan + UBSan  | Ubuntu, Clang (`asan` preset)                                 |

## Start a new project from this template

1. On GitHub, click **Use this template** → **Create a new repository**.
2. Rename the project in the root `CMakeLists.txt` (`project(cpp_ci_template ...)`).
3. Update the badge URL at the top of this README to the new repo.
4. Replace the example code in `src/` and `tests/`, and rename the `core`/`app` targets if you like.
5. Push and confirm all CI jobs go green.

