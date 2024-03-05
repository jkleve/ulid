#include "ulid/ulid.h"
#include <iostream>

#include "catch2/catch_test_macros.hpp"
#include "catch2/benchmark/catch_benchmark.hpp"

TEST_CASE("Benchmark now_random_generator", "[benchmark]") {
    BENCHMARK_ADVANCED("ulid::now_random_generator::now()")(Catch::Benchmark::Chronometer meter) {
        ulid::now_random_generator generator{};
        meter.measure([&] {
            return generator.now();
        });
    };

    BENCHMARK_ADVANCED("ulid::from_string()")(Catch::Benchmark::Chronometer meter) {
        std::string str{"01H6VCEPN30000000000000000"};
        meter.measure([&] {
            return ulid::from_string(str);
        });
    };

    BENCHMARK_ADVANCED("ulid::to_string()")(Catch::Benchmark::Chronometer meter) {
        ulid::ulid id{ulid::from_string("01H6VCEPN30000000000000000")};
        meter.measure([&] {
            return ulid::to_string(id++);
        });
    };
}