To implement: `mini_stl::vector`.
# Spec

#### General

 | Member Function | Status | 
|---------------|----------- |
|Constructors | ✅ |
|Destructor | ✅ |
|`operator=` (copy)| ✅ |
|`operator=` (move)| ✅ |
|`assign`| |
|`assign_range`| |
|`get_allocator`| ✅ |


#### Element Access

| Member Function | Status | 
|---------------|----------- |
|`at` | ✅ |
|`operator[]` | ✅ |
|`front`| ✅ |
|`back`| ✅ |
|`data`| ✅ |

#### Iterators
| Member Function | Status | 
|---------------|----------- |
|`begin`/`cbegin` | ✅ |
|`end`/`cend` | ✅|
|`rbegin`/`rend`| ✅|
|`rend`/`cend`| ✅|

#### Capacity

| Member Function | Status | 
|---------------|----------- |
|`empty` | ✅|
|`size`| ✅|
|`max_size`| ✅|
|`reserve`| ✅|
|`capacity`| ✅|
|`shrink_to_fit`| ✅|

#### Modifiers
| Member Function | Status | 
|---------------|----------- |
|`clear` | |
|`insert`| |
|`insert_range`| |
|`emplace`| |
|`erase`| |
|`push_back`| ✅|
|`emplace`| ✅|
|`emplace_back`| ✅|
|`append_range`| |
|`pop_back`| |
|`resize`| |
|`swap`| ✅|

# Notes
I'm not really consistent about using `constexpr`.

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


