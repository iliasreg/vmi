#include "vm.h"
#include "../readers/file_lexer.h"
#include "../helpers/helpers.h"

#include <stdio.h>
#include <stdint.h>

/* Initializations */
bool loop = true;
int stack[STACK_SIZE] = {0};
int registers[NUM_OF_REGISTERS];
int memory[MEMORY_SIZE] = {0};

// Fetching instructions from the program array 
int fetch(int* prog){
	return prog[registers[IP]];
}

// Evaluating instructions
void eval(int* prog, int inst){
	switch(inst){
		case HLT: {
			loop = false;
			break;
		}
		case PSH: {
			registers[SP]++;
			if(registers[SP] >= STACK_SIZE - 1){
				fprintf(stderr, "Error: Stack Overflow !\n");
				loop = false;
				break;
			}
			stack[registers[SP]] = prog[++registers[IP]];
			printf("--Pushed Value: %d\n", stack[registers[SP]]);
			break;
		}
		case LWD: {
			registers[SP]++;
			if(registers[SP] >= STACK_SIZE - 1){
				fprintf(stderr, "Error: Stack Overflow !\n");
				loop = false;
				break;
			}
			int loadFromRegister = prog[++registers[IP]];
			int valueToLoad = registers[loadFromRegister];
			stack[registers[SP]] = valueToLoad;
			printf("--Loaded Value %d from Register %s\n", valueToLoad, getRegisterName(loadFromRegister));
			break;
		}
		case POP: {
			if(registers[SP] < 0){
				fprintf(stderr, "Error: Stack Underflow !\n");
				loop = false;
				break;
			}
			int poppedValue = stack[registers[SP]--];
			printf("Popped Value: %d\n", poppedValue);
			break;
		}
		case ADD: {
			if(registers[SP] < 1){
				fprintf(stderr, "Error: Stack Underflow; Stack should have 2 values to add together\n");
				loop = false;
				break;
			}
			if(registers[SP]+1 > STACK_SIZE){
				fprintf(stderr, "Error: Stack Underflow; Stack should have 2 values to add together\n");
				loop = false;
				break;
			}
			int res = stack[registers[SP]--] + stack[registers[SP]--];
			registers[SP] = registers[SP] + 3;
			stack[registers[SP]] = res;
			printf("--Added two last values in stack !\n");
			break;
		}
		case SUB: {
			if(registers[SP] < 1){
				fprintf(stderr, "Error: Stack Underflow !\n");
				loop = false;
				break;
			}
			int res = stack[registers[SP]--] - stack[registers[SP]--];
			stack[++registers[SP]] = res;
			printf("--Subtracted two last values in stack !\n");
			break;
		}
		case MUL: {
			if(registers[SP] <0){
				fprintf(stderr, "Error: Stack Underflow !\n");
				loop = false;
				break;
			}
			int coeff = prog[++registers[IP]];
			int res = stack[registers[SP]--] * coeff;
			stack[++registers[SP]] = res;
			printf("--Multiplied by %d\n", coeff);
			break;
		}
		case DIV: {
			if(registers[SP] < 0){
				fprintf(stderr, "Error: Stack Underflow !\n");
				loop = false;
				break;
			}
			int a = stack[registers[SP]--];
			int coeff = prog[++registers[IP]];
			if(coeff == 0){
				fprintf(stderr, "Error: Division by zero is impossible !\n");
				loop = false;
				break;
			}
			int res = a / coeff;
			stack[++registers[SP]] = res;
			printf("--Divided by %d\n", coeff);
			break;
		}
		case SET: {
			int reg = prog[++registers[IP]];
			if (reg > NUM_OF_REGISTERS){
				fprintf(stderr, "Error: Invalid Register\n");
				loop = false;
				break;
			}
			int x = prog[++registers[IP]];
			registers[reg] = x;
			printf("--Register %s set to: %d\n", getRegisterName(reg), x);
			break;
		}
		case STO: {
			int address = prog[++registers[IP]];
			if(registers[SP] < 0){
				fprintf(stderr, "Error: Stack Underflow !\n");
				loop = false;
				break;
			}
			if(address < 0 || address > MEMORY_SIZE){
				fprintf(stderr, "Invalid memory location, check the range of addresses allowed !\n");
				loop = false;
				break;
			}
			int valueToStore = stack[registers[SP]--];
			memory[address] = valueToStore;
			printf("--Stored value %d to memory adddress 0x%04X\n", valueToStore, address);
			break;
		}
		default: {
			fprintf(stderr, "Invalid instruction, check the instruction set !\n");
			loop = false;
			break;
		}
	}
}