#include <iostream>
#include <vector>

#include "simlib.h"

#include "macros.hpp"
#include "constants.hpp"
#include "data_types.hpp"
#include "file_data.hpp"

unsigned int gv_car_count = 0; // global variable car count
double gv_kms = 0; //kilometers travelled
double gv_duration = 0;//time of collecting
double gv_kg_oftrash = 0;
double smeti = 0;


class Car : public Process {

	void Behavior() {
		double tmptime;
		std::vector<street> streets_1 = load_tsv_file(FILE_PATH_OF_DATA_1);
		
		//ide auticko
		PRINT("Car.Behavior()");
		
		//cas na vyjazd
		tmptime = Uniform(2.5,3.5);
		gv_duration+= tmptime;
		gv_kms+= 1.5;

		//PRINT_STREET_VECTOR(streets_1);


		checkcapacity:
		//kontrola kapacity
		if(gv_kg_oftrash <= (CAR_CAPACITY_KG-BIN_LARGE_MAX_KG) || gv_kg_oftrash <= (CAR_CAPACITY_KG-BIN_SMALL_MAX_KG)){
			//std::cout << "picsa" << std::endl;
			//std::cout << gv_kg_oftrash << std::endl;
			//kontrola ci su este ulice vobec
			while(streets_1.size() > 0){//ak su ulice
				street tmp_street = streets_1[0];//ziskame z vrocholu ulicu
				

				streets:
				//kym mame kapacitu
				while(gv_kg_oftrash <= (CAR_CAPACITY_KG-BIN_LARGE_MAX_KG) || gv_kg_oftrash <= (CAR_CAPACITY_KG-BIN_SMALL_MAX_KG)){
					//std::cout << gv_kg_oftrash << std::endl;
					//std::cout << "fasz" << std::endl;
					//std::cout << tmp_street.bin_large_count << std::endl;
					//std::cout << tmp_street.bin_small_count << std::endl;
					//::cout << gv_kms << std::endl;

					//vybavili sa kose, mame este kapacitu			
					if(tmp_street.bin_large_count == 0 && tmp_street.bin_small_count == 0){
						streets_1.erase(streets_1.begin());//vyberieme ulicu z vektoru
						break;
					}


					//ak su velke kose a dostatocna kapacita tak sa vyprazdni velky kos
					if(tmp_street.bin_large_count > 0 && gv_kg_oftrash <= (CAR_CAPACITY_KG-BIN_LARGE_MAX_KG)){
						tmptime = Uniform(0.8,1);//vyprazdni kos
						gv_duration += tmptime;//cas
						gv_kg_oftrash += Uniform(BIN_LARGE_MIN_KG,BIN_LARGE_MAX_KG);
						tmp_street.bin_large_count--;
					}
					//ak su male kose  akapacita tak vyprazdni sa maly kos
					else if(tmp_street.bin_small_count > 0 && gv_kg_oftrash <= (CAR_CAPACITY_KG-BIN_SMALL_MAX_KG)){
						tmptime = Uniform(0.6,0.8);//vyprazdni kos
						gv_duration += tmptime;//cas
						gv_kg_oftrash += Uniform(BIN_SMALL_MIN_KG,BIN_SMALL_MAX_KG);//vynulujeme pocitadlo kg smeti
						tmp_street.bin_small_count--;
					}	
					else{
						break;
					}


				}	

				//ak nemame kapacitu tak vyprazdnime a vratime sa
				if(gv_kg_oftrash > (CAR_CAPACITY_KG-BIN_LARGE_MAX_KG) || gv_kg_oftrash > (CAR_CAPACITY_KG-BIN_SMALL_MAX_KG)){
					//vratime sa do ulice,vyprazdnime auticko
					gv_kms += 60; 
					tmptime = Uniform(50,55);
					gv_duration += tmptime;
					smeti += gv_kg_oftrash;
					gv_kg_oftrash = 0;//vynulujeme pocitadlo kg smeti
					
					goto streets;
				}				
				else{//boli vyprazdnene kose
					//std::cout << "fasz" << std::endl;
					goto checkcapacity;
				}

			}
			
			


			//nie su dalsie ulice ale
			if(gv_kg_oftrash > 0){//ak je uz nejaky odpad v aute
				gv_kms += 60; 
				tmptime = Uniform(50,55);
				gv_duration += tmptime;
				smeti += gv_kg_oftrash;
				gv_kg_oftrash = 0;//vynulujeme pocitadlo kg smeti
			}
			else{//ked nie su ulice a ani neni odpad tak neni potreba odniest
				//cas naspat??? TODO
				;
			}
		
		}
		else{//auto plne
			gv_kms += 60; 
			tmptime = Uniform(50,55);
			gv_duration += tmptime;
			smeti += gv_kg_oftrash;
			gv_kg_oftrash = 0;//vynulujeme pocitadlo kg smeti
			goto checkcapacity;
		}

		


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

    RandomSeed(SEED);

    Init(0);
    (new Generator)->Activate();
    Run();

    // TODO remove
    //std::vector<street> streets_1 = load_tsv_file(FILE_PATH_OF_DATA_1);
    //PRINT_STREET_VECTOR(streets_1);
    std::cout << gv_kms << std::endl;
    std::cout << gv_duration << std::endl;
    std::cout << gv_kg_oftrash << std::endl;
     std::cout << "smetii: " << smeti << std::endl;

    return 0;
}
