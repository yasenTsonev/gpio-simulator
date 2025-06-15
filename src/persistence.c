#include "persistence.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Helper function to get current timestamp
void get_timestamp(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *tm_info = gmtime(&now);
    strftime(buffer, size, "%Y-%m-%dT%H:%M:%SZ", tm_info);
}

int gpio_save_state(gpio_system_t *gpio, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: Cannot create file '%s'\n", filename);
        return -1;
    }
    
    char timestamp[32];
    get_timestamp(timestamp, sizeof(timestamp));
    
    // Write JSON header
    fprintf(file, "{\n");
    fprintf(file, "  \"gpio_state\": {\n");
    fprintf(file, "    \"version\": \"1.0\",\n");
    fprintf(file, "    \"timestamp\": \"%s\",\n", timestamp);
    fprintf(file, "    \"pins\": [\n");
    
    // Write configured pins
    bool first_pin = true;
    for (int i = 0; i < MAX_GPIO_PINS; i++) {
        if (gpio->pins[i].configured) {
            if (!first_pin) {
                fprintf(file, ",\n");
            }
            
            const char *mode_str = (gpio->pins[i].mode == GPIO_MODE_INPUT) ? "input" : "output";
            
            fprintf(file, "      {\n");
            fprintf(file, "        \"pin\": %d,\n", i);
            fprintf(file, "        \"configured\": true,\n");
            fprintf(file, "        \"mode\": \"%s\",\n", mode_str);
            fprintf(file, "        \"value\": %d\n", gpio->pins[i].value);
            fprintf(file, "      }");
            
            first_pin = false;
        }
    }
    
    // Write JSON footer
    fprintf(file, "\n    ]\n");
    fprintf(file, "  }\n");
    fprintf(file, "}\n");
    
    fclose(file);
    printf("GPIO state saved to '%s'\n", filename);
    return 0;
}

int gpio_load_state(gpio_system_t *gpio, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Info: No saved state file '%s' found\n", filename);
        return -1;
    }
    
    printf("Loading GPIO state from '%s'...\n", filename);
    
    // Simple JSON parsing (for demo purposes)
    // In production, you'd use a proper JSON library like cJSON
    char line[256];
    int pin = -1;
    gpio_mode_t mode = GPIO_MODE_INPUT;
    int value = 0;
    bool in_pin_object = false;
    
    while (fgets(line, sizeof(line), file)) {
        // Remove whitespace and parse key-value pairs
        char *trimmed = line;
        while (*trimmed == ' ' || *trimmed == '\t') trimmed++;
        
        if (strstr(trimmed, "\"pin\":")) {
            sscanf(trimmed, "\"pin\": %d", &pin);
            in_pin_object = true;
        } else if (strstr(trimmed, "\"mode\":") && in_pin_object) {
            if (strstr(trimmed, "\"output\"")) {
                mode = GPIO_MODE_OUTPUT;
            } else {
                mode = GPIO_MODE_INPUT;
            }
        } else if (strstr(trimmed, "\"value\":") && in_pin_object) {
            sscanf(trimmed, "\"value\": %d", &value);
        } else if (strstr(trimmed, "}") && in_pin_object && pin >= 0) {
            // End of pin object - apply the configuration
            gpio_set_mode(gpio, pin, mode);
            gpio->pins[pin].value = value;
            printf("  Restored pin %d: %s, value=%d\n", pin, 
                   (mode == GPIO_MODE_INPUT) ? "INPUT" : "OUTPUT", value);
            
            // Reset for next pin
            pin = -1;
            in_pin_object = false;
        }
    }
    
    fclose(file);
    printf("GPIO state loaded successfully\n");
    return 0;
}

bool persistence_file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}
