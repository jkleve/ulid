#ifndef ULID_INTERNAL_ENCODE_H
#define ULID_INTERNAL_ENCODE_H

#include <chrono>

#include "ulid/ulid.h"

namespace ulid::internal {

void encode_time(ulid& id);
void encode_entropy(std::function<std::uint8_t()> const& rng, ulid& id);

}  // namespace ulid::internal

#endif  // ULID_INTERNAL_ENCODE_H