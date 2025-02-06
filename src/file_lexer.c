#include "file_lexer.h"
#include "vm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

InstructionMap instMap[]= {
    {"PSH", PSH},
    {"ADD", ADD},
    {"SET", SET},
    {"HLT", HLT},
    {"POP", POP},
    {NULL, 0}
};

int getOpcode(const char* name){
    for(int i = 0; instMap[i].name; i++){
        if(strcmp(name, instMap[i].name) == 0){
            return instMap[i].opcode;
        }
    }
    return -1;
}
bool checkStringToNum(char* str){
    return (strcmp(str, "0") || atoi(str) != 0) ? true : false;
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
        char* token = strtok(line, " /t/n");
        token = removeChars(token, ";\n");
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
        if(opcode == PSH || opcode == SET || opcode == ADD){
            token = strtok(NULL, " /t/n");
            token = removeChars(token, ";\n");
            if(!token){
                fprintf(stderr, "Error: Missing operands for instruction %s\n", instMap[opcode].name);
                free(prog);
                fclose(file);
                return NULL;
            }
            if(checkStringToNum(token)){
                int operand = atoi(token); 
                prog[(*progSize)++] = operand;
            } else {
                    fprintf(stderr, "Error: Invalid form of operand, check the list of instructions !\n");
                    free(prog);
                    fclose(file);
                    return NULL;
            }
        }
    }

    fclose(file);
    // Returning pointer to the program
    return prog; 
}
