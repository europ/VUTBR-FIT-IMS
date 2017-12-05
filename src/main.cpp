#include <iostream>
#include <vector>

#include "simlib.h"

#include "macros.hpp"
#include "constants.hpp"
#include "data_types.hpp"
#include "file_data.hpp"



// GLOBAL VARIABLES
unsigned int gv_car_count = 0; // car count
double *smeti;//[CAR_COUNT] = {0.0}; // TODO check it and rename it properly
double *gv_kms;//[CAR_COUNT] = {0.0}; // kilometers travelled
double *gv_duration;//[CAR_COUNT] = {0.0}; // time of collecting
double *gv_kg_oftrash;//[CAR_COUNT] = {0.0};// kg of trash in car

unsigned int car_count;//depends on 
unsigned int dump_distance;

std::vector< std::vector<street> > streets;//[CAR_COUNT];//streets - for every car different

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
        //std::cout<<carnum<<std::endl;

        //streets_1 = load_tsv_file(FILE_PATH_OF_DATA_1); // ulice pre auto
        tmptime = Uniform(2.5,3.5); // cas výjazdu v minutach
        Wait(tmptime);

        gv_duration[carnum] += tmptime;
        gv_kms[carnum] += CAR_AVERAGE_SPEED*(tmptime/60);

        //std::cout <<gv_kms[carnum]<<std::endl;

        checkcapacity: // GOTO LABEL

        // kontrola kapacity
        if( (gv_kg_oftrash[carnum] <= (CAR_CAPACITY_KG - BIN_LARGE_MAX_KG)) || (gv_kg_oftrash[carnum] <= (CAR_CAPACITY_KG - BIN_SMALL_MAX_KG)) ) {

            //std::cout <<"fasz" + std::to_string(carnum) <<std::endl;
            // kym su ulice
            while(streets[carnum].size() > 0) {

                // ziskame prvu ulicu
                street tmp_street = streets[carnum][0];

                //std::cout << "faszom    " + std::to_string(streets[carnum].size()) <<std::endl;


                // kym mame kapacitu
                while( (gv_kg_oftrash[carnum] <= (CAR_CAPACITY_KG - BIN_LARGE_MAX_KG)) || (gv_kg_oftrash[carnum] <= (CAR_CAPACITY_KG - BIN_SMALL_MAX_KG)) ) {
                    //std::cout <<"while" + std::to_string(carnum) <<std::endl;
                    // vybavili sa kose na aktualnej ulici a mame este kapacitu na pokracovanie
                    if( (tmp_street.bin_large_count == 0) && (tmp_street.bin_small_count == 0) ) {//ak na ulici vsetky kose vyprazdnene
                        gv_kms[carnum] += tmp_street.street_length;//pridame prejetu dlzku
                        gv_duration[carnum] += (tmp_street.street_length/CAR_AVERAGE_SPEED)*60;//pocet minut v ulici
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
                       // std::cout <<"BIG " + std::to_string(tmp_street.bin_large_count) <<std::endl;
                        streets[carnum][0] = tmp_street;

                    }

                    // ak su male kose  akapacita tak vyprazdni sa maly kos
                    else if( (tmp_street.bin_small_count > 0) && (gv_kg_oftrash[carnum] <= (CAR_CAPACITY_KG - BIN_SMALL_MAX_KG)) ) {

                        tmptime = Uniform(0.6,0.8); // vyprazdnime kos
                        Wait(tmptime);
                        gv_duration[carnum] += tmptime; // celkovy cas
                        gv_kg_oftrash[carnum] += Uniform(BIN_SMALL_MIN_KG,BIN_SMALL_MAX_KG); // dokopy všetky smeti
                        tmp_street.bin_small_count--;
                        //std::cout <<"SMALL " + std::to_string(tmp_street.bin_small_count) <<std::endl;
                        streets[carnum][0] = tmp_street;

                    }

                    else {//ma este kapacitu na maly kos ale maly kos uz neni v ulici - tak odnesie smeti

                        break;

                    }


                } // WHILE - INNER


                // ak nemame kapacitu tak vyprazdnime auto a vratime sa
                if( (gv_kg_oftrash[carnum] > (CAR_CAPACITY_KG-BIN_LARGE_MAX_KG)) || (gv_kg_oftrash[carnum] > (CAR_CAPACITY_KG - BIN_SMALL_MAX_KG)) ) {

                    tmptime = Uniform(50,55);

                    Wait(tmptime);
                    gv_kms[carnum] += 2*dump_distance; // distance
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
                gv_kms[carnum] += 2*dump_distance;
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
            gv_kms[carnum] += 2*dump_distance;
            gv_duration[carnum] += tmptime;
            smeti[carnum] += gv_kg_oftrash[carnum];

            gv_kg_oftrash[carnum] = 0; // vynulujeme pocitadlo kg smeti auta

            goto checkcapacity;

        }


    } // END Behavior()

};


class Generator : public Event {

    void Behavior() {
        for(; gv_car_count<car_count; gv_car_count++) {
            (new Car(gv_car_count))->Activate(Time);
            //Activate(Time);
        }
    }

};


