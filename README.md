# ulid

![ULID Spec](https://github.com/ulid/spec)

Putting a new interface on [suyash/ulid](https://github.com/suyash/ulid).

## Limitations

Requires support for `__uint128_t`.

- [Usage](#usage)
- [API](#api)
- [Benchmarks](#benchmarks)

## Usage

```c++
#include <ulid/ulid.h>

...

auto generator = ulid::now_random_generator();
auto id = generator.now();
std::cout << ulid::to_string(id) << std::endl;
```

## API

### ulid::ulid

The wrapper type for a `__uint128_t` / 16 byte array representing a ulid.

### ulid::now_random_generator

Generator to generate ulid's based off the current system clock.

### ulid::now_random_generator::now

Generates a ulid based off the current system clock.

## Benchmarks

Apple clang version 15.0.0 (clang-1500.1.0.2.5)

```
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ulid_benchmark is a Catch2 v3.4.0 host application.
Run with -? for options

-------------------------------------------------------------------------------
Benchmark now_random_generator
-------------------------------------------------------------------------------
ulid/ulid_benchmark.cc:7
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
ulid::now_random_generator::now()              100           155      4.588 ms 
                                        314.696 ns    296.227 ns    342.044 ns 
                                        113.594 ns    84.4111 ns     149.47 ns 
                                                                               
ulid::from_string()                            100          2776     4.4416 ms 
                                        13.8779 ns    13.8636 ns    13.9348 ns 
                                       0.133053 ns  0.0160179 ns   0.315292 ns 
                                                                               
ulid::to_string()                              100           518     4.5584 ms 
                                        70.9005 ns    69.4134 ns     76.426 ns 
                                         12.664 ns    3.07345 ns    28.8345 ns 
                                                                               

===============================================================================
test cases: 1 | 1 passed
assertions: - none -
```
