#ifndef ULID_H
#define ULID_H

#include <cstdint>
#include <functional>
#include <iostream>
#include <chrono>
#include <string>
#include <random>

/// @brief Defines the ulid api
///
/// Quick guide
/// -----------
///
/// auto ulid_generator = ulid::now_random_generator();
/// auto id = ulid_generator.now();
///
namespace ulid {

using ulid = __uint128_t;

char constexpr crockfords_base32_chars[] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'M',
    'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Y', 'Z'
};

/// now_random_generator
///
/// @brief Generates ulid's using the current time and a random generator.
///
/// The random generator is a random distribution of the crockford's base32
/// characters.
///
struct now_random_generator {
    /// ctors
    now_random_generator() = default;

    ulid now() noexcept;

  private:
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<> distrib{0, std::size(crockfords_base32_chars)};
};

/// to_string
void to_string(ulid const& ulid, char dst[26]);
std::string to_string(ulid const& id);

/// from_string
void from_string(char const str[26], ulid& id);
ulid from_string(std::string const& str);

}  // namespace ulid

#endif // ULID_H