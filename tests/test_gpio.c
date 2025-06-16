#include "../src/gpio.h"
#include "simple_test.h"

// Test GPIO initialization
int test_gpio_init() {
    gpio_system_t gpio;
    gpio_init(&gpio);
    
    // Check first and last pins are properly initialized
    ASSERT(gpio.pins[0].configured == false);
    ASSERT(gpio.pins[0].value == 0);
    ASSERT(gpio.pins[0].mode == GPIO_MODE_INPUT);
    
    ASSERT(gpio.pins[MAX_GPIO_PINS-1].configured == false);
    ASSERT(gpio.pins[MAX_GPIO_PINS-1].value == 0);
    
    return 1;
}

// Test setting pin modes
int test_gpio_set_mode() {
    gpio_system_t gpio;
    gpio_init(&gpio);
    
    // Test valid pin configuration
    ASSERT(gpio_set_mode(&gpio, 5, GPIO_MODE_OUTPUT) == 0);
    ASSERT(gpio.pins[5].configured == true);
    ASSERT(gpio.pins[5].mode == GPIO_MODE_OUTPUT);
    
    // Test invalid pin numbers
    ASSERT(gpio_set_mode(&gpio, -1, GPIO_MODE_INPUT) == -1);
    ASSERT(gpio_set_mode(&gpio, MAX_GPIO_PINS, GPIO_MODE_INPUT) == -1);
    
    return 1;
}

// Test writing and reading values
int test_gpio_write_read() {
    gpio_system_t gpio;
    gpio_init(&gpio);
    
    // Configure pin as output
    gpio_set_mode(&gpio, 10, GPIO_MODE_OUTPUT);
    
    // Test writing and reading back
    ASSERT(gpio_write(&gpio, 10, 1) == 0);
    ASSERT(gpio_read(&gpio, 10) == 1);
    
    ASSERT(gpio_write(&gpio, 10, 0) == 0);
    ASSERT(gpio_read(&gpio, 10) == 0);
    
    // Test invalid values
    ASSERT(gpio_write(&gpio, 10, 2) == -1);
    ASSERT(gpio_write(&gpio, 10, -1) == -1);
    
    return 1;
}

// Test simulation functionality
int test_gpio_simulate() {
    gpio_system_t gpio;
    gpio_init(&gpio);
    
    // Test simulating on unconfigured pin
    ASSERT(gpio_simulate(&gpio, 15, 1) == 0);
    ASSERT(gpio.pins[15].configured == true);
    ASSERT(gpio.pins[15].mode == GPIO_MODE_INPUT);
    ASSERT(gpio.pins[15].value == 1);
    
    // Test invalid simulation values
    ASSERT(gpio_simulate(&gpio, 15, 5) == -1);
    
    return 1;
}

// Test edge cases
int test_gpio_edge_cases() {
    gpio_system_t gpio;
    gpio_init(&gpio);
    
    // Test boundary pins
    ASSERT(gpio_set_mode(&gpio, 0, GPIO_MODE_INPUT) == 0);
    ASSERT(gpio_set_mode(&gpio, MAX_GPIO_PINS - 1, GPIO_MODE_OUTPUT) == 0);
    
    // Test reading unconfigured pin
    ASSERT(gpio_read(&gpio, 20) == 0);
    
    return 1;
}

int main() {
    printf("GPIO Simulator - Unit Tests\n");
    printf("===========================\n");
    
    TEST(gpio_init);
    TEST(gpio_set_mode);
    TEST(gpio_write_read);
    TEST(gpio_simulate);
    TEST(gpio_edge_cases);  // Fixed the name here
    
    TEST_SUMMARY();
    
    return (test_passed == test_count) ? 0 : 1;
}

