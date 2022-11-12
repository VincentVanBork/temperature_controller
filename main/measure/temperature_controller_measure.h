//
// Created by michal on 12/11/2022.
//

#ifndef TEMPERATURE_CONTROLLER_TEMPERATURE_CONTROLLER_MEASURE_H
#define TEMPERATURE_CONTROLLER_TEMPERATURE_CONTROLLER_MEASURE_H
    #include "owb.h"
    #include "owb_rmt.h"
    #include "ds18b20.h"

    #define GPIO_DS18B20_0       (4)
    #define MAX_DEVICES          (8)
    #define DS18B20_RESOLUTION   (DS18B20_RESOLUTION_12_BIT)
    #define SAMPLE_PERIOD        (1000)   // milliseconds

    void measure_using_DS18B20();
#endif //TEMPERATURE_CONTROLLER_TEMPERATURE_CONTROLLER_MEASURE_H

