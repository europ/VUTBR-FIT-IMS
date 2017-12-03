#include <iostream>
#include <vector>

#include "simlib.h"

#include "macros.hpp"
#include "constants.hpp"
#include "data_types.hpp"
#include "file_data.hpp"


int main(int argc, char* argv[]) {

    (void)argc; // -Wunused-parameter    
    (void)argv; // -Wunused-parameter

    std::vector<street> streets_1 = load_tsv_file(FILE_PATH_OF_DATA_1);

    PRINT_STREET_VECTOR(streets_1);

    return 0;
}
