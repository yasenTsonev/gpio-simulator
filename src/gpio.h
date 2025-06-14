// #ifndef GPIO_H
// #define GPIO_H

// #include <stdbool.h>

// typedef enum {
//     GPIO_MODE_INPUT,
//     GPIO_MODE_OUTPUT
// } gpio_mode_t;

// typedef void (*gpio_callback_t)(int pin, int old_value, int new_value);

// typedef struct {
//     gpio_mode_t mode;
//     int value;
//     bool configured;
//     gpio_callback_t callback;
// } gpio_pin_t;

// typedef struct {
//     gpio_pin_t pins[32];
// } gpio_system_t;

// void gpio_init(gpio_system_t *gpio);
// int gpio_set_mode(gpio_system_t *gpio, int pin, gpio_mode_t mode);
// int gpio_write(gpio_system_t *gpio, int pin, int value);
// int gpio_read(gpio_system_t *gpio, int pin, int *value);
// int gpio_simulate_input(gpio_system_t *gpio, int pin, int value);
// void gpio_register_callback(gpio_system_t *gpio, int pin, gpio_callback_t cb);

// #endif

#ifndef GPIO_H
#define GPIO_H

#include <stdbool.h>

#define MAX_GPIO_PINS 32

// Callback function type
typedef void (*gpio_callback_t)(int pin, int old_value, int new_value, void *user_data);

typedef enum {
    GPIO_MODE_INPUT,
    GPIO_MODE_OUTPUT
} gpio_mode_t;

typedef struct {
    gpio_mode_t mode;
    int value;
    bool configured;
} gpio_pin_t;

// Callback entry structure
typedef struct {
    gpio_callback_t callback;
    void *user_data;
    bool active;
} gpio_callback_entry_t;

typedef struct {
    gpio_pin_t pins[MAX_GPIO_PINS];
    gpio_callback_entry_t callbacks[MAX_GPIO_PINS];
} gpio_system_t;





// Core functions
void gpio_init(gpio_system_t *gpio);
int gpio_set_mode(gpio_system_t *gpio, int pin, gpio_mode_t mode);
int gpio_write(gpio_system_t *gpio, int pin, int value);
int gpio_read(gpio_system_t *gpio, int pin);
int gpio_is_valid_pin(int pin);
int gpio_list_pins(gpio_system_t *gpio);
int gpio_simulate(gpio_system_t *gpio, int pin, int value);
int gpio_set_callback(gpio_system_t *gpio, int pin, gpio_callback_t callback, void *user_data);
void gpio_trigger_callbacks(gpio_system_t *gpio, int pin, int old_value, int new_value);
void pin_change_callback(int pin, int old_value, int new_value, void *user_data);

#endif