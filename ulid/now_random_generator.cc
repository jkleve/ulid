#include <chrono>

#include "ulid/ulid.h"
#include "ulid/internal/encode.hh"

namespace ulid {

ulid now_random_generator::now() noexcept
{
    ulid ulid{};
    internal::encode_time(ulid);
    internal::encode_entropy([this] { return distrib(gen); }, ulid);
    return ulid;
}

}  // namespace ulid