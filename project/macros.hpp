#ifndef __macros_hpp
#define __macros_hpp

// STRING ===========================================================================

#define ECHO() std::cout << std::endl;

#define PRINT(data) std::cout << data << std::endl;

#define PRINTLN(data) std::cout << data << std::endl << std::endl;

#define PRINT_VEC(vector) {                                       \
    for (auto i = vector.begin(); i != vector.end(); ++i) {       \
        std::cout << *i << std::endl;                             \
        if (std::next(i) != vector.end()) std::cout << std::endl; \
    }                                                             \
}

// STREET ===========================================================================

#define PRINT_STREET(s) {                                                \
    std::cout << "bin_small_count = " << s.bin_small_count << std::endl  \
              << "bin_large_count = " << s.bin_large_count << std::endl  \
              << "street_length   = " << s.street_length   << std::endl; \
}

#define PRINT_STREET_VECTOR(vector) {                                           \
    for (auto i = vector.begin(); i != vector.end(); ++i) {                     \
        std::cout << "bin_small_count = " << (*i).bin_small_count << std::endl  \
                  << "bin_large_count = " << (*i).bin_large_count << std::endl  \
                  << "street_length   = " << (*i).street_length   << std::endl; \
        if (std::next(i) != vector.end()) std::cout << std::endl;               \
    }                                                                           \
}

#endif
