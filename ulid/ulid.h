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
	using generator_type = std::function<uint8_t()>;

	/// ctors
	now_random_generator();
	// explicit now_random_generator(generator_type generator);

	ulid now() noexcept;

  private:
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<> distrib{0, std::size(crockfords_base32_chars)};

	// generator_type _generator;
};

// inline ulid now() {
//     return ulid::internal::
// }

namespace details {
    ulid generate(std::function<uint8_t()>& gen);
}

/// int_generator
///
/// @code[.cpp]
///
///   int_generator gen;
///   auto id = gen();
///
template <typename GeneratorType>
struct int_generator {
    using result_type = ulid;

    int_generator(GeneratorType gen) : _gen(std::move(gen)) {}

    result_type operator()() noexcept {
        return details::generate(_gen);
    }

  private:
    GeneratorType _gen;
};

struct random_generator {
    using result_type = ulid;
    using generator_type = std::function<uint8_t()>;

    random_generator();
    explicit random_generator(generator_type gen);

    result_type operator()() noexcept;

  private:
    generator_type _gen;
};

struct string_generator {
    using result_type = ulid;

    template <typename ch, typename char_traits, typename alloc>
    result_type operator()(std::basic_string<ch, char_traits, alloc> const& s) const {
        // return ulid::internal::string_gen(s);
        using namespace std::chrono;

        auto const now = time_point_cast<milliseconds>(steady_clock::now()).time_since_epoch().count();
	    ulid t = static_cast<uint8_t>(now >> 40);
	    t <<= 8;
	    t |= static_cast<uint8_t>(now >> 32);
	    t <<= 8;
	    t |= static_cast<uint8_t>(now >> 24);
	    t <<= 8;
	    t |= static_cast<uint8_t>(now >> 16);
	    t <<= 8;
	    t |= static_cast<uint8_t>(now >> 8);
	    t <<= 8;
	    t |= static_cast<uint8_t>(now);
	    t <<= 80;

	    ulid mask = 1;
	    mask <<= 80;
	    mask--;

        ulid ulid{};
	    ulid = t | (ulid & mask);
        return ulid;
    }
};

/// to_string
void marshal_to(ulid const& ulid, char dst[26]);
std::string to_string(ulid const& id);

/// from_string
void unmarshal_from(char const str[26], ulid& id);
ulid from_string(std::string const& str);

}  // namespace ulid

#endif // ULID_H