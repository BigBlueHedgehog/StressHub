# StressHub

StressHub is a small C++17 command-line tool for stress testing solutions.
It repeatedly generates tests, runs two solutions on the same input, and
compares their output token by token.

The usual setup is:

- `gen.cpp` generates one random test.
- `slow.cpp` is a trusted, usually simpler solution.
- `fast.cpp` is the solution being checked.

If the outputs differ, StressHub prints the failing case and saves the input,
expected output, and actual output in `failed_tests/`.

## Build

Build the tool with:

```bash
make
```

This creates the executable:

```text
./stresshub
```

Equivalent manual build command:

```bash
g++ -std=c++17 -Wall -Wextra -Iinclude \
  src/main.cpp src/config.cpp src/compiler.cpp src/runner.cpp \
  -o stresshub
```

## Usage

```bash
./stresshub <generator> <slow_solution> <fast_solution> <test_count>
```

Example:

```bash
./stresshub examples/gen.cpp examples/slow.cpp examples/fast.cpp 100
```

StressHub will compile the three provided programs, then run:

1. the generator to produce `tmp/input.txt`;
2. the slow solution to produce the expected answer;
3. the fast solution to produce the answer being checked.

When all tests pass, the output looks like:

```text
Test 1 : OK
Test 2 : OK
...
All tests passed :)
```

When a mismatch is found, StressHub saves:

- `failed_tests/test_<n>.in` - generated input;
- `failed_tests/expected_<n>.out` - output from the trusted solution;
- `failed_tests/got_<n>.out` - output from the checked solution.

## Examples

The `examples/` directory contains a small sorting test:

- `examples/gen.cpp` generates a random array;
- `examples/slow.cpp` sorts it correctly with `std::sort`;
- `examples/fast.cpp` uses an intentionally limited sorting routine.

Run a passing smoke test with:

```bash
make run
```

This compares `examples/slow.cpp` with itself.

To see StressHub catch a wrong answer, run:

```bash
make demo-fail
```

or manually:

```bash
./stresshub examples/gen.cpp examples/slow.cpp examples/fast.cpp 100
```

This command is expected to stop when it finds a mismatch and return a non-zero
exit code.

## Clean

Remove the built executable and temporary files:

```bash
make clean
```

## Notes

- The tested programs are compiled with `g++`.
- Output is compared token by token, so extra spaces and line breaks do not
  affect the comparison.
- Temporary files are written to `tmp/`.
