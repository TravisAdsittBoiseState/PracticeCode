#include <stdio.h>
#include <stdlib.h>
/*
 * This program is meant to emulate the Intel 8080 processor, 
 * I am going to attempt writing this on my own without any
 * online tutorial help so the first iteration is just going to 
 * be a functional thing no optimizations.
 *
 * One design choice is to make this a representation of how
 * one of my college proffessors used to grind it into our 
 * heads...
 * 	Fetch
 * 	Decode
 * 	Execute
 * So, as such I want to implement those as functions and just
 * loop on them.
 *
 * Version : 0
 *
 * Author : Travis Adsitt (Original engineering obviously done
 * 				by Intel)
 *
 * 2AUGG18
 */

#define MAX_MEM_LOC 65536



struct CPUINFO{

	//Registers
	unsigned int A  : 8; //AKA the accumulator
	unsigned int B  : 8;
	unsigned int C  : 8;
	unsigned int D  : 8;
	unsigned int E  : 8;
	unsigned int H  : 8; //H and L are used in special opcodes for 
	unsigned int L  : 8; //memory references and stack stuff
	unsigned int PC :16; 
	unsigned int SP :16; //Kind of cheating with these last two...
			     //They should be two 8 bit registers...

	//Processor Status Word (PSW)
	unsigned char Z : 1;
	unsigned char S : 1;
	unsigned char P : 1;
	unsigned char CY: 1;
	unsigned char AC: 1;
}CPUINFO;

typedef struct op_def{
	unsigned char op;
	unsigned char byte1;
	unsigned char byte2;
}op;

void loadProgram(char* filename, char *memSpace);
op* fetch(unsigned int PC);

char *memory;

int main(int argc, char**arggv){

	//Allocate maximum memory possible for 8080 Processor due to its
	//16 bit addressing.
	memory = malloc(sizeof(char) * MAX_MEM_LOC);

	if(argc >! 1){
		printf("No file specified!");
		exit(1);
	}

	loadProgram(arggv[1],memory);
	
	while(1){
	
		decode_execute(fetch(CPUINFO.PC));

	}	

	return 0;
}


/*
 * This is a helper function built to load a file into the memory space
 * for the processor to start using.
 */
void loadProgram(char* filename, char *memSpace){

	FILE *f = fopen(filename, "rb");

	if(f == NULL){
		printf("File load failure!");
		exit(1);
	}
	
	fseek(f,0L,SEEK_END);

	int size = ftell(f);

	fread(memSpace,size,1,f);
	
	fclose(f);

}

op* fetch(unsigned int PC){

	op* newOP = malloc(sizeof(op));
	
	newOP->op = memory[PC];
	newOP->byte1 = memory[PC + 1];
	newOP->byte2 = memory[PC + 2];

	return newOP;	
}

int decode_execute(op* operation){



	free(operation);

	return 0;

}
