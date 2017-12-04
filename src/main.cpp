#include <iostream>
#include <vector>

#include "simlib.h"

#include "macros.hpp"
#include "constants.hpp"
#include "data_types.hpp"
#include "file_data.hpp"



// GLOBAL VARIABLES
unsigned int gv_car_count = 0; // car count
double smeti[CAR_COUNT] = {0.0}; // TODO check it and rename it properly
double gv_kms[CAR_COUNT] = {0.0}; // kilometers travelled
double gv_duration[CAR_COUNT] = {0.0}; // time of collecting
double gv_kg_oftrash[CAR_COUNT] = {0.0};// kg of trash in car

std::vector<street> streets[CAR_COUNT];//streets - for every car different

class Car : public Process {
    public:
    int carnum;
    Car(int num) {
        carnum = num;
    }


    void Behavior() {

        double tmptime = 0.0;
        //std::vector<street> streets_1;
        //int carnum = procnum++;
        std::cout<<carnum<<std::endl;

        //streets_1 = load_tsv_file(FILE_PATH_OF_DATA_1); // ulice pre auto
        tmptime = Uniform(2.5,3.5); // cas výjazdu v minutach
        Wait(tmptime);

        gv_duration[carnum] += tmptime;
        gv_kms[carnum] += CAR_AVERAGE_SPEED*(tmptime/60);

        std::cout <<gv_kms[carnum]<<std::endl;

        checkcapacity: // GOTO LABEL

        // kontrola kapacity
        if( (gv_kg_oftrash[carnum] <= (CAR_CAPACITY_KG - BIN_LARGE_MAX_KG)) || (gv_kg_oftrash[carnum] <= (CAR_CAPACITY_KG - BIN_SMALL_MAX_KG)) ) {

           // std::cout <<"fasz" + std::to_string(carnum) <<std::endl;
            // kym su ulice
            while(streets[carnum].size() > 0) {

                // ziskame prvu ulicu
                street tmp_street = streets[carnum][0];

               // std::cout << "faszom    " + std::to_string(streets[carnum].size()) <<std::endl;


                // kym mame kapacitu
                while( (gv_kg_oftrash[carnum] <= (CAR_CAPACITY_KG - BIN_LARGE_MAX_KG)) || (gv_kg_oftrash[carnum] <= (CAR_CAPACITY_KG - BIN_SMALL_MAX_KG)) ) {
                    //std::cout <<"while" + std::to_string(carnum) <<std::endl;
                    // vybavili sa kose na aktualnej ulici a mame este kapacitu na pokracovanie
                    if( (tmp_street.bin_large_count == 0) && (tmp_street.bin_small_count == 0) ) {
                        streets[carnum].erase(streets[carnum].begin()); // odstranime aktualnu ulicu (odpad sme pozbierali)
                        break;

                    }


                    // ak su velke kose a dostatocna kapacita tak sa vyprazdni velky kos
                    if( (tmp_street.bin_large_count > 0) && ( gv_kg_oftrash[carnum] <= (CAR_CAPACITY_KG - BIN_LARGE_MAX_KG)) ) {

                        tmptime = Uniform(0.8,1); // vyprazdnime kos
                        Wait(tmptime);
                        gv_duration[carnum] += tmptime; // celkovy cas
                        gv_kg_oftrash[carnum] += Uniform(BIN_LARGE_MIN_KG,BIN_LARGE_MAX_KG); // dokopy všetky smeti
                        tmp_street.bin_large_count--;
                        streets[carnum][0] = tmp_street;
                    }

                    // ak su male kose  akapacita tak vyprazdni sa maly kos
                    else if( (tmp_street.bin_small_count > 0) && (gv_kg_oftrash[carnum] <= (CAR_CAPACITY_KG - BIN_SMALL_MAX_KG)) ) {

                        tmptime = Uniform(0.6,0.8); // vyprazdnime kos
                        Wait(tmptime);
                        gv_duration[carnum] += tmptime; // celkovy cas
                        gv_kg_oftrash[carnum] += Uniform(BIN_SMALL_MIN_KG,BIN_SMALL_MAX_KG); // dokopy všetky smeti
                        tmp_street.bin_small_count--;
                        streets[carnum][0] = tmp_street;

                    }

                    else {

                        break;

                    }


                } // WHILE - INNER


                // ak nemame kapacitu tak vyprazdnime auto a vratime sa
                if( (gv_kg_oftrash[carnum] > (CAR_CAPACITY_KG-BIN_LARGE_MAX_KG)) || (gv_kg_oftrash[carnum] > (CAR_CAPACITY_KG - BIN_SMALL_MAX_KG)) ) {

                    tmptime = Uniform(50,55);

                    Wait(tmptime);
                    gv_kms[carnum] += 60; // distance
                    gv_duration[carnum] += tmptime; // celkovy cas
                    smeti[carnum] += gv_kg_oftrash[carnum]; // TODO why we use smeti variable?

                    gv_kg_oftrash[carnum] = 0; // vynulujeme pocitadlo kg smeti

                    //goto streets; // vratime sa sa do ulice ak este nejake ostali
                    continue;
                
                    

                }

                // boli vyprazdnene kose na aktualnej ulici
                else{

                    goto checkcapacity;
                }


            } // WHILE - OUTER


            // nie su dalsie ulice
            if(gv_kg_oftrash[carnum] > 0) { // ak je este nejaky odpad v aute tak ho odnesie

                tmptime = Uniform(50,55);
                Wait(tmptime);
                gv_kms[carnum] += 60;
                gv_duration[carnum] += tmptime;
                smeti[carnum] += gv_kg_oftrash[carnum]; // TODO

                gv_kg_oftrash[carnum] = 0; // vynulujeme pocitadlo kg smeti auta
            }
            else { // nie je odpad v aute & nie su ulice

                //cas naspat??? TODO
                ;

            }

        } // IF 
        else { // auto je plne & este su ulice

            tmptime = Uniform(50,55);
            Wait(tmptime);
            gv_kms[carnum] += 60;
            gv_duration[carnum] += tmptime;
            smeti[carnum] += gv_kg_oftrash[carnum];

            gv_kg_oftrash[carnum] = 0; // vynulujeme pocitadlo kg smeti auta

            goto checkcapacity;

        }


    } // END Behavior()

};


