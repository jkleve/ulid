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
ulid::now_random_generator::now()              100           149      4.321 ms 
                                        275.424 ns    272.456 ns    287.025 ns 
                                        27.2423 ns     4.0894 ns    64.2933 ns 
                                                                               
ulid::from_string()                            100          3081     4.0053 ms 
                                        17.1893 ns    15.9926 ns    18.7415 ns 
                                        6.95869 ns    5.68075 ns    8.35291 ns 
                                                                               
ulid::to_string()                              100           570      4.275 ms 
                                        71.1015 ns    69.4857 ns    75.0115 ns 
                                        11.9934 ns    5.84828 ns    22.6972 ns 
                                                                               

===============================================================================
test cases: 1 | 1 passed
assertions: - none -
```
