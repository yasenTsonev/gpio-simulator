#ifndef CLI_H
#define CLI_H

#include "gpio.h"

// Command handlers
int handle_set_mode(gpio_system_t *gpio, int arg_count, char *argv[]);
int handle_write(gpio_system_t *gpio, int arg_count, char *argv[]);
int handle_read(gpio_system_t *gpio, int arg_count, char *argv[]);
int handle_list(gpio_system_t *gpio);
int handle_simulate(gpio_system_t *gpio, int argc, char *argv[]);
int handle_list_wrapper(gpio_system_t *gpio, int argc, char *argv[]);

// menu functions
int handle_set_mode_interactive(gpio_system_t *gpio, int argc, char *argv[]);
int handle_write_interactive(gpio_system_t *gpio, int argc, char *argv[]);
int handle_read_interactive(gpio_system_t *gpio, int argc, char *argv[]);
int handle_simulate_interactive(gpio_system_t *gpio, int argc, char *argv[]);
int handle_help_interactive(gpio_system_t *gpio, int argc, char *argv[]);

int handle_save_interactive(gpio_system_t *gpio, int argc, char *argv[]);
int handle_load_interactive(gpio_system_t *gpio, int argc, char *argv[]);


void print_usage(const char *program_name);

#endif