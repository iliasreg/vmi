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
			printf("--Loaded Value %d from Register %d\n", valueToLoad, loadFromRegister);
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
				fprintf(stderr, "Error: Stack Underflow !\n");
				loop = false;
				break;
			}
			int res = stack[registers[SP]--] + stack[registers[SP]--];
			stack[++registers[SP]] = res;
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
			printf("--Register %d set to: %d\n", reg, x);
			break;
		}
		default: {
			fprintf(stderr, "Invalid instruction, check the instruction set !\n");
			loop = false;
			break;
		}
	}
}