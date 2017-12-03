#include "file_data.hpp"

#include <sstream>
#include <fstream>

street street_load(std::string str) {

    std::string value;
    std::stringstream ss(str);
    std::vector<unsigned int> vec;

    unsigned int i = 0;
    while (std::getline(ss, value, '\t')) {
        if (i == 3) break;
        vec.push_back((unsigned)std::stoi(value));
        i++;
    }

    return street_init(vec[0],vec[1],vec[2]);
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
