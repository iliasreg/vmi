#ifndef FILE_LEXER_H
#define FILE_LEXER_H

#include <stdbool.h>

// Maybe would add an integer to keep track of operands required by each instruction
typedef struct {
    const char* name;
    int opcode; 
} InstructionMap;


int *readProgam(const char* filename, int* progSize);
int getOpcode(const char* name);
int getRegistercode(const char* name);
bool checkStringToNum(char* str);
char* removeChars(char *str, const char *chars_to_remove);
bool verifyFile(char* file);

#endif