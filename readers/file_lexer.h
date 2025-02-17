#ifndef FILE_LEXER_H
#define FILE_LEXER_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
   const char* name;
   uint8_t opcode; 
   uint8_t numOperands;
} InstructionMap;

typedef struct {
   const char* name;
   uint8_t registerCode; 
} RegisterMap;


int *readProgam(const char* filename, int* progSize);

uint8_t getOpcode(const char* name);
uint8_t getRegistercode(const char* name);
uint8_t getNumOperands(uint8_t opcode);

const char* getRegisterName(int registerCode);
const char* getInstructionName(int opcode);

bool checkStringToNum(char* str);
char* removeChars(char *str, const char *chars_to_remove);
bool verifyFile(char* file);

#endif