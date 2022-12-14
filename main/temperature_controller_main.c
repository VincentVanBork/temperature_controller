/*
 * MIT License
 *
 * Copyright (c) 2017 David Antliff
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"

#include "measure/temperature_controller_measure.h"
#include "screen/temperature_controller_screen.h"


_Noreturn void app_main()
{
    // Override global log level
    esp_log_level_set("*", ESP_LOG_INFO);

    // To debug, use 'make menuconfig' to set default Log level to DEBUG, then uncomment:
    //esp_log_level_set("owb", ESP_LOG_DEBUG);
    //esp_log_level_set("ds18b20", ESP_LOG_DEBUG);


    // Stable readings require a brief period before communication
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    OneWireBus* owb = initialize_bus();
    FoundDevices* found_devices = find_devices(owb);
    read_devices(owb, found_devices->rom);
    DS18B20_Info* device = create_devices(owb);

    i2c_master_init();
    ssd1306_init();
    xTaskCreate(&task_ssd1306_display_clear, "ssd1306_display_clear",  2048, NULL, 6, NULL);
    vTaskDelay(100/portTICK_PERIOD_MS);
    while(1){
        TickType_t last_wake_time = xTaskGetTickCount();
        float reading = measure_using_DS18B20(device);
        char message[48] = {0};
        char const_message[] = " Temperatura:\n";
        int j = snprintf(message, 16, "%s", const_message);
        j += snprintf(message+j, 16, "    %.1f    \n", reading);
        j += snprintf(message+j, 16, " Czas: \n");
        snprintf(message+j, 16, "%.1u\n", last_wake_time);
        xTaskCreate(&task_ssd1306_display_text, "ssd1306_display_text",  2048,
                    (void *)message, 6, NULL);
//        xTaskCreate(&task_ssd1306_display_clear, "ssd1306_display_clear",  2048, NULL, 6, NULL);
//        vTaskDelayUntil(&last_wake_time, SAMPLE_PERIOD / portTICK_PERIOD_MS);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }

    printf("Restarting now.\n");
    fflush(stdout);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    esp_restart();
}