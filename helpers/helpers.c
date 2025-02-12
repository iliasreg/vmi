#include <stdio.h>
#include <stdlib.h>

#include "../vm/vm.h"

void addToProgram(int* array, int size, int new_element, int index) {
    for (int i = size; i > index; i--) {
        array[i] = array[i - 1];
    }
    array[index] = new_element;
}

// Prints memory contents
void printMemory(int memory[]) {
    printf("Memory:\n");
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i] != 0) { // Print only non-zero values
            printf("[0x%04X] = %d\n", i, memory[i]);
        }
    }
}

// Prints stack content
void printStack(int stack[]) {
    printf("Stack: [ ");
    for (int i = 0; i < STACK_SIZE; i++) {
        if (stack[i] != 0) { // Print only non-zero values
            printf("%d ", stack[i]);
        }
    }
    printf("]\n");
}

// Prints register X content
void printRegister(int x) {
    int valueInRegister = registers[x];
    printf("Register %d: %d", x, valueInRegister);
}
