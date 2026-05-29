# Examples

This directory contains a small example for checking a sorting solution with
StressHub.

## Files

- `gen.cpp` generates a random vector.
- `slow.cpp` is the trusted solution. It sorts the vector with `std::sort`.
- `fast.cpp` is the solution being tested. It is intentionally unreliable, so
  StressHub can find a failing test.

## Run

From the project root:

```bash
g++ -std=c++17 src/main.cpp -o stressHub
./stressHub examples/gen.cpp examples/slow.cpp examples/fast.cpp 100
```

If the outputs are different, the failing input and both outputs will be saved
to `failed_tests/`.
