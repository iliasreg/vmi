#ifndef FILE_LEXER_H
#define FILE_LEXER_H

#include <stdbool.h>
#include <stdint.h>

// Maybe would add an integer to keep track of operands required by each instruction
typedef struct {
    const char* name;
    uint16_t opcode; 
    //uint16_t operands; // number of required operands
} InstructionMap;


int *readProgam(const char* filename, int* progSize);
uint16_t getOpcode(const char* name);
uint16_t getRegistercode(const char* name);
char* getRegisterName(int opcode);
bool checkStringToNum(char* str);
char* removeChars(char *str, const char *chars_to_remove);
bool verifyFile(char* file);

#endif