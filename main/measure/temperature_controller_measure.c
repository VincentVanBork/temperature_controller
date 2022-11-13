//
// Created by michal on 12/11/2022.
//

#include "temperature_controller_measure.h"

OneWireBus* initialize_bus(){
    OneWireBus* owb = malloc(sizeof (OneWireBus));
    owb_rmt_driver_info* p_rmt_driver_info = malloc(sizeof (owb_rmt_driver_info));
    owb = owb_rmt_initialize(p_rmt_driver_info, GPIO_DS18B20_0, RMT_CHANNEL_1, RMT_CHANNEL_0);
    owb_use_crc(owb, true);  // enable CRC check for ROM code
    return owb;
}

FoundDevices* find_devices(const OneWireBus* owb){
    // TODO: write malloc guards for everything
    FoundDevices* devices = malloc(sizeof (FoundDevices));
    printf("Find devices:\n");
    OneWireBus_ROMCode* device_rom_code = malloc(sizeof (OneWireBus_ROMCode));
    OneWireBus_SearchState* search_state = malloc(sizeof (OneWireBus_SearchState ));
    uint8_t num_devices = 0;
    bool found = false;
    owb_search_first(owb, search_state, &found);
    if(found){
        char rom_code_s[17];
        owb_string_from_rom_code(search_state->rom_code, rom_code_s, sizeof(rom_code_s));
        printf(" First Device : %s\n", rom_code_s);
        *(device_rom_code) = search_state->rom_code;
        ++num_devices;
    }
    printf("Found %d device%s\n", num_devices, num_devices == 1 ? "" : "s");
    if (num_devices == 0 ){
        printf("\nNo DS18B20 devices detected!\n");
    }
    devices->num = num_devices;
    devices->rom = device_rom_code;
    return devices;
};

void read_devices(const OneWireBus* owb, OneWireBus_ROMCode* rom_code){
    owb_status status = owb_read_rom(owb, rom_code);
    if (status == OWB_STATUS_OK)
        {
            char rom_code_s[OWB_ROM_CODE_STRING_LENGTH];
            owb_string_from_rom_code(*(rom_code), rom_code_s, sizeof(rom_code_s));
            printf("Read ROM Single device %s present\n", rom_code_s);
        }
    else
    {
        printf("An error occurred reading ROM code: %d", status);
    }
}


DS18B20_Info* create_devices(const OneWireBus* owb){
     DS18B20_Info * ds18b20_info = ds18b20_malloc();  // heap allocation
     printf("Single device optimisations enabled\n");
     ds18b20_init_solo(ds18b20_info, owb);          // only one device on bus
     ds18b20_use_crc(ds18b20_info, true);           // enable CRC check on all reads
     ds18b20_set_resolution(ds18b20_info, DS18B20_RESOLUTION);
     return ds18b20_info;
};

float measure_using_DS18B20(DS18B20_Info* device){
    ds18b20_convert(device);
    ds18b20_wait_for_conversion(device);
    float reading;
    DS18B20_ERROR error = ds18b20_read_temp(device, &reading);
    printf("Read temperature %.1f    %d errors\n",  reading, error);
    return reading;
//    ds18b20_free(&device);
//
//    owb_uninitialize(owb);
}