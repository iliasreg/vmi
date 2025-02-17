#ifndef VM_H
#define VM_H

#include <stdbool.h>
#include <stdint.h>

// Stack
#define STACK_SIZE (1 << 8) // 8 bits = 256

// Program Size
// TODO::Could implement dynamic program reading
#define MAX_PROGRAM_SIZE 256

// Memory
#define MEMORY_SIZE (1 << 8)  // 8 bits = 256


/* Instruction Set */
typedef enum{
	PSH,
	ADD,
	SUB,
	MUL,
	DIV,
	SET,
	HLT,
	LWD,
	STO,
	POP
} InstructionSet;

/* Registers */
typedef enum{
	A,	B,	C,	D,	E, F,
	IP,	SP,
	NUM_OF_REGISTERS
} Registers;

/* GLOBAL VARIABLES */
extern bool loop;

extern int registers[];
extern int stack[STACK_SIZE];
extern int memory[MEMORY_SIZE];

/* Functions */
int fetch(int* prog);
void eval(int* prog, int inst);


#endif 