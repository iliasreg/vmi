#include "vm.h"
#include "file_lexer.h"

#include <stdio.h>
#include <stdlib.h>

// TODO::Implement debugging helpers 
void printProg(int* prog, int progSize){
	printf("Program is: \t");
	for(int i=0; i < progSize; ++i){
		printf("%d,", prog[i]);
	}
	printf("\n");
}

int main(int argc, char** argv){

	
	/* Reading files through arguments */
	if(argc != 2){
		printf("USAGE: ./vm [FILE]\n");
		return 1;
	}
	if(verifyFile(argv[1]) == false){
		fprintf(stderr, "Invalid file extension, name you file following this format: [fileName.asi]\n");
		return 1;
	}	
	
	const char* fileName = argv[1]; 
	int progSize;
	int *prog = readProgam(fileName, &progSize);
	if(!prog){
		return 1;
	}
	
	/* VM Initialization */
	registers[IP] = 0; 	// Instruction Pointer
	registers[SP] = -1; 	// Stack Pointer
	
	//printProg(prog, progSize);

	/* Main Loop */
	while(loop){
		int inst = fetch(prog);
		eval(prog, inst);
		registers[IP]++; // Increments the IP to get the next instruction
	}

	return 0;
}
