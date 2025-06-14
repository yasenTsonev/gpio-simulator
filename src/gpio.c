#include "gpio.h"
#include <string.h>
#include <stdio.h>

void gpio_init(gpio_system_t *gpio) {
    memset(gpio, 0, sizeof(gpio_system_t));
    
    // Initialize all pins as unconfigured with default values
    for (int i = 0; i < MAX_GPIO_PINS; i++) {
        gpio->pins[i].configured = false;
        gpio->pins[i].value = 0;
        gpio->pins[i].mode = GPIO_MODE_INPUT;  // Default mode

        // Initialize callbacks
        gpio->callbacks[i].callback = NULL;
        gpio->callbacks[i].user_data = NULL;
        gpio->callbacks[i].active = false;

        // Register default callback for all pins
        gpio_set_callback(gpio, i, pin_change_callback, NULL);        
    }
    
}

int gpio_is_valid_pin(int pin) {
    return pin >= 0 && pin < MAX_GPIO_PINS;
}

int gpio_set_mode(gpio_system_t *gpio, int pin, gpio_mode_t mode) {
    if (!gpio_is_valid_pin(pin)) {
        printf( "Error: Pin %d out of range (0-%d)\n", pin, MAX_GPIO_PINS - 1);
        return -1;
    }
    
    gpio->pins[pin].mode = mode;
    gpio->pins[pin].configured = true;
    
    // Reset value to 0 when changing modes (common behavior)
    gpio->pins[pin].value = 0;
    
    return 0;
}

int gpio_write(gpio_system_t *gpio, int pin, int value) {
    if (!gpio_is_valid_pin(pin)) {
        printf( "Error: Pin %d out of range (0-%d)\n", pin, MAX_GPIO_PINS - 1);
        return -1;
    }
    //TODO check if the mode/direction is already set, 
    //if not set as output, maybe do not proceed?
    if (value < 0 || value > 1) {
        printf("Invalid value supplied, please use only 0 or 1");
        return -1;
    }
    
    int old_value = gpio->pins[pin].value;
    gpio->pins[pin].value = value;
    gpio->pins[pin].configured = true;
    
    // Trigger callbacks on value change
    gpio_trigger_callbacks(gpio, pin, old_value, value);   
    
    return 0;
}

int gpio_read(gpio_system_t *gpio, int pin) {
    if (!gpio_is_valid_pin(pin)) {
        printf( "Error: Pin %d out of range (0-%d)\n", pin, MAX_GPIO_PINS - 1);
        return -1;
    }
   
    return gpio->pins[pin].value;
}

// Add these functions to gpio.c

int gpio_list_pins(gpio_system_t *gpio) {
    printf("\nGPIO Pin States:\n");
    printf("================\n");
    printf("Pin | Mode   | Configured | Value\n");
    printf("----|--------|------------|------\n");
    
    bool any_configured = false;
    
    for (int i = 0; i < MAX_GPIO_PINS; i++) {
        if (gpio->pins[i].configured) {
            const char *mode_str = (gpio->pins[i].mode == GPIO_MODE_INPUT) ? "INPUT" : "OUTPUT";
            printf("%2d  | %-6s | %-10s | %d\n", 
                   i, mode_str, "YES", gpio->pins[i].value);
            any_configured = true;
        }
    }
    
    if (!any_configured) {
        printf("No pins are currently configured.\n");
        printf("Use 'set-mode' command to configure pins.\n");
    }
    
    printf("\n");
    return 0;
}

int gpio_simulate(gpio_system_t *gpio, int pin, int value) {
    if (!gpio_is_valid_pin(pin)) {
        printf("Error: Pin %d out of range (0-%d)\n", pin, MAX_GPIO_PINS - 1);
        return -1;
    }
    
    if (value < 0 || value > 1) {
        printf("Error: Invalid value %d. Use 0 or 1 only.\n", value);
        return -1;
    }
    
    // Check if pin is configured
    if (!gpio->pins[pin].configured) {
        printf("Warning: Pin %d is not configured. Setting as INPUT and simulating value.\n", pin);
        gpio_set_mode(gpio, pin, GPIO_MODE_INPUT);
    }
    
    // For simulation, we allow setting any pin's value regardless of mode
    // This simulates external signals on input pins or confirms output values
    int old_value = gpio->pins[pin].value;
    gpio->pins[pin].value = value;
    
    const char *mode_str = (gpio->pins[pin].mode == GPIO_MODE_INPUT) ? "INPUT" : "OUTPUT";
    
    if (old_value != value) {
        printf("Pin %d (%s): %d -> %d (simulated)\n", pin, mode_str, old_value, value);
        
        // Trigger callbacks on value change
        gpio_trigger_callbacks(gpio, pin, old_value, value);
    } else {
        printf("Pin %d (%s): value remains %d\n", pin, mode_str, value);
    }
    
    return 0;
}

// Callback system functions
int gpio_set_callback(gpio_system_t *gpio, int pin, gpio_callback_t callback, void *user_data) {
    if (!gpio_is_valid_pin(pin)) {
        printf("Error: Pin %d out of range (0-%d)\n", pin, MAX_GPIO_PINS - 1);
        return -1;
    }
    
    gpio->callbacks[pin].callback = callback;
    gpio->callbacks[pin].user_data = user_data;
    gpio->callbacks[pin].active = (callback != NULL);
    
    return 0;
}

void gpio_trigger_callbacks(gpio_system_t *gpio, int pin, int old_value, int new_value) {
    printf("Callback invoked before IF gpio_trigger_callbacks\n");
    if (gpio_is_valid_pin(pin) && gpio->callbacks[pin].active && old_value != new_value) {
        gpio->callbacks[pin].callback(pin, old_value, new_value, gpio->callbacks[pin].user_data);
        printf("Callback invokedin IF gpio_trigger_callbacks\n");
    }
}

void pin_change_callback(int pin, int old_value, int new_value, void *user_data) {
    (void)user_data; // Suppress unused parameter warning
    printf("CALLBACK: Pin %d changed from %d to %d in pin_change_callback()\n", pin, old_value, new_value);
}