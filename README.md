# StressHub

StressHub is a small C++ tool for stress testing solutions. It runs three
programs on the same generated tests:

- `gen.cpp` generates a random input test.
- `slow.cpp` is a simple trusted solution.
- `fast.cpp` is the solution you want to check.

If `slow.cpp` and `fast.cpp` produce different output, StressHub prints the
failing test and saves it to `failed_tests/`.

## Build

```bash
g++ -std=c++17 src/main.cpp -o stressHub
```

## Usage

```bash
./stressHub examples/gen.cpp examples/slow.cpp examples/fast.cpp 100
```

Command format:

```text
./stressHub <generator> <slow_solution> <fast_solution> <test_count>
```

Example output when all tests pass:

```text
Test 1 : OK
Test 2 : OK
...
All tests passed :)
```

When a mismatch is found, StressHub saves:

- `failed_tests/test_<n>.in` - generated input.
- `failed_tests/expected_<n>.out` - output from the trusted solution.
- `failed_tests/got_<n>.out` - output from the checked solution.

## Example

The `examples/` directory contains a simple sorting task:

- `examples/gen.cpp` generates a random vector.
- `examples/slow.cpp` sorts it with `std::sort`.
- `examples/fast.cpp` contains an intentionally unreliable implementation.

Run it with:

```bash
./stressHub examples/gen.cpp examples/slow.cpp examples/fast.cpp 100
```

## Notes

- All three programs are compiled with `g++`.
- Output is compared token by token, so extra spaces and line breaks do not
  affect the result.
- Temporary files are written to `tmp/`.
