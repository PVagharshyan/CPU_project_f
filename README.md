# Project Documentation: Custom Assembler Interpreter

This project is an assembler interpreter designed to process code written in a custom assembly language similar to MASM (Microsoft Macro Assembler). The interpreter translates the assembly code into machine code and executes it accordingly.

## Usage

To use the interpreter, follow these steps:

1. **Input File Preparation:**
   - Prepare a text file (`text.txt`) containing the assembly code written in the custom assembly language. Ensure that the code adheres to the syntax and grammar specified below.

2. **Executing the Interpreter:**
   - Execute the interpreter by running the compiled executable (`a.out`) in the terminal:
     ```
     ./output text.txt
     ```

3. **Command-Based Grammar:**
   - The assembler language follows a command-based grammar with specific syntax for instructions and directives. Below are the supported commands:

     - **mov/add/sub/mul/div/and/or**:
       - Syntax: `<command> operand1, operand2`
       - Valid operands include registers and memory addresses (literals).

     - **cmp**:
       - Syntax: `cmp operand1, operand2`
       - Compares the values stored in the specified memory addresses or registers.

     - **jpm/jg/jl/je**:
       - Syntax: `<command> marker`
       - Jumps to the specified marker based on the result of the previous comparison operation.

4. **Dump Memory Visualization:**
   - Use the `dumpMemory` command to visualize the memory contents during program execution.

## Syntax

- **Forbidden Symbols:**
  - The custom assembler language prohibits the use of the following symbols: `!@#$%^&*()-+={}[]\|;'"<>./?`

- **Tokenization:**
  - Names and commands can be separated by any number of spaces or newline characters (`\n`). Redundant symbols are mostly ignored during tokenization.

- **Memory Domain References:**
  - Memory addresses can be referenced using `[]` notation inside the code.

- **Markers:**
  - Markers serve as labels within the code and cannot be repeated. They are defined by writing the marker name followed by a colon (`:`).

## Example Usage

An example usage scenario involves writing custom assembly code in a text file (`text.txt`), executing the interpreter with the input file, and observing the program's execution along with memory visualization.
