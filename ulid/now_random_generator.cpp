#include "ulid/ulid.h"

#include <chrono>

namespace ulid {

now_random_generator::now_random_generator()
    // : _generator()
{}

ulid now_random_generator::now() noexcept
{
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
    // using std::chrono;
    // auto now = duration_cast<milliseconds>(steady_clock::now());
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


}  // namespace ulid