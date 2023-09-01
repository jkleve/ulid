// #include "ulid.h"
#include "ulid/ulid.h"
#include <iostream>

#include "catch2/catch_test_macros.hpp"

// ulid
// base32
// you count from 0 to 32, athought the
// numbers skip quite a few numbers.
//
// each symbol carries 5 bits.
//
// 26 character string.
//
//   01AN4Z07BY      79KA1307SR9X4MV3
//  |----------|    |----------------|
//   Timestamp          Randomness
//     48bits             80bits
//    10 chars           16 chars
// 
// 10 chars x 8 bits per = 80 bits = 8 bytes
// 80 bits / 5 bits per = 16 "chars"
//
// 16 chars x 8 bits per = 128 bits = 16 bytes
//
// 0 1 2 3 4 5 6 7 8 9 A B C D E F G
//
//  1  2  3  4  5  6  7  8  9 10 11 12 13
// 01 H6 Z2 ED 0Z WV HS 0H V4 K3 AV XR Z2
//
// time
//    1    2    3   4   5   6   7   7    8   9    10   11   12
// 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 
// 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 

TEST_CASE("Test ulid now")
{
    // ulid::string_generator gen{};

    SECTION("Nominal")
    {
        auto id = ulid::from_string("01H6VCEPN30000000000000000");
        CHECK(ulid::to_string(id) == "01H6VCEPN30000000000000000");
    }

    SECTION("Test maximum")
    {
        auto id = ulid::from_string("7ZZZZZZZZZZZZZZZZZZZZZZZZZ");
        CHECK(ulid::to_string(id) == "7ZZZZZZZZZZZZZZZZZZZZZZZZZ");
    }

    SECTION("Test outside range")
    {
        auto id = ulid::from_string("8ZZZZZZZZZZZZZZZZZZZZZZZZZ");
        CHECK(ulid::to_string(id) == "0ZZZZZZZZZZZZZZZZZZZZZZZZZ");
    }
}

TEST_CASE("Test now_random_generator")
{
    SECTION("Test now")
    {
        auto generator = ulid::now_random_generator();
        // @todo get now and ensure we within a few seconds
        auto id = generator.now();
        std::cout << ulid::to_string(id) << std::endl;
        CHECK(id > 0ULL);
    }
}