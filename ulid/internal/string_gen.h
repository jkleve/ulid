#ifndef ULID_INTERNALS_H
#define ULID_INTERNALS_H

#include <chrono>
#include <string>

// #include "ulid_uint128.hh"

namespace ulid::internal {

template <typename ch, typename char_traits, typename alloc>
ulid::ulid now(std::basic_string<ch, char_traits, alloc> const& s) {
    // using namespace std::chrono;
    // auto const now = time_point_cast<milliseconds>(steady_clock::now()).time_since_epoch().count();
	// ulid t = static_cast<uint8_t>(now >> 40);
	// t <<= 8;
	// t |= static_cast<uint8_t>(now >> 32);
	// t <<= 8;
	// t |= static_cast<uint8_t>(now >> 24);
	// t <<= 8;
	// t |= static_cast<uint8_t>(now >> 16);
	// t <<= 8;
	// t |= static_cast<uint8_t>(now >> 8);
	// t <<= 8;
	// t |= static_cast<uint8_t>(now);
	// t <<= 80;

	// ulid mask = 1;
	// mask <<= 80;
	// mask--;

    // ulid ulid{};
	// ulid = t | (ulid & mask);
    // return ulid;
    // auto now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now());
	// ulid::ulid t = static_cast<uint8_t>(now >> 40);
	// t <<= 8;
	// t |= static_cast<uint8_t>(now >> 32);
	// t <<= 8;
	// t |= static_cast<uint8_t>(now >> 24);
	// t <<= 8;
	// t |= static_cast<uint8_t>(now >> 16);
	// t <<= 8;
	// t |= static_cast<uint8_t>(now >> 8);
	// t <<= 8;
	// t |= static_cast<uint8_t>(now);
	// t <<= 80;

	// ulid::ulid mask = 1;
	// mask <<= 80;
	// mask--;

    // ulid::ulid id{};
	// ulid = t | (ulid & mask);
    // return ulid;
}

}  // namespace ulid::internal

#endif  // ULID_INTERNALS_H