#include "vm.h"
#include "file_lexer.h"

#include <stdlib.h>

int main(void){

	/* Main Loop */
	int progSize;
	//TODO: make it read files through arguments
	int *prog = readProgam("test.asi", &progSize);
	if(!prog){
		return 1;
	}

	/* VM Initialization */
	registers[IP] = 0; 	// Instruction Pointer
	registers[SP] = -1; 	// Stack Pointer


	/* Main Loop */
	while(loop){
		int inst = fetch(prog);
		eval(prog, inst);
		registers[IP]++; // Increments the IP to get the next instruction
	}

	return 0;
}
