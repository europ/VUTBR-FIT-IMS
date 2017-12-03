#include <iostream>
#include <vector>

#include "simlib.h"

#include "macros.hpp"
#include "constants.hpp"
#include "data_types.hpp"
#include "file_data.hpp"

unsigned int gv_car_count = 0; // global variable car count


class Car : public Process {

	void Behavior() {
		PRINT("Car.Behavior()");
	}

};


class Generator : public Event {

    void Behavior() {
		for(; gv_car_count<CAR_COUNT; gv_car_count++) {
			(new Car)->Activate();
        	Activate(Time);
		}
    }

};


int main(int argc, char* argv[]) {

    (void)argc; // -Wunused-parameter
    (void)argv; // -Wunused-parameter

    //RandomSeed(time(NULL));

    Init(0);
    (new Generator)->Activate();
    Run();

    // TODO remove
    //std::vector<street> streets_1 = load_tsv_file(FILE_PATH_OF_DATA_1);
    //PRINT_STREET_VECTOR(streets_1);

    return 0;
}
