#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include "gpio.h"
#include <stdbool.h>

// Function declarations
int gpio_save_state(gpio_system_t *gpio, const char *filename);
int gpio_load_state(gpio_system_t *gpio, const char *filename);
int gpio_export_config(gpio_system_t *gpio, const char *filename);
bool persistence_file_exists(const char *filename);

// Default filenames
#define DEFAULT_STATE_FILE "gpio_state.json"
#define DEFAULT_CONFIG_FILE "gpio_config.json"

#endif // PERSISTENCE_H
