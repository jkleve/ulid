#include <iostream>

#include "ulid/ulid.h"

int main()
{
    auto generator = ulid::now_random_generator();
    auto id = generator.now();
    std::cout << ulid::to_string(id) << std::endl;

    return 0;
}