class Generator : public Event {

    void Behavior() {
        for(; gv_car_count<CAR_COUNT; gv_car_count++) {
            (new Car(gv_car_count))->Activate(Time);
            //Activate(Time);
        }
    }

};


int main(int argc, char* argv[]) {

    (void)argc; // -Wunused-parameter
    (void)argv; // -Wunused-parameter


    if(CAR_COUNT==2){
        streets[0] = load_tsv_file(FILE_PATH_OF_DATA_1); // ulice pre auto
        streets[1] = load_tsv_file(FILE_PATH_OF_DATA_2);
    }
    else if(CAR_COUNT==1){
        std::vector<street> tmp1 = load_tsv_file(FILE_PATH_OF_DATA_1);
        std::vector<street> tmp2 = load_tsv_file(FILE_PATH_OF_DATA_2);
        tmp1.insert(tmp1.end(),tmp2.begin(),tmp2.end());
        streets[0] = tmp1;
    }


    RandomSeed(SEED);

    Init(0);
    (new Generator)->Activate();
    Run();

    // TODO remove
    std::cout << "prejete km auto c. 1 = " << gv_kms[0] << std::endl;
    std::cout << "dlzka zberu auto c. 1   = " << gv_duration[0] << std::endl;
    std::cout << "smeti v aute c. 1 po dokonceni = " << gv_kg_oftrash[0] << std::endl;
    std::cout << "smeti dokopy auto 1        = " << smeti[0] << std::endl;

    std::cout << "prejete km auto c. 2 = " << gv_kms[1] << std::endl;
    std::cout << "dlzka zberu auto c. 2   = " << gv_duration[1] << std::endl;
    std::cout << "smeti v aute c. 2 po dokonceni = " << gv_kg_oftrash[1] << std::endl;
    std::cout << "smeti dokopy auto 2        = " << smeti[1] << std::endl;

    double tmp = smeti[0]+smeti[1];

    std::cout << "vsetkooooo " << tmp << std::endl;
    
    return 0;
}
