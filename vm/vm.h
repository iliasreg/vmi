#ifndef VM_H
#define VM_H

#include <stdbool.h>

// Stack
#define STACK_SIZE 256

// Program Size
// TODO::Could implement dynamic program reading
#define MAX_PROGRAM_SIZE 256

// Memory
#define MEMORY_SIZE 256  // 8 bits


/* Instruction Set */
typedef enum{
	HLT,
	PSH,
	ADD,
	SUB,
	MUL,
	DIV,
	POP,
	SET,
	LWD,
	STO
} InstructionSet;

/* Registers */
typedef enum{
	A,	B,	C,	D,	E, F,
	IP,	SP,
	NUM_OF_REGISTERS
} Registers;

/* GLOBAL VARIABLES */
extern bool loop;

extern int stack[STACK_SIZE];
extern int registers[];
extern int memory[MEMORY_SIZE];

/* Functions */
int fetch(int* prog);
void eval(int* prog, int inst);


#endif 