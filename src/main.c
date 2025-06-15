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

// Menu command structure
typedef struct {
    int id;
    const char *name;
    command_handler_t handler;
    const char *description;
} menu_command_t;


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

static const menu_command_t menu_commands[] = {
    {1, "set-mode", handle_set_mode_interactive, "Set Pin Mode"},
    {2, "write", handle_write_interactive, "Set Output Pin Value"},
    {3, "read", handle_read_interactive, "Read Input Pin Value"},
    {4, "simulate", handle_simulate_interactive, "Simulate Input Value"},
    {5, "list", handle_list_wrapper, "List All Pin States"},
    {6, "help", handle_help_interactive, "Show Help"},
    {0, "exit", NULL, "Exit Program"},
    {-1, NULL, NULL, NULL} // Sentinel
};

void display_menu() {
    printf("\n");
    printf("GPIO Simulator\n");
    printf("==============\n");
    for (int i = 0; menu_commands[i].id != -1; i++) {
        printf("%d. %s\n", menu_commands[i].id, menu_commands[i].description);
    }
    printf("Enter choice: ");
}

const menu_command_t* find_menu_command(int choice) {
    for (int i = 0; menu_commands[i].id != -1; i++) {
        if (menu_commands[i].id == choice) {
            return &menu_commands[i];
        }
    }
    return NULL;
}


int handle_help() {
    
    printf("Available commands:\n");
    for (int i = 0; commands[i].name != NULL; i++) {
        printf("  %-10s - %s\n", commands[i].name, commands[i].description);
    }
    return 0;
}

// TODO range check?
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
    // Initialize GPIO system
    gpio_system_t gpio;
    gpio_init(&gpio);
    
    printf("Welcome to GPIO Simulator!\n");
    
    // Interactive menu loop
    while (1) {
        display_menu();
        
        int choice;
        if (scanf("%d", &choice) == 1) {
            // Success - choice contains valid integer, and is only 1 digit
            printf("You entered: %d\n", choice);
        } else {
            // Failure - clear buffer and show error
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Error: Please enter a valid number.\n");
        }
        
        // Clear the input buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        
        if (choice == 0) {
            printf("Goodbye!\n");
            break;
        }
        
        const menu_command_t *cmd = find_menu_command(choice);
        if (cmd != NULL && cmd->handler != NULL) {
            // Create dummy argc/argv for compatibility
            char *dummy_argv[] = {"gpio_simulator", cmd->name, NULL, NULL, NULL};
            cmd->handler(&gpio, 2, dummy_argv);
        } else if (choice == 6) {
            // Handle help separately since it doesn't need GPIO
            handle_help_interactive(&gpio, 0, NULL);
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}