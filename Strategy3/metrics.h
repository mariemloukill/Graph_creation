//
// Created by Mariem Loukil on 3/20/22.
//

#ifndef STRATEGY3_METRICS_H
#include <chrono>
using namespace std::chrono;

void add_result_to_file (double result, std::string f);


//void calculate_total_time ( std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<long,
        //std::ratio<1, 1000000000>>> start);


void calculate_peak_RAM (std::string results_file);

#define STRATEGY3_METRICS_H

#endif STRATEGY3_METRICS_H
