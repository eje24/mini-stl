To implement: `mini_stl::vector`.
# Spec

#### General
 Constructor
 - See constructor [documentation](https://en.cppreference.com/w/cpp/container/vector/vector).
 
 Destructor
 `operator=`
 `assign`
 `assign_range`
 `get_allocator`
#### Element Access
`at`
`operator[]`
`front`
`back`
`data`
#### Iterators
`begin`/`cbegin`
`end`/`cend`
`rbegin`/`crbegin`
`rend`/`crend`
#### Capacity
`empty`
`size`
`max_size`
`reserve`
`capacity`
`shrink_to_fit`
#### Modifiers
`clear`
`insert`
`insert_range`
`emplace`
`erase`
`push_back`
`emplace_back`
`append_range`
`pop_back`
`resize`
`swap`
# Testing
Driven by testing harness.
#### Memory Safety Tests
- Memory leaks
- Buffer overflows/underflows
- Valgrind and AddressSanitizer
- should be done via testing harness, not vector-specific tests
#### Behavioral Tests
- Correct behavior when resizing, appending, etc
- Correct error-handling
#### Performance Tests
- Compare against std::vector, can use Google Benchmark

# Sources
1. https://codereview.stackexchange.com/questions/244787/stdvector-remake
2. https://en.cppreference.com/w/cpp/container/vector


