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
    #define SAMPLE_PERIOD        (2000)   // milliseconds

    typedef struct {
        int num;
        OneWireBus_ROMCode* rom;
    } FoundDevices;

    float measure_using_DS18B20(DS18B20_Info* device);

    OneWireBus* initialize_bus();
    FoundDevices* find_devices(const OneWireBus* owb);
    void read_devices(const OneWireBus* owb, OneWireBus_ROMCode* rom_code);
    DS18B20_Info* create_devices(const OneWireBus* owb);

#endif //TEMPERATURE_CONTROLLER_TEMPERATURE_CONTROLLER_MEASURE_H

