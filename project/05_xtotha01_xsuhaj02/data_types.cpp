#include "data_types.hpp"

street street_init(unsigned int bin_small_count, unsigned int bin_large_count, double street_length) {

    street s;

    s.bin_small_count = bin_small_count;
    s.bin_large_count = bin_large_count;
    s.street_length = street_length;

    return s;
}
