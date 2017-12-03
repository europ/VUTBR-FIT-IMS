#ifndef __data_types_hpp
#define __data_types_hpp

typedef struct struct_street {

    unsigned int bin_small_count; // 120 liter
    unsigned int bin_large_count; // 1100 liter
    unsigned int street_length;   // kilometers
    bool done;

} street;

street street_init(unsigned int bin_small_count, unsigned int bin_large_count, unsigned int street_length);

#endif
