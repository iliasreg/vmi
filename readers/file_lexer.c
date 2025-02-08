#include "file_lexer.h"
#include "../vm/vm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_EXTENSION ".asi"

InstructionMap instMap[]= {
    {"PSH", PSH},
    {"ADD", ADD},
    {"SUB", SUB},
    {"MUL", MUL},
    {"DIV", DIV},
    {"SET", SET},
    {"HLT", HLT},
    {"LWD", LWD},
    {"POP", POP},
    {NULL, 0}
};

InstructionMap registerMap[]= {
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

int getOpcode(const char* name){
    for(int i = 0; instMap[i].name; i++){
        if(strcmp(name, instMap[i].name) == 0){
            return instMap[i].opcode;
        }
    }
    return -1;
}

int getRegistercode(const char* name){
    for(int i = 0; registerMap[i].name; i++){
        if(strcmp(name, registerMap[i].name) == 0){
            return registerMap[i].opcode;
        }
    }
    return -1;
}

char* removeChars(char *str, const char *chars_to_remove) {
    if (!str || !chars_to_remove) return str; // Check for NULL pointers
    
    int i = 0, j = 0;
    while (str[i]) {
        // Check if the current character is in the list of characters to remove
        if (!strchr(chars_to_remove, str[i])) {
            str[j++] = str[i]; // Keep the character
        }
        i++;
    }
    str[j] = '\0'; // Null-terminate the modified string
    return str;
}

bool checkStringToNum(char* str){
    return (strcmp(str, "0") == 0 || atoi(str) != 0) ? true : false;
}


int *readProgam(const char* filename, int* progSize){
    FILE* file = fopen(filename, "r");

    //TODO: Add check for file extension .asi 
    if(!file){
        fprintf(stderr, "Error: Could not open the file %s\n", filename);
        return NULL;
    }

    int* prog = malloc(MAX_PROGRAM_SIZE * sizeof(int));
    *progSize = 0;

    char line[256];
    while(fgets(line, sizeof(line), file)){
        // Isolating the instructions
        char* token = strtok(line, " \t\n");
        token = removeChars(token, " ;\n");
        if(!token || token[0] == ';') continue;

        // Gettingg the opcode
        int opcode = getOpcode(token);
        if(opcode == -1){
            fprintf(stderr, "Error: Invalid instruction, read the list of instructions ! \n");
            free(prog);
            fclose(file);
            return NULL;
        }

        // Adding the instruction to the array if it's validated
        prog[(*progSize)++] = opcode;
    
        // Handling instructions with operands
        if(opcode == PSH || opcode == DIV || opcode == MUL || opcode == LWD){
            token = strtok(NULL, " \t\n");
            token = removeChars(token, " ;\n");
            if(!token){
                fprintf(stderr, "Error: Missing operands for instruction %s\n", instMap[opcode].name);
                free(prog);
                fclose(file);
                return NULL;
            }

            int operand;
            if(opcode == PSH || opcode == DIV || opcode == MUL){
                if(checkStringToNum(token)){
                    operand = atoi(token);
                } else {
                        fprintf(stderr, "Error: Invalid form of operand, check the list of instructions !\n");
                        free(prog);
                        fclose(file);
                        return NULL;
                }
            } else{
                operand = getRegistercode(token);
            } 
            prog[(*progSize)++] = operand;

        } else if(opcode == SET){
            token = strtok(NULL, " \t\n");
            token = removeChars(token, " ;\n");
            if(!token){
                fprintf(stderr, "Error: Missing operands for instruction %s\n", instMap[opcode].name);
                free(prog);
                fclose(file);
                return NULL;
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
                return NULL;
            }

            // Second operand: Value
            token = strtok(NULL, " \t\n");
            if (!token) {
                fprintf(stderr, "Error: Missing value for SET.\n");
                free(prog);
                fclose(file);
                return NULL;
            }

            int value;
            if(checkStringToNum(token)){
                value = atoi(token);
            } else {
                    fprintf(stderr, "Error: Invalid form of operand, check the list of instructions !\n");
                    free(prog);
                    fclose(file);
                    return NULL;
            }

            // Add SET instruction and operands to program
            prog[(*progSize)++] = reg;
            prog[(*progSize)++] = value;
        }
    }

    fclose(file);
    // Returning pointer to the program
    return prog; 
}
