#include <iostream>
#include <vector>

#include "simlib.h"

#include "constants.hpp"
#include "data_types.hpp"
#include "file_data.hpp"


int main(int argc, char* argv[]) {

    (void)argc; // -Wunused-parameter    
    (void)argv; // -Wunused-parameter

    std::vector<street> vec = load_tsv_file(DATA_PATH_1);
    PRINT_STREET_VECTOR(vec);

    return 0;
}
