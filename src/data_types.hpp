#ifndef __data_types_hpp
#define __data_types_hpp

typedef struct struct_street {

    int bin_small_count; // 120  liter bins  [count]
    int bin_large_count; // 1100 liter bins  [count]
    double street_length;         // length of street [kilometers]
    bool done;

} street;

street street_init(unsigned int bin_small_count, unsigned int bin_large_count, double street_length);

#endif
