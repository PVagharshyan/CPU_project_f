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

## Syntax and Grammar

- **Forbidden Symbols:**
  - The custom assembler language prohibits the use of the following symbols: `!@#$%^&*()-+={}[]\|;'"<>./?`

- **Tokenization:**
  - Names and commands can be separated by any number of spaces or newline characters (`\n`). Redundant symbols are mostly ignored during tokenization.

- **Memory Domain References:**
  - Memory addresses can be referenced using `[]` notation inside the code.

- **Registers:**
  - The following registers are available:
    - `AYB`
    - `BEN`
    - `GIM`
    - `DA`
    - `ECH`
    - `ZA`
    - `GH` (acts as the instruction pointer)

- **Markers:**
  - Markers serve as labels within the code and cannot be repeated. They are defined by writing the marker name followed by a colon (`:`).

## Example Usage

An example usage scenario involves writing custom assembly code in a text file (`text.txt`), executing the interpreter with the input file, and observing the program's execution along with memory visualization.

### Output of `text.txt` Execution

---------MEMORY---------
------------------------
|0	 | dumpMemory
------------------------
------------------------
|1	 | MOV AYB, [24]
------------------------
------------------------
|2	 | MOV BEN, 10
------------------------
------------------------
|3	 | ADD AYB, BEN
------------------------
------------------------
|4	 | CMP [25], AYB
------------------------
------------------------
|5	 | JE marker1
------------------------
------------------------
|6	 | JMP marker2
------------------------
------------------------
|7	 | SUB AYB, 5
------------------------
------------------------
|8	 | JG marker3
------------------------
------------------------
|9	 | DIV AYB, 2
------------------------
------------------------
|10	 | JMP marker4
------------------------
------------------------
|11	 | MUL BEN, 3
------------------------
------------------------
|12	 | JMP marker5
------------------------
------------------------
|13	 | dumpMemory
------------------------
------------------------
|14	 | MOV [26], BEN
------------------------
------------------------
|15	 | 0
------------------------
------------------------
|16	 | 0
------------------------
------------------------
|17	 | 0
------------------------
------------------------
|18	 | 0
------------------------
------------------------
|19	 | 0
------------------------
------------------------
|20	 | 0
------------------------
------------------------
|21	 | 0
------------------------
------------------------
|22	 | 0
------------------------
------------------------
|23	 | 0
------------------------
------------------------
|24	 | 0
------------------------
------------------------
|25	 | 0
------------------------
------------------------
|26	 | 0
------------------------
------------------------
|27	 | 0
------------------------
------------------------
|28	 | 0
------------------------
------------------------
|29	 | 0
------------------------
------------------------
|30	 | 0
------------------------
------------------------
|31	 | 0
------------------------
---------INSTRUCTION(1)-----

---------REGISTORS-------

AYB: 0

BEN: 0

GIM: 0

DA: 0

ECH: 0

ZA: 0

GH: 1

----------------------------

---------INSTRUCTION(2)-----

---------REGISTORS-------

AYB: 0

BEN: 0

GIM: 0

DA: 0

ECH: 0

ZA: 9

GH: 2

----------------------------

---------INSTRUCTION(3)-----

---------REGISTORS-------

AYB: 10

BEN: 10

GIM: 0

DA: 0

ECH: 0

ZA: 1

GH: 3

----------------------------

---------INSTRUCTION(4)-----

---------REGISTORS-------

AYB: 20

BEN: 10

GIM: 0

DA: 0

ECH: 0

ZA: 1

GH: 4

----------------------------

---------INSTRUCTION(5)-----

---------REGISTORS-------

AYB: 0

BEN: 10

GIM: 0

DA: 0

ECH: 0

ZA: 9

GH: 5

----------------------------

---------INSTRUCTION(6)-----

---------REGISTORS-------

AYB: 0

BEN: 10

GIM: 0

DA: 0

ECH: 0

ZA: 9

GH: 6

----------------------------

---------INSTRUCTION(10)-----

---------REGISTORS-------

AYB: 0

BEN: 10

GIM: 0

DA: 0

ECH: 0

ZA: 9

GH: 10

----------------------------

---------INSTRUCTION(14)-----

---------REGISTORS-------

AYB: 0

BEN: 10

GIM: 0

DA: 0

ECH: 0

ZA: 9

GH: 14

----------------------------

---------INSTRUCTION(15)-----

---------REGISTORS-------

AYB: 10

BEN: 10

GIM: 0

DA: 0

ECH: 0

ZA: 1

GH: 15

----------------------------

