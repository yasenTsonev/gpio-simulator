
# Firmware Engineer Coding Task: GPIO CLI Simulator

## Overview

This task is designed to assess your skills in C programming, software design, Linux development, and version control. You are asked to create a command-line application that simulates GPIO (General Purpose Input/Output) pin control and behavior in a Linux environment—**no hardware is required**.

The focus is on writing clean, modular C code, applying good software architecture principles, and demonstrating development workflows using Git.

---

## Objectives

- Build a simulated GPIO system in C  
- Provide an interactive CLI (Command Line Interface) for choosing actions during runtime  
- Simulate GPIO modes, reads/writes
- Set callbacks for pin state change
- Showcase software engineering best practices  
- Optional: Persist GPIO state to a file for reuse across executions

---

## Task Details

### 1. GPIO Simulation Backend
Create a software layer that simulates GPIO behavior:
- Each GPIO pin can be configured as:
  - `input`: value can be simulated externally
  - `output`: value is set via the CLI
- Store pin states and configuration in memory
- Maximum number of pins is by default 32, zero based numbering.

### 2. Interactive Command-Line Interface (CLI)
Implement an **interactive** CLI that lets users perform operations in a single execution session.  
- On program start, show a menu like:
  ```text
  GPIO Simulator
  ==============
  1. Set Pin Mode
  2. Set output pin value 
  3. Read input pin value 
  4. Simulate input value
  5. List All Pin States
  6. Exit
  Enter choice:
  ```
- After each operation, the menu should be shown again until the user chooses to exit.
- **On exit, the GPIO state is lost.**
- Use standard C libraries (`stdio.h`, `stdlib.h`, etc.)

### 3. Set callbacks for pin state change
Your code should have a callback executed when a state of a GPIO input changes. Callback should be able to print information about the state change.

### 4. State Persistence (Bonus)
- Save pin states and configurations to a file (e.g., JSON or text)
- On startup, optionally load from that file to restore state

## Requirements

- Language: C (C99 or newer)  
- Platform: Linux (x86 or ARM, any distro)  
- Build system: Makefile (CMake is acceptable if justified)  
- Version control: Git, with a meaningful commit history  
- Tests: Include at least a few unit tests for core logic  
- Documentation:
  - `README.md`: Build instructions, usage examples
  - `architecture.md`: Short write-up (300–600 words) describing your software design and component responsibilities

---

## Evaluation Criteria

| Category          | What We’re Looking For                                                 |
|------------------|------------------------------------------------------------------------|
| Code Quality      | Clear, readable, idiomatic C with good structure                       |
| Architecture      | Separation of concerns, modular design, testability                    |
| Linux Familiarity | CLI patterns, file IO, Makefile usage                                  |
| Git Workflow      | Logical commit history, use of branches if applicable                  |
| Testing           | Demonstrated ability to test functionality and edge cases              |
| Documentation     | Clear instructions, high-level design reasoning                        |
| Bonus Features    | Edge detection, state persistence, logging                             |

---

## Timebox

- Estimated time: 16–24 hours total, ideally spread over up to 4 days  
- Submit a link to Git repo with your implementation

---

## Bonus (Optional)

Implement any of the following for extra credit:
- File-based GPIO state persistence  
- Concurrency simulation (e.g., simulate GPIO pin events in a thread)  
- GPIOD-like API design  
- JSON export of pin states

---

## Submission Checklist

- [ ] Makefile builds the tool cleanly  
- [ ] Interactive CLI functions correctly  
- [ ] Simulated GPIO behavior matches description  
- [ ] Test cases included and runnable  
- [ ] Git history shows logical progression  
- [ ] README.md and architecture.md are clear and complete  
- [ ] Bonus: File-based persistence
