#ifndef __constatns_hpp
#define __constatns_hpp

#include <time.h>

#define SEED time(NULL)

#define CAR_COUNT 2 // testing purposes

#define FILE_PATH_OF_DATA_1 "../data/sim_2_cars/ulice1.tsv" // file path to ulice1.tsv
#define FILE_PATH_OF_DATA_2 "../data/sim_2_cars/ulice2.tsv" // file path to ulice2.tsv


#define FILE_PATH_OF_DATA_3 "../data/sim_3_cars/ulice1.tsv" // file path to ulice1.tsv
#define FILE_PATH_OF_DATA_4 "../data/sim_3_cars/ulice2.tsv" // file path to ulice2.tsv
#define FILE_PATH_OF_DATA_5 "../data/sim_3_cars/ulice3.tsv" // file path to ulice1.tsv



#define BIN_SMALL_MIN_KG 10 // half of max avg. weight of trash [kg]
#define BIN_SMALL_MAX_KG 40 // max avg. weight of trash [kg]

#define BIN_LARGE_MIN_KG 100 // half of max capacity [kg]
#define BIN_LARGE_MAX_KG 150 // max avg. weight of trash [kg]

#define CAR_CAPACITY_KG 10000 // max capacity [kg]
#define CAR_AVERAGE_SPEED 20  // average speed [km/h]
#define CAR_FUEL_CONSUMPTION_PER_KM 0.7 // consumption liter per kilometer [liter]

#define PRICE_FUEL_PER_LITER 1.10 // price of 1 liter of fuel [€]

#define DUMP_DISTANCE 27 // dump distance from town [km]

#endif
