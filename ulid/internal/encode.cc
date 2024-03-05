#include "ulid/internal/encode.hh"

namespace ulid::internal {

void encode_time(ulid& id)
{
    using namespace std::chrono;
    auto const now = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
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
	id = t | (id & mask);
}

void encode_entropy(std::function<std::uint8_t()> const& rng, ulid& id)
{
	id = (id >> 80) << 80;

	ulid e = rng();

	e <<= 8;
	e |= rng();

	e <<= 8;
	e |= rng();

	e <<= 8;
	e |= rng();

	e <<= 8;
	e |= rng();

	e <<= 8;
	e |= rng();

	e <<= 8;
	e |= rng();

	e <<= 8;
	e |= rng();

	e <<= 8;
	e |= rng();

	e <<= 8;
	e |= rng();

	id |= e;
}

}  // namespace ulid::internal