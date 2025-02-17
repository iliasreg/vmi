# Vmi - A Virtual Machine in C

A simple stack-based virtual machine implemented in C. This project is designed to help you understand how virtual machines work at a low level, including instruction fetching, decoding, and execution.

## Features
- **Stack-Based Design**: Uses a stack for arithmetic and data manipulation.
- **Basic Instruction Set**: Supports instructions like `PSH`, `POP`, `ADD`, `SUB`, `MUL`, `DIV`, `SET`, `LWD`, `STO`, and `HLT`.
- **File-Based Programs**: Reads programs from `.asi` files (Assembly Instruction).
- **Registers**: Includes general-purpose registers (`A`, `B`, `C`, `D`, `E`, `F`) and special-purpose registers (`IP`, `SP`).
- **Memory System**: Supports storing and loading values from memory addresses.

## Instruction Set
| Instruction | Description                          | Example          |
|-------------|--------------------------------------|------------------|
| `PSH <val>` | Push a value onto the stack          | `PSH 10`         |
| `POP`       | Pop the top value from the stack     | `POP`            |
| `ADD`       | Add the top two stack values         | `ADD`            |
| `SUB`       | Subtract the top two stack values    | `SUB`            |
| `MUL <val>` | Multiply the top stack value by `<val>` | `MUL 2`       |
| `DIV <val>` | Divide the top stack value by `<val>`  | `DIV 2`       |
| `SET <reg>, <val>` | Set a register to a value      | `SET A, 10`      |
| `LWD <reg>` | Load value from a register onto the stack | `LWD A`    |
| `STO <addr>`| Store the top stack value at memory address `<addr>` | `STO 0` |
| `HLT`       | Halt the program                     | `HLT`            |

---

## Getting Started

### Prerequisites
- A C compiler (e.g., `clang`, `gcc`).
- GNU Make (for building the project).

### Building the Project
1. Clone the repository:
   ```bash
   git clone https://github.com/iliasreg/vmi.git
   cd vmi
   ```

2. Build the project using `make`:
   ```bash
   make
   ```

3. Run the virtual machine:
   ```bash
   ./vm
   ```

### Writing Programs
Programs are written in `.asi` files. Each line contains an instruction. Comments start with `;`.

#### Example Program (`test.asi`)
```plaintext
; Add 5 and 10 and print the result
PSH 5    ; Push 5 to the stack
PSH 10   ; Push 10 to the stack
ADD      ; Pop 5 and 10, push 15
POP      ; Print the result (15)
HLT      ; Stop the program
```

#### Running the Program
1. Save the program in a file (e.g., `test.asi`).
2. Run the VM with the program:
   ```bash
   ./vm test.asi
   ```

### Expected Output
```
Popped Value is: 15
```

---

## Project Structure
```
vmi/
├── vscode/            // VS Code configuration files
├── helpers/           // Helper functions and utilities
│   ├── helpers.c      // Implementation of helper functions
│   └── helpers.h      // Header for helper functions
├── readers/           // File reading and lexing
│   ├── file_lexer.c   // Implementation of file lexer
│   └── file_lexer.h   // Header for file lexer
├── src/               // Source code
│   ├── main.c         // Entry point (minimal code)
│   └── vm/            // Virtual machine core logic
│       ├── vm.c       // Implementation of VM instructions
│       └── vm.h       // Header for VM logic
├── .gitignore         // Git ignore file
├── code.asi           // Example assembly program
├── Makefile           // Build system
└── README.md          // Project documentation
```

---


### **Key Updates**
1. **Instruction Set**: Added `STO`, `LWD`, `MUL`, `DIV`, and `SUB` instructions.
2. **Example Program**: Updated to demonstrate `STO` and `LWD`.
3. **Project Structure**: Added `file_lexer.h` and `file_lexer.c` to reflect the file reading system.
4. **Future Improvements**: Added plans for control flow and debugging tools.

Let me know if you’d like further tweaks or additions! 🚀

---

## Contributing
Contributions are welcome! If you'd like to contribute:
1. Fork the repository.
2. Create a new branch for your feature: `git checkout -b feature/your-feature`.
3. Commit your changes: `git commit -m "Add your feature"`.
4. Push to the branch: `git push origin feature/your-feature`.
5. Submit a pull request.

---

## License
This project is licensed under the **MIT License**. See [LICENSE](LICENSE) for details.

---
