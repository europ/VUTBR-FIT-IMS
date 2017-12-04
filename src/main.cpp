#include <iostream>
#include <vector>

#include "simlib.h"

#include "macros.hpp"
#include "constants.hpp"
#include "data_types.hpp"
#include "file_data.hpp"

// GLOBAL VARIABLES
unsigned int gv_car_count = 0; // car count
double smeti = 0; // TODO check it and rename it properly
double gv_kms = 0; // kilometers travelled
double gv_duration = 0; // time of collecting
double gv_kg_oftrash = 0;


class Car : public Process {

    void Behavior() {

        double tmptime;
        std::vector<street> streets_1;


        streets_1 = load_tsv_file(FILE_PATH_OF_DATA_1); // ulice pre auto
        tmptime = Uniform(2.5,3.5); // cas výjazdu

        gv_duration+= tmptime;
        gv_kms+= 1.5;



        checkcapacity: // GOTO LABEL



        // kontrola kapacity
        if( (gv_kg_oftrash <= (CAR_CAPACITY_KG - BIN_LARGE_MAX_KG)) || (gv_kg_oftrash <= (CAR_CAPACITY_KG - BIN_SMALL_MAX_KG)) ) {


            // kym su ulice
            while(streets_1.size() > 0) {

                // ziskame prvu ulicu
                street tmp_street = streets_1[0];



                streets: // GOTO LABEL



                // kym mame kapacitu
                while( (gv_kg_oftrash <= (CAR_CAPACITY_KG - BIN_LARGE_MAX_KG)) || (gv_kg_oftrash <= (CAR_CAPACITY_KG - BIN_SMALL_MAX_KG)) ) {

                    // vybavili sa kose na aktualnej ulici a mame este kapacitu na pokracovanie
                    if( (tmp_street.bin_large_count == 0) && (tmp_street.bin_small_count == 0) ) {

                        streets_1.erase(streets_1.begin()); // odstranime aktualnu ulicu (odpad sme pozbierali)
                        break;

                    }


                    // ak su velke kose a dostatocna kapacita tak sa vyprazdni velky kos
                    if( (tmp_street.bin_large_count > 0) && ( gv_kg_oftrash <= (CAR_CAPACITY_KG - BIN_LARGE_MAX_KG)) ) {

                        tmptime = Uniform(0.8,1); // vyprazdnime kos
                        
                        gv_duration += tmptime; // celkovy cas
                        gv_kg_oftrash += Uniform(BIN_LARGE_MIN_KG,BIN_LARGE_MAX_KG); // dokopy všetky smeti
                        tmp_street.bin_large_count--;

                    }

                    // ak su male kose  akapacita tak vyprazdni sa maly kos
                    else if( (tmp_street.bin_small_count > 0) && (gv_kg_oftrash <= (CAR_CAPACITY_KG - BIN_SMALL_MAX_KG)) ) {

                        tmptime = Uniform(0.6,0.8); // vyprazdnime kos
                        gv_duration += tmptime; // celkovy cas
                        gv_kg_oftrash += Uniform(BIN_SMALL_MIN_KG,BIN_SMALL_MAX_KG); // dokopy všetky smeti
                        tmp_street.bin_small_count--;

                    }

                    else {

                        break;

                    }


                } // WHILE - INNER


                // ak nemame kapacitu tak vyprazdnime auto a vratime sa
                if( (gv_kg_oftrash > (CAR_CAPACITY_KG-BIN_LARGE_MAX_KG)) || (gv_kg_oftrash > (CAR_CAPACITY_KG - BIN_SMALL_MAX_KG)) ) {

                    tmptime = Uniform(50,55);

                    gv_kms += 60; // distance
                    gv_duration += tmptime; // celkovy cas
                    smeti += gv_kg_oftrash; // TODO why we use smeti variable?

                    gv_kg_oftrash = 0; // vynulujeme pocitadlo kg smeti

                    goto streets; // vratime sa sa do ulice

                }

                // boli vyprazdnene kose na aktualnej ulici
                else{

                    goto checkcapacity;
                }


            } // WHILE - OUTER


            // nie su dalsie ulice
            if(gv_kg_oftrash > 0) { // ak je este nejaky odpad v aute tak ho odnesie

                tmptime = Uniform(50,55);

                gv_kms += 60;
                gv_duration += tmptime;
                smeti += gv_kg_oftrash; // TODO

                gv_kg_oftrash = 0; // vynulujeme pocitadlo kg smeti auta
            }
            else { // nie je odpad v aute & nie su ulice

                //cas naspat??? TODO
                ;

            }

        } // IF 
        else { // auto je plne & este su ulice

            tmptime = Uniform(50,55);

            gv_kms += 60;
            gv_duration += tmptime;
            smeti += gv_kg_oftrash;

            gv_kg_oftrash = 0; // vynulujeme pocitadlo kg smeti auta

            goto checkcapacity;

        }


    } // END Behavior()

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
    std::cout << "gv_kms        = " << gv_kms << std::endl;
    std::cout << "gv_duration   = " << gv_duration << std::endl;
    std::cout << "gv_kg_oftrash = " << gv_kg_oftrash << std::endl;
    std::cout << "smeti         = " << smeti << std::endl;

    return 0;
}
