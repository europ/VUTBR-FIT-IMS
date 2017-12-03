#include "file_data.hpp"

#include <sstream>
#include <fstream>

street street_load(std::string str) {

    std::string value;
    std::stringstream ss(str);

    unsigned int bin_small_count;
    unsigned int bin_large_count;
    double       street_length;        

    unsigned int i = 0;
    while (std::getline(ss, value, '\t')) {

        if (i == 0)
            bin_small_count = (unsigned)std::stoi(value);
        else if (i == 1)
            bin_large_count = (unsigned)std::stoi(value);
        else if (i == 2)
            street_length = std::stod(value);
        else
            break;

        i++;
    }

    return street_init(bin_small_count, bin_large_count, street_length);
}

std::vector<street> load_tsv_file(std::string filename) {

    std::vector<street> vec;

    std::ifstream file;
    file.open(filename);

    if(file.good()) {

        std::string line;

        while (std::getline(file, line)) {
            vec.push_back(street_load(line));
        }

    }

    return vec;
}
