#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gpio.h"
#include "cli.h"

// Command handler function pointer type
typedef int (*command_handler_t)(gpio_system_t *gpio, int argc, char *argv[]);

int handle_help();

// Command structure
typedef struct {
    const char *name;
    command_handler_t handler;
    const char *description;
} command_t;

// Command table
static const command_t commands[] = {
    {"set-mode", handle_set_mode, "Set pin mode - e.g. set [0-31] input/output"},
    {"write", handle_write, "Write value to output pin - e.g. write [0-31] 1/0"},
    {"read", handle_read, "Read value from input pin - e.g. read [0-31]"},
    {"simulate", handle_simulate, "Simulate input value"},
    {"list", handle_list_wrapper, "List all pin states"},
    {"help", handle_help, "Show this help message"},
    {NULL, NULL, NULL} // Sentinel to mark end of array
};

// Wrapper for handle_list to match function signature
// int handle_list_wrapper(gpio_system_t *gpio, int argc, char *argv[]) {
//     (void)argc; // Suppress unused parameter warning
//     (void)argv;
//     return handle_list(gpio);
// }

// // Help command handler
int handle_help() {
    
    printf("Available commands:\n");
    for (int i = 0; commands[i].name != NULL; i++) {
        printf("  %-10s - %s\n", commands[i].name, commands[i].description);
    }
    return 0;
}

//TODO range check?
// Find command by name
const command_t* find_command(const char *name) {
    for (int i = 0; commands[i].name != NULL; i++) {
        if (strcmp(commands[i].name, name) == 0) {
            return &commands[i];
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    // Check if we have at least a command
    if (argc < 2) {
        fprintf(stderr, "Error: No command specified\n");
        print_usage(argv[0]);
        return 1;
    }
    
    // Initialize GPIO system
    gpio_system_t gpio;
    gpio_init(&gpio);
    
    // // Parse command
    // const char *command = argv[1];
    //TODO implement better way to do this, maybe with function pointers
    printf("argc is %d \n", argc);
    // Find and execute command
    const char *command_name = argv[1];
    const command_t *cmd = find_command(command_name);
    
    if (cmd != NULL) {
        return cmd->handler(&gpio, argc, argv);
    } else {
        printf("Error: Unknown command '%s'\n", command_name);
        printf("Use 'help' to see available commands.\n");
        print_usage(argv[0]);
        return 1;
    }
    
    return 0;
}