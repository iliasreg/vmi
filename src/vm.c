#include "vm.h"
#include "file_lexer.h"
#include <stdio.h>

bool loop = true;
int stack[STACK_SIZE];
int registers[NUM_OF_REGISTERS];

int fetch(int* prog){
	return prog[registers[IP]];
}

void eval(int* prog, int inst){
	switch(inst){
		case HLT: {
			loop = false;
			break;
		}
		case PSH: {
			registers[SP]++;
			if(registers[SP] >= STACK_SIZE - 1){
				fprintf(stderr, "Error: Stack Overflow !");
				loop = false;
				break;
			}
			stack[registers[SP]] = prog[++registers[IP]];
			printf("Pushed Value: %d\n", stack[registers[SP]]);
			break;
		}
		case POP: {
			if(registers[SP] < 0){
				fprintf(stderr, "Error: Stack Underflow !");
				loop = false;
				break;
			}
			int poppedValue = stack[registers[SP]--];
			printf("Poppedd Value is: %d\n", poppedValue);
			break;
		}
		case ADD: {
			int res = stack[registers[SP]--] + stack[registers[SP]--];
			stack[++registers[SP]] = res;
			break;
		}
		case SET: {
			int reg = prog[++registers[IP]];
			if (reg > NUM_OF_REGISTERS){
				fprintf(stderr, "Error: Invalid Register");
				loop = false;
				break;
			}
			int x = prog[++registers[IP]];
			registers[reg] = x;
			printf("Register %d set to: %d", reg, x);
			break;
		}
		default: {
			fprintf(stderr, "Invalid instruction, check the instruction set !");
			loop = false;
			break;
		}
	}
}