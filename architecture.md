# GPIO CLI Simulator - Architecture Description
## Overview
The GPIO CLI Simulator is a modular C application that simulates GPIO pin control and behavior in a Linux environment. The system provides both command-line and interactive menu interfaces for GPIO operations, with optional state persistence and callback functionality.

## Component Architecture
1. Core GPIO Layer (gpio.c/gpio.h)
Responsibility: Pure GPIO simulation logic and state management

- GPIO State Management: Maintains pin configurations (mode, value, configured status) for 32 pins (0-31)
- Pin Operations: Provides core functions for setting modes, reading/writing values, and input simulation
- Callback System: Implements event-driven callbacks that trigger on pin state changes
- Validation: Ensures pin numbers and values are within valid ranges
- Key Functions: gpio_init(), gpio_set_mode(), gpio_write(), gpio_read(), gpio_simulate()

2. Command Line Interface (cli.c/cli.h)
Responsibility: User interface and command parsing

- Command Parsing: Handles both single-command execution and interactive menu operations
- Input Validation: Robust parsing with error handling and user feedback
- Interactive Menu: Provides numbered menu system as specified in requirements
- Session Management: Maintains GPIO state across multiple operations in interactive mode
- Key Functions: Command handlers for set-mode, write, read, simulate, list operations

3. Persistence Layer (persistence.c/persistence.h)
Responsibility: State serialization and restoration (Bonus Feature)

- JSON Export/Import: Human-readable state files with versioning and timestamps
- Selective Persistence: Only saves configured pins for compact storage
- Auto-restore: Optional state loading on application startup

4. Application Controller (main.c)
Responsibility: Application orchestration and command routing

- Function Pointer Dispatch: Uses command tables with function pointers for clean, extensible command routing
- Interactive Loop: Manages the main menu loop with proper input handling and buffer management
- System Integration: Coordinates between GPIO core, CLI, and persistence layers
- Design Principles Applied
    - Separation of Concerns
    - GPIO logic is isolated from user interface concerns
    - CLI layer handles only presentation and input parsing
    - Persistence is completely optional and doesn't affect core functionality
    - Modularity
    - Each component has clear interfaces and minimal dependencies
    - Components can be tested independently
    - Easy to extend with new commands or features
    - Error Handling
    - Comprehensive input validation at all layers
    - Graceful error recovery with user-friendly messages
    - Proper resource cleanup and buffer management

- Data Flow
    - User Input → CLI Parser → Command Validation
    - Command Execution → GPIO Core Operations → State Updates
    - State Changes → Callback Triggers → User Notifications
    - Optional Persistence → JSON Serialization → File Storage
- Testing Strategy
    - Simple unit test framework focusing on:

