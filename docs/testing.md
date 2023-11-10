Can make use a C++ testing framework like Google Test/Catch2 or write from scratch.

# Testing Harness
Testing framework to write tests. For correctness and memory safety. For performance, let's use Google Benchmark.
- Allows for creation/registration of individual tests, grouping tests into modules, and testing modules via command line.
- Compile with Valgrind/address sanitizer to check for memory leaks and buffer underflows/overflows.
- Would be nice to handle input/output or inspect resulting ostream object to verify that test finished as expected. Test could dump output into dedicated string stream, can compile with std vector to generate expected results (think about this).

# Frameworks
Maybe try these out, but would be fun to write our own harness.
#### Google Test
#### Catch2
#### Google Benchmark
