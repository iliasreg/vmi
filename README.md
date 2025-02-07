# Virtual Machine in C

A simple stack-based virtual machine implemented in C. This project is designed to help you understand how virtual machines work at a low level, including instruction fetching, decoding, and execution.

## Features
- **Stack-Based Design**: Uses a stack for arithmetic and data manipulation.
- **Basic Instruction Set**: Supports instructions like `PSH`, `POP`, `ADD`, `SET`, and `HLT`.
- **File-Based Programs**: Reads programs from `.asi` files (Assembly Instruction).
- **Registers**: Includes general-purpose registers (`A`, `B`, `C`, `D`, `E`, `F`) and special-purpose registers (`IP`, `SP`).

## Instruction Set
| Instruction | Description                          | Example          |
|-------------|--------------------------------------|------------------|
| `PSH <val>` | Push a value onto the stack          | `PSH 10`         |
| `POP`       | Pop the top value from the stack     | `POP`            |
| `ADD`       | Add the top two stack values         | `ADD`            |
| `SET <reg>, <val>` | Set a register to a value      | `SET A, 10`      |
| `HLT`       | Halt the program                     | `HLT`            |

---

## Getting Started

### Prerequisites
- A C compiler (e.g., `clang`, `gcc`).
- GNU Make (for building the project).

### Building the Project
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/your-repo-name.git
   cd your-repo-name
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
vm/
├── vm.h          // Main header file (public declarations)
├── vm.c          // Core VM logic (stack, registers, instructions)
├── file_lexer.h // Header for file reading functionality
├── file_lexer.c // Implementation of file reading
├── main.c        // Entry point (minimal code)
└── Makefile      // Build system
```

---

## Future Improvements
- Add more instructions (e.g., `SUB`, `MUL`, `DIV`, `JMP`, `JEQ`).
- Improve error handling (stack overflow/underflow, invalid instructions).
- Add debugging tools (step-by-step execution, register inspection).

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

## Acknowledgments
- Inspired by [Felix Angell's Virtual Machine in C](https://blog.felixangell.com/virtual-machine-in-c/).
- Special thanks to the Hacker News community for feedback and ideas.
```
