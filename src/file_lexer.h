#ifndef FILE_LEXER_H
#define FILE_LEXER_H

#include <stdbool.h>

typedef struct {
    const char* name;
    int opcode; 
} InstructionMap;


int *readProgam(const char* filename, int* progSize);
int getOpcode(const char* name);
bool checkStringToNum(char* str);
char* removeChars(char *str, const char *chars_to_remove);
bool verifyFile(char* file);

#endif