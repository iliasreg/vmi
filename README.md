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

## Getting Started

### Prerequisites
- A C compiler (e.g., `clang`, `gcc`).
- GNU Make (for building the project).
