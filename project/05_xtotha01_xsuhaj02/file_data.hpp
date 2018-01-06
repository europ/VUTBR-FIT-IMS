#ifndef __file_data_hpp
#define __file_data_hpp

#include <vector>
#include <string>

#include "data_types.hpp"

street street_load(std::string str);

std::vector<street> load_tsv_file(std::string filename);

#endif
