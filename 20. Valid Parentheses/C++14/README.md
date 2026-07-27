# 20. Valid Parentheses - C++14

LeetCode problem 20: Valid Parentheses solution in C++14.

## Algorithm

This solution uses a stack-based approach:
- Time Complexity: O(n) - Each character is processed exactly once
- Space Complexity: O(n) - In the worst case, all characters are opening brackets

## Two Ways to Run

### Option 1: Standalone (g++)

Compile and run the standalone file directly:

```bash
make run     # Compile and run (includes tests)
make test    # Same as run
```

The standalone file is: `valid_parentheses.cpp`

### Option 2: CMake + vcpkg (Google Test)

#### Prerequisites

1. Install vcpkg:
   ```bash
   git clone https://github.com/microsoft/vcpkg.git
   cd vcpkg && ./bootstrap-vcpkg.sh
   ```

2. Configure CMake with vcpkg:
   ```bash
   cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=[vcpkg-root]/scripts/buildsystems/vcpkg.cmake
   ```

3. Build and run tests:
   ```bash
   cmake --build build
   cd build && ctest --output-on-failure
   ```

Or use the Makefile shortcut:

```bash
make cmake_config    # Configure CMake
make cmake_build     # Build the project
make cmake_test      # Run tests
```

## Cleanup

```bash
make clean           # Remove standalone binary
make cmake_clean     # Remove CMake build directory
```

## Examples

| Input | Output |
|-------|--------|
| `"()"` | `true` |
| `"()[]{}"` | `true` |
| `"(]"` | `false` |
| `"([])"` | `true` |
| `"([)]"` | `false` |
