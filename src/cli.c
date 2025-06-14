
// int handle_set_mode(gpio_system_t *gpio, int argc, char *argv[]) {
//     if (argc != 4) {
//         printf("Usage: %s set-mode <pin> <input|output>\n", argv[0]);
//         return 1;
//     }
    
//     int pin = atoi(argv[2]);
//     gpio_mode_t mode = (strcmp(argv[3], "input") == 0) ? 
//                        GPIO_MODE_INPUT : GPIO_MODE_OUTPUT;
    
//     if (gpio_set_mode(gpio, pin, mode) < 0) {
//         printf("Failed to set mode\n");
//         return 1;
//     }
    
//     printf("Pin %d set to %s\n", pin, argv[3]);
//     return 0;
// }

#include "cli.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage(const char *program_name) {
    printf("Usage: %s <command> [arguments]\n", program_name);
    printf("\nCommands:\n");
    printf("  set-mode <pin> <input|output>  Configure pin mode\n");    
    printf("\nExample:\n");
    printf("  %s set-mode 5 output\n", program_name);

    printf("  write <pin> <0|1>  Set pin value\n");    
    printf("\nExample:\n");
    printf("  %s write 5 0\n", program_name);
}

int handle_set_mode(gpio_system_t *gpio, int arg_count, char *argv[]) {
    // Check argument count
    if (arg_count != 4) {
        printf( "Error: set-mode requires 2 arguments\n");
        printf( "Usage: %s set-mode <pin> <input|output>\n", argv[0]);
        return 1;
    }
    
    // Parse pin number
    char *endptr;
    int pin = strtol(argv[2], &endptr, 10);
    
    // Check if pin parsing was successful
    if (*endptr != '\0') {
        printf( "Error: Invalid pin number '%s'\n", argv[2]);
        return 1;
    }
    
    // Parse mode
    gpio_mode_t mode;
    if (strcmp(argv[3], "input") == 0) {
        mode = GPIO_MODE_INPUT;
    } else if (strcmp(argv[3], "output") == 0) {
        mode = GPIO_MODE_OUTPUT;
    } else {
        printf( "Error: Invalid mode '%s'. Use 'input' or 'output'\n", argv[3]);
        return 1;
    }
    
    // Set the mode
    if (gpio_set_mode(gpio, pin, mode) < 0) {
        return 1;  // Error already printed by gpio_set_mode
    }
    
    // Success message
    printf("Pin %d configured as %s\n", pin, argv[3]);
    return 0;
}

int handle_write(gpio_system_t *gpio, int arg_count, char *argv[]) {
    // Check argument count
    if (arg_count != 4) {
        printf( "Error: writ requires 2 arguments\n");
        printf( "Usage: %s write <pin> <0|1>\n", argv[0]);
        return 1;
    }
    
    // Parse pin number
    char *endptr;
    int pin = strtol(argv[2], &endptr, 10);
    
    // Check if pin parsing was successful
    if (*endptr != '\0') {
        printf( "Error: Invalid pin number '%s'\n", argv[2]);
        return 1;
    }
    
    //parse value
    char *endptr_value;
    int value = strtol(argv[3], &endptr_value, 10);
    
    // Check if pin parsing was successful
    if (*endptr_value != '\0') {
        printf( "Error: Invalid pin number '%s'\n", argv[3]);
        return 1;
    }       
    // Set the mode
    if (gpio_write(gpio, pin, value) < 0) {
        return 1;  // Error already printed by gpio_set_mode
    }
    
    // Success message
    printf("Pin %d set as %d\n", pin, value);
    return 0;
}

int handle_read(gpio_system_t *gpio, int arg_count, char *argv[]) {
    // Check argument count
    if (arg_count != 3) {
        printf( "Error: writ requires 1 argument\n");
        printf( "Usage: %s read <pin> \n", argv[0]);
        return 1;
    }
    
    // Parse pin number
    char *endptr;
    int pin = strtol(argv[2], &endptr, 10);
    
    // Check if pin parsing was successful
    if (*endptr != '\0') {
        printf( "Error: Invalid pin number '%s'\n", argv[2]);
        return 1;
    }
    
    int value  = gpio_read(gpio, pin);
    if ( value != -1) {
        printf("Pin %d read as %d\n", pin, value);
    }else {
        printf("Error at reading %d pin\n", pin);
    }
    // Success message
    
    return value;
}

// Add these CLI handlers to cli.c

int handle_list(gpio_system_t *gpio) {
    return gpio_list_pins(gpio);
}

int handle_simulate(gpio_system_t *gpio, int argc, char *argv[]) {
    // Check argument count
    if (argc != 4) {
        printf("Error: simulate requires 2 arguments\n");
        printf("Usage: %s simulate <pin> <value>\n", argv[0]);
        printf("  pin:   GPIO pin number (0-%d)\n", MAX_GPIO_PINS - 1);
        printf("  value: 0 or 1\n");
        printf("Example: %s simulate 5 1\n", argv[0]);
        return 1;
    }
    
    // Parse pin number
    char *endptr;
    int pin = strtol(argv[2], &endptr, 10);
    
    // Check if pin parsing was successful
    if (*endptr != '\0') {
        printf("Error: Invalid pin number '%s'\n", argv[2]);
        return 1;
    }
    
    // Parse value
    char *endptr_value;
    int value = strtol(argv[3], &endptr_value, 10);
    
    // Check if value parsing was successful
    if (*endptr_value != '\0') {
        printf("Error: Invalid value '%s'\n", argv[3]);
        return 1;
    }
    
    // Call the GPIO core function
    if (gpio_simulate(gpio, pin, value) < 0) {
        return 1;  // Error already printed by gpio_simulate
    }
    
    return 0;
}

int handle_list_wrapper(gpio_system_t *gpio, int argc, char *argv[]) {
    (void)argc; // Suppress unused parameter warning
    (void)argv; // Suppress unused parameter warning
    return handle_list(gpio);
}