int main(int argc, char* argv[]) {

    (void)argc; // -Wunused-parameter
    //(void)argv; // -Wunused-parameter

    if(argc!=2){
        std::cerr << "Wrong arguments!" << std::endl;
        exit(1);
    }


    if(std::string(argv[1]) == "experiment1"){
        car_count = 2;
        dump_distance = 27;
        smeti = new double[2]{0.0};
        gv_kms = new double[2]{0.0};
        gv_duration = new double[2]{0.0};
        gv_kg_oftrash = new double[2]{0.0};


        streets.push_back(load_tsv_file(FILE_PATH_OF_DATA_1)); // ulice pre auto
        streets.push_back(load_tsv_file(FILE_PATH_OF_DATA_2));
        std::cout << "Experiment 1 " << std::endl;
    
        /*PRINT_STREET_VECTOR(load_tsv_file(FILE_PATH_OF_DATA_1));
        PRINT("============================");
        PRINT_STREET_VECTOR(load_tsv_file(FILE_PATH_OF_DATA_2));
        */

    }
    else if(std::string(argv[1]) == "experiment2"){
        dump_distance = 27;
        car_count = 3;
        smeti = new double[3]{0.0};
        gv_kms = new double[3]{0.0};
        gv_duration = new double[3]{0.0};
        gv_kg_oftrash = new double[3]{0.0};



        streets.push_back(load_tsv_file(FILE_PATH_OF_DATA_3)); // ulice pre auto
        streets.push_back(load_tsv_file(FILE_PATH_OF_DATA_4));
        streets.push_back(load_tsv_file(FILE_PATH_OF_DATA_5)); 
        std::cout << "Experiment 2 " << std::endl;

    }
    else if(std::string(argv[1]) == "experiment3"){
        dump_distance = 5;
        car_count = 2;
        smeti = new double[2]{0.0};
        gv_kms = new double[2]{0.0};
        gv_duration = new double[2]{0.0};
        gv_kg_oftrash = new double[2]{0.0};

        streets.push_back(load_tsv_file(FILE_PATH_OF_DATA_1)); // ulice pre auto
        streets.push_back(load_tsv_file(FILE_PATH_OF_DATA_2));
        std::cout << "Experiment 3 " << std::endl;
    }
    else{
        std::cerr << "Chybne argumenty!" << std::endl;
        exit(1);
    }


    RandomSeed(SEED);

    Init(0);
    (new Generator)->Activate();
    Run();



    // TODO remove
    std::cout << "Prejete km auto c. 1 = " << gv_kms[0] << std::endl;
    std::cout << "Dlzka zberu auto c. 1   = " << gv_duration[0]/60 << std::endl;
    std::cout << "smeti v aute c. 1 po dokonceni = " << gv_kg_oftrash[0] << std::endl;
    std::cout << "Smeti dokopy auto c. 1        = " << smeti[0] << std::endl;
    std::cout << "Spotreba auta c. 1        = " << gv_kms[0]*CAR_FUEL_CONSUMPTION_PER_KM << "L" << std::endl << std::endl;

    std::cout << "Prejete km auto c. 2 = " << gv_kms[1] << std::endl;
    std::cout << "Dlzka zberu auto c. 2   = " << gv_duration[1]/60 << std::endl;
    std::cout << "smeti v aute c. 2 po dokonceni = " << gv_kg_oftrash[1] << std::endl;
    std::cout << "Smeti dokopy auto c. 2        = " << smeti[1] << std::endl;
    std::cout << "Spotreba auta c. 2        = " << gv_kms[1]*CAR_FUEL_CONSUMPTION_PER_KM << "L" << std::endl << std::endl;

    if(std::string(argv[1]) == "experiment1" || std::string(argv[1]) == "experiment3"){
        
        double tmp_trash = smeti[0]+smeti[1];
        double tmp_time = gv_duration[0]/60 + gv_duration[1]/60;
        std::cout << "Celkovy cas zberu = " << tmp_time << std::endl;
        std::cout << "Celkovy pocet smeti v kg = " << tmp_trash << std::endl << std::endl;
    }

 

    if(std::string(argv[1]) == "experiment2"){
        std::cout << "Prejete km auto c. 3 = " << gv_kms[2] << std::endl;
        std::cout << "Dlzka zberu auto c. 3   = " << gv_duration[2]/60 << std::endl;
        std::cout << "meti v aute c. 3 po dokonceni = " << gv_kg_oftrash[2] << std::endl;
        std::cout << "Smeti dokopy auto c. 3        = " << smeti[2] << std::endl;
        std::cout << "Spotreba auto c. 3        = " << gv_kms[2]*CAR_FUEL_CONSUMPTION_PER_KM << "L" << std::endl << std::endl;

        double tmp_trash = smeti[0]+smeti[1]+smeti[2];
        double tmp_time = gv_duration[0]/60 + gv_duration[1]/60 + gv_duration[2]/60;
        std::cout << "Celkovy cas zberu = " << tmp_time << std::endl;
        std::cout << "Celkovy pocet smeti v kg = " << tmp_trash  << std::endl << std::endl;
    }


    delete [] smeti;
    delete [] gv_kms;
    delete [] gv_duration;
    delete [] gv_kg_oftrash;


    return 0;
}
