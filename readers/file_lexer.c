#include "file_lexer.h"
#include "../vm/vm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define FILE_EXTENSION ".asi"

InstructionMap instMap[]= {
    {"PSH", PSH, 1},
    {"ADD", ADD, 0},
    {"SUB", SUB, 0},
    {"MUL", MUL, 1},
    {"DIV", DIV, 1},
    {"SET", SET, 2},
    {"HLT", HLT, 0},
    {"LWD", LWD, 1},
    {"STO", STO, 1},
    {"POP", POP, 0},
    {NULL, 0, 0}
};

RegisterMap registerMap[]= {
    {"A", A},
    {"B", B},
    {"C", C},
    {"D", D},
    {"E", E},
    {"F", F},
    {"IP", IP},
    {"SP", SP},
    {NULL, 0}
};

bool verifyFile(char* file){
    if(strcmp(file, "") == 0){
        return false;
    }
    
    char ext[5];
    int fileSize = (int) strlen(file);
    for(int i = fileSize - 4, j=0; i < fileSize; i++, j++){
        ext[j] = file[i];
    }
    if(strcmp(ext, FILE_EXTENSION) == 0){
        return true;
    }
    return false;
}

uint8_t getOpcode(const char* name){
    for(uint8_t i = 0; instMap[i].name; i++){
        if(strcmp(name, instMap[i].name) == 0){
            return instMap[i].opcode;
        }
    }
    return 255;
}

const char* getRegisterName(int registerCode){
    for(uint8_t i = 0; registerMap[i].name; i++){
        if(registerCode == registerMap[i].registerCode){
            return registerMap[i].name;
        }
    }
    return "";
}

const char* getInstructionName(int opcode){
    for(uint8_t i = 0; instMap[i].name; i++){
        if(opcode == instMap[i].opcode){
            return instMap[i].name;
        }
    }
    return "";
}

uint8_t getRegistercode(const char* name){
    for(uint8_t i = 0; registerMap[i].name; i++){
        if(strcmp(name, registerMap[i].name) == 0){
            return registerMap[i].registerCode;
        }
    }
    return 255; 
}

uint8_t getNumOperands(uint8_t opcode){
    for(uint8_t i = 0; instMap[i].name; i++){
        if(opcode == instMap[i].opcode){
            return instMap[i].numOperands;
        }
    }
    return 0;
}

char* removeChars(char *str, const char *chars_to_remove) {
    if (!str || !chars_to_remove) return str;
    int i = 0, j = 0;
    while (str[i]) {
        if (!strchr(chars_to_remove, str[i])) {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
    return str;
}

bool checkStringToNum(char* str){
    return (strcmp(str, "0") == 0 || atoi(str) != 0) ? true : false;
}

bool verifyToken(char* token, uint8_t opcode, int* prog, FILE* file){
    if(!token){
        fprintf(stderr, "Error: Missing operands for instruction %s\n", getInstructionName(opcode));
        free(prog);
        fclose(file);
        return false;
    }
    return true;
}

uint8_t getOperand(char* token, uint8_t opcode, int* prog, FILE* file){
    if(opcode == PSH || opcode == DIV || opcode == MUL || opcode == STO){
        if(checkStringToNum(token)){
            return atoi(token);
        } else {
                fprintf(stderr, "Error: Invalid form of operand, check the list of instructions !\n");
                free(prog);
                fclose(file);
                return 0;
        }
    } else{
        return getRegistercode(token);
    } 
}

bool handleSet(char* token, uint8_t opcode, int* prog, FILE* file, int* progSize){
    if(!verifyToken(token, opcode, prog, file)){
        return false;
    }
            
            int reg = -1;
            if (strcmp(token, "A") == 0) reg = A;
            else if (strcmp(token, "B") == 0) reg = B;
            else if (strcmp(token, "C") == 0) reg = C;
            else if (strcmp(token, "D") == 0) reg = D;
            else if (strcmp(token, "E") == 0) reg = E;
            else if (strcmp(token, "F") == 0) reg = F;
            else {
                fprintf(stderr, "Error: Invalid register %s.\n", token);
                free(prog);
                fclose(file);
                return false;
            }

            // Second operand: Value
            token = strtok(NULL, " \t\n");
            if (!token) {
                fprintf(stderr, "Error: Missing value for SET.\n");
                free(prog);
                fclose(file);
                return false;
            }

            int value;
            if(checkStringToNum(token)){
                value = atoi(token);
            } else {
                    fprintf(stderr, "Error: Invalid form of operand, check the list of instructions !\n");
                    free(prog);
                    fclose(file);
                    return false;
            }

            // Add SET instruction and operands to program
            prog[(*progSize)++] = reg;
            prog[(*progSize)++] = value;
            return true;
        
}

int *readProgam(const char* filename, int* progSize){
    FILE* file = fopen(filename, "r");

    if(!file){
        fprintf(stderr, "Error: Could not open the file %s\n", filename);
        return NULL;
    }

    int* prog = calloc(MAX_PROGRAM_SIZE, sizeof(int));
    *progSize = 0;

    char line[256];
    while(fgets(line, sizeof(line), file)){
        // Isolating the instructions
        char* token = strtok(line, " \t\n");
        token = removeChars(token, " ;\n");
        if(!token || token[0] == ';') continue;

        // Getting the opcode
        uint8_t opcode = getOpcode(token);
        if(opcode == 255){
            fprintf(stderr, "Error: Invalid instruction, read the list of instructions ! \n");
            free(prog);
            fclose(file);
            return NULL;
        }

        // Adding the instruction to the array if it's validated
        prog[(*progSize)++] = opcode;
    
        // Handling instructions with one operand
        if(getNumOperands(opcode) == 1){
            token = strtok(NULL, " \t\n");
            token = removeChars(token, " ;\n");
            if(!verifyToken(token, opcode, prog, file)){
                return NULL;
            }

        prog[(*progSize)++] = getOperand(token, opcode, prog,file);

        // Handling SET operation
        } else if(opcode == SET){
            token = strtok(NULL, " \t\n");
            token = removeChars(token, " ;\n");
            if(!handleSet(token, opcode, prog, file, progSize)){
                return NULL;
            }
        }
    }

    fclose(file);
    // Returning pointer to the program
    return prog; 
}
