#include <stdio.h>

/*
*
*This is a program that is meant to emulate the Intel 8080 processor.
*
*/

int main(){

	

}

/*
*
*This is a function to determine the number of bytes an OPCode requires.
*
* Buffer - a pointer to the machine instruction buffer
* PC - the offset to a position in the machine instruction buffer
*/

int numBytes(char *Buffer,int PC){

	int numBytes = 1;
	char instruction = Buffer[PC];

	switch(instruction){

		case 0xc3:
			//JMP
			numBytes = 3;
			break;

	}

	return numBytes;
	


}
