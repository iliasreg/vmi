#ifndef VM_H
#define VM_H

#include <stdbool.h>

#define STACK_SIZE 256
#define MAX_PROGRAM_SIZE 256

/* Instruction Set */
typedef enum{
	PSH,
	ADD,
	SUB,
	MUL,
	DIV,
	POP,
	SET,
	LWD,
	HLT
} InstructionSet;

/* Registers */
typedef enum{
	A,	B,	C,	D,	E, F,
	IP,	SP,
	NUM_OF_REGISTERS
} Registers;

/* GLOBAL VARIABLES */
extern bool loop;
extern int stack[];
extern int registers[];

/* Functions */
int fetch(int* prog);
void eval(int* prog, int inst);


#endif 