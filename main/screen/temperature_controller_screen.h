
#ifndef TEMPERATURE_CONTROLLER_TEMPERATURE_CONTROLLER_SCREEN_H
#define TEMPERATURE_CONTROLLER_TEMPERATURE_CONTROLLER_SCREEN_H
void task_ssd1306_display_text(const void *arg_text);
void task_ssd1306_scroll(void *ignore);
void task_ssd1306_contrast(void *ignore);
void task_ssd1306_display_clear(void *ignore);
void task_ssd1306_display_pattern(void *ignore);
void ssd1306_init();
void i2c_master_init();

#endif //TEMPERATURE_CONTROLLER_TEMPERATURE_CONTROLLER_MEASURE_H
