#ifndef __constatns_hpp
#define __constatns_hpp

#include <time.h>

#define SEED time(NULL)

#define CAR_COUNT 1 // testing purposes

#define FILE_PATH_OF_DATA_1 "../data/ulice1.tsv" // file path to ulice1.tsv
#define FILE_PATH_OF_DATA_2 "../data/ulice2.tsv" // file path to ulice2.tsv

#define BIN_SMALL_MIN_KG 24 // half of max capacity [kg]
#define BIN_SMALL_MAX_KG 48 // max capacity [kg]

#define BIN_LARGE_MIN_KG 150 // half of max capacity [kg]
#define BIN_LARGE_MAX_KG 300 // max capacity [kg]

#define CAR_CAPACITY_KG 10000 // max capacity [kg]
#define CAR_AVERAGE_SPEED 20  // average speed [km/h]
#define CAR_FUEL_CONSUMPTION_PER_KM 0.7 // consumption liter per kilometer [liter]

#define PRICE_FUEL_PER_LITER 1.10 // price of 1 liter of fuel [€]

#define DUMP_DISTANCE 27 // dump distance from town [km]

#endif
