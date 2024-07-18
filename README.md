
# Common Firmware Environment (CFE)

## Summary

The Common Firmware Environment (CFE) is a versatile firmware platform designed to initialize and manage the hardware of embedded systems. It provides essential services such as bootloading, diagnostics, and hardware abstraction, allowing for smooth interaction between software and hardware components.

##ARM/printf

### Overview

The ARM source file is responsible for initializing the ARM processor. The file initializes the processor state, including setting up stack pointers and other necessary registers. Here, we configure various hardware peripherals, such as the USART for serial communication. The lib_printf.c file implements a simple printf function, designed for use in boot ROMs. We Typically used the prtinf function for debugging and logging within the firmware.

### Features

- **Formatted Output:** Supports standard printf formatting options for integers, strings, floats, and more.
- **Hardware Integration:** Leverages ARM-specific instructions and optimizations.

## Misccmds

### Overview

The `misccmds` module in CFE provides a collection of miscellaneous commands that enhance the functionality and usability of the firmware environment. These commands cover a wide range of utility functions not categorized under other specific command modules.

### Key Commands

- **`display`:** Displays the current memory contents of a specific address
- **`edit`:** Edits a specific address's value
- **`writei2c`:** writes to the I2C device, used for LEDS and joystick that make use of IOexpander 1 or 2.
- **`displayi2c`:** Displays the value of an addreess on an I2C device
- **`writei2cio2`:** Writes to an address and displays the result, mainly used for debugging purposes
- **`ledx`:** x refers to a specific LED on the STM32 board, can be used to turn on and off any light i.e ledb 0 (LED blue off)
- **`joystick`:** Initilizes the joystick for user input and prints out the input from the joystick
- **`systick`:** Initializes Systick and starts counting down from the SysTick Reload Value.  

### Implementation

The `misccmds` commands are implemented in the `ui_misccmds.c` file, where each command is defined and its behavior is specified.

## Examcmds

### Overview

The `examcmds` module contains a set of examination commands used primarily for testing and debugging the system. These commands allow developers to inspect and manipulate various aspects of the system's state.

### Key Commands

- **`ui_cmd_disasm`:** Disassembles instructions at the specified address. This command can continue disassembly from the last address if no parameters are provided.

- **`ui_cmd_memdump`:** Dumps memory data in various formats (bytes, halfwords, words, quadwords). ASCII text, if present, is shown alongside the hex data. Remembers the previous word size, dump length, and last displayed address for continuous dumping.

- **`ui_cmd_memedit`:** Modifies the contents of memory at the specified address. If data is not provided on the command line, it prompts for it interactively. Allows backing up, dumping memory, or exiting edit mode during the prompt.

- **`ui_cmd_memfill`:** Fills the contents of memory with a specified pattern starting from the given address for a certain length. Supports various data sizes (bytes, halfwords, words, quadwords).

- **`ui_cmd_memtest`:** Tests memory starting at a specified address for a given length. This is a basic test and should not be relied upon for critical purposes. Includes options to not stop on error and to loop the test until a keypress.

### Implementation

The `examcmds` commands are implemented in the `ui_examcmds.c` file. Each command is tailored to provide detailed information that assists in system diagnostics and troubleshooting.

## Systicktimer

### Overview

The `systicktimer` module in CFE is responsible for managing the system tick timer, a critical component for timekeeping and scheduling in embedded systems. It provides precise timing and interrupt handling capabilities.

### Features

- **Accurate Timekeeping:** Ensures precise measurement of elapsed time.
- **Interrupt Handling:** Generates periodic interrupts for task scheduling.
- **Low Overhead:** Optimized for minimal performance impact.

### Usage

The `systicktimer` is typically initialized during system startup and used throughout the firmware to manage timed operations and schedule tasks.

##Resethandler

### Overview

The `resethandler` module manages the system reset functionality, ensuring a controlled and orderly reset process. It handles various types of resets, including hardware and software-initiated resets.

### Features

- **Controlled Reset:** Ensures all system components are properly reset.
- **Error Handling:** Logs reset causes and errors for post-reset diagnostics.
- **Customizable:** Allows for customization of reset behavior based on specific requirements.

### Implementation

The `resethandler` is implemented in the `cfe_resethandler.c` file. It includes functions for initiating and managing the reset process, as well as logging and handling errors.

## Updates

- v0.0 updated readme 