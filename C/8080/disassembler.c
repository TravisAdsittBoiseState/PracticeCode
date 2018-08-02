#include <stdio.h>
#include <stdlib.h>

/*
*
*This is a program that is meant to emulate the Intel 8080 processor.
*
*/

char decodeRegister(unsigned char op,int loc);
int numBytes(char *Buffer,int PC);
char decodeCon(unsigned char op);
char decodeRP(unsigned char op, int offset);


int main(int argc, char**argv){

	FILE *f = fopen(argv[1], "rb");
	
	if(f == NULL){
		printf("Couldn't open the file specified!\n");
		exit(1);
	}
	
	fseek(f,0L,SEEK_END);

	int size = ftell(f);
	
	rewind(f);
	
	unsigned char* buffer = malloc(size);

	fread(buffer,size,1,f);

	fclose(f);

	int PC = 0;

	while(PC<size){
		PC += numBytes(buffer,PC);
	}

}

/*
*
*This is a function to determine the number of bytes an OPCode requires.
*Also prints to console the corresponding Assembly Code to help in the 
*effort of reverse engineering the code...
*
* Buffer - a pointer to the machine instruction buffer
* PC - the offset to a position in the machine instruction buffer
*/

int numBytes(char *Buffer,int PC){

	int numBytes = 1;
	unsigned char* instruction = &Buffer[PC];
	
	printf("%04x\t",PC);

	switch(*instruction){

		case 0x00:
			//NOP
			printf("NOP\n");
			break;
                case 0x1e:
                case 0x3e:
                case 0x26:
                case 0x0e:
                case 0x2e:
                case 0x06:
                case 0x16:
			//MVI r, data
			printf("MVI %c, %#02x\n",decodeRegister(*instruction,2),instruction[1]);
			numBytes = 2;
			break;
                case 0x73:
                case 0x75:
                case 0x70:
                case 0x72:
                case 0x74:
                case 0x71:
                case 0x77:
			//MOV ADDR (H and L), r
			printf("MOV ADDR, %c\n",decodeRegister(*instruction,1));
			break;
                case 0x66:
                case 0x7e:
                case 0x4e:
                case 0x6e:
                case 0x56:
                case 0x46:
                case 0x5e:
			//MOV r, ADDR (H and L)
			printf("MOV %c, ADDR\n",decodeRegister(*instruction,2));
			break;

                case 0x31:
                case 0x21:
                case 0x01:
                case 0x11:
			//LXI rp, data
			printf("LXI %c, %#04x\n",decodeRP(*instruction, 4),((instruction[2] << 8) | instruction[1]));
			numBytes = 3;
			break;
		case 0x3a:
			//LDA addr
			printf("LDA A, %#04x\n",((instruction[2] << 8) | instruction[1]));
			numBytes = 3;
			break;
		case 0x32:
			//STA addr
			printf("STA %#04x, A\n",((instruction[2] << 8) | instruction[1]));
			numBytes = 3;
			break;
		case 0x2a:
			//LHLD addr
			printf("LHDL L, %#04x, H, %#04x\n",((instruction[2] << 8) | instruction[1]), ((instruction[2] << 8) | instruction[1]) + 1);
			numBytes = 3;
			break;
		case 0x22:
			//SHLD addr
			printf("SHDL %#04x, L, %#04x, H\n",((instruction[2] << 8) | instruction[1]), ((instruction[2] << 8) | instruction[1]) + 1);
			numBytes = 3;
			break;
                case 0x1a:
                case 0x0a:
			//LDAX rp
			printf("LDAX %c\n",decodeRP(*instruction,4));
			break;
                case 0x12:
                case 0x02:
			//STAX rp
			printf("STAX %c\n",decodeRP(*instruction,4));
			break;
		case 0xeb:
			//XCHG HL and DE
			printf("XCHG\n");
			break;
                case 0x82:
                case 0x87:
                case 0x81:
                case 0x83:
                case 0x85:
                case 0x84:
                case 0x80:
			//ADD r
			printf("ADD %c\n",decodeRegister(*instruction,1));
			break;
		case 0x86:
			//ADD M
			//The content of the memory at the HL address is added to the
			//accumulator (register A).
			printf("ADD M\n");
			break;
		case 0xc6:
			//ADI data
			printf("ADI A, %#02x\n",instruction[1]);
			numBytes = 2;
			break;
                case 0x8a:
                case 0x8b:
                case 0x89:
                case 0x8f:
                case 0x88:
                case 0x8d:
                case 0x8c:
			//ADC r
			//register A + r + Carry Bit
			printf("ADC %c\n",decodeRegister(*instruction,1));
			break;
		case 0x8e:
			//ADC M
			//register A + M(HL) + Carry Bit
			printf("ADC M");
			break;
		case 0xce:
			//ACI data
			//register A + (byte 2) + CY flag
			printf("ACI %#02x\n",instruction[1]);
			numBytes = 2;
			break;
                case 0x92:
                case 0x90:
                case 0x94:
                case 0x93:
                case 0x97:
                case 0x91:
                case 0x95:
			//SUB r
			printf("SUB %c\n",decodeRegister(*instruction,1));
			break;
		case 0x96:
			//SUB M
			printf("SUB M\n");
			break;
		case 0xd6:
			//SUI data
			printf("SUI %#02x\n",instruction[1]);
			numBytes = 2;
			break;
                case 0x9f:
                case 0x9c:
                case 0x9d:
                case 0x9a:
                case 0x9b:
                case 0x99:
                case 0x98:
			//SBB r
			printf("SBB %c\n",decodeRegister(*instruction,1));
			break;
		case 0x9e:
			//SBB M
			printf("SBB M");
			break;
		case 0xde:
			//SBI data
			printf("SBI %#02x\n",instruction[1]);
			numBytes = 2;
			break;
                case 0x1c:
                case 0x14:
                case 0x04:
                case 0x3c:
                case 0x0c:
                case 0x24:
                case 0x2c:
			//INR r
			printf("INR %c\n",decodeRegister(*instruction,2));
			break;
		case 0x34:
			//INR M
			printf("INR M\n");
			break;
                case 0x05:
                case 0x25:
                case 0x2d:
                case 0x0d:
                case 0x3d:
                case 0x1d:
                case 0x15:
			//DCR r
			printf("DCR %c\n",decodeRegister(*instruction,2));
			break;
		case 0x35:
			//DCR M
			printf("DCR M\n");
			break;
                case 0x03:
                case 0x23:
                case 0x13:
                case 0x33:
			//INX rp
			//Increment the register pairs lower by one
			printf("INX %c\n",decodeRP(*instruction,4));
			break;
                case 0x1b:
                case 0x0b:
                case 0x3b:
                case 0x2b:
			//DCX rp
			printf("DCX %c\n",decodeRP(*instruction,4));
			break;
                case 0x09:
                case 0x39:
                case 0x29:
                case 0x19:
			//DAD rp
			//Adds the register pair to the H and L registers
			printf("DAD %c\n",decodeRP(*instruction,4));
			break;
		case 0x27:
			//DAA
			//Forms two four bit Binary Coded Decimal digits from the
			//Accumulator (Register A)
			printf("DAA\n");
			break;
                case 0xa7:
                case 0xa5:
                case 0xa0:
                case 0xa1:
                case 0xa4:
                case 0xa3:
                case 0xa2:
			//ANA r
			printf("ANA %c\n",decodeRegister(*instruction,1));
			break;
		case 0xa6:
			//ANA M
			printf("ANA M\n");
			break;
		case 0xe6:
			//ANI data
			printf("ANI %#02x\n",instruction[1]);
			numBytes = 2;
			break;
                case 0xac:
                case 0xad:
                case 0xaa:
                case 0xaf:
                case 0xa8:
                case 0xab:
                case 0xa9:
			//XRA r
			printf("XRA %c\n",decodeRegister(*instruction,1));
			break;
		case 0xae:
			//XRA M
			printf("XRA M");
			break;
		case 0xee:
			//XRI data
			printf("XRI %#02x\n",instruction[1]);
			numBytes = 2;
			break;
                case 0xb1:
                case 0xb0:
                case 0xb3:
                case 0xb7:
                case 0xb4:
                case 0xb2:
                case 0xb5:
			//ORA r
			printf("ORA %c\n",decodeRegister(*instruction,1));
			break;
		case 0xf6:
			//ORI data
			printf("ORI %#02x\n",instruction[1]);
			numBytes = 2;
			break;
                case 0xbc:
                case 0xbb:
                case 0xb8:
                case 0xbd:
                case 0xb9:
                case 0xbf:
                case 0xba:
			//CMP r
			printf("CMP %c\n",decodeRegister(*instruction,1));
			break;
		case 0xbe:
			//CMP M
			printf("CMP M");
			break;
		case 0xfe:
			//CPI data
			printf("CPI %#02x\n",instruction[1]);
			numBytes = 2;
			break;
		case 0x07:
			//RLC
			printf("RLC\n");
			break;
		case 0x0f:
			//RRC
			printf("RRC\n");
			break;
		case 0x17:
			//RAL
			printf("RAL\n");
			break;
		case 0x1f:
			//RAR
			printf("RAR\n");
			break;
		case 0x2f:
			//CMA
			printf("CMA\n");
			break;
		case 0x3f:
			//CMC
			printf("CMC\n");
			break;
		case 0x37:
			//STC
			printf("STC\n");
			break;	
		case 0x36:
			//MVI ADDR (H and L), r 
			printf("MVI M, %#02x\n",instruction[1]);
			numBytes = 2;
			break;
		case 0xc3:
			//JMP
			printf("JMP %#04x\n",((instruction[2] << 8) | instruction[1]));
			numBytes = 3;
			break;
                case 0xda:
                case 0xe2:
                case 0xea:
                case 0xf2:
                case 0xc2:
                case 0xd2:
                case 0xfa:
                case 0xca:
			//JMPCON
			printf("JMPCON %c %#04x\n",decodeCon(*instruction),((instruction[2] << 8) | instruction[1]));
			numBytes = 3;
			break;
		case 0xcd:
			//CALL addr
			printf("CALL %#04x\n",instruction[2] << 8 | instruction[1]);
			numBytes = 3;
			break;
                case 0xd4:
                case 0xec:
                case 0xfc:
                case 0xdc:
                case 0xcc:
                case 0xc4:
                case 0xe4:
                case 0xf4:
			//Ccondition addr
			//It seems this pushes the PC onto the stack and places
			//the address of the following bytes into the PC if the
			//condition is true.
			printf("CONCALL %c, %#04x\n",decodeCon(*instruction),instruction[2] << 8 | instruction[1]);
			numBytes = 3;
			break;
		case 0xc9:
			//RET
			//Pulls an address off the stack and puts it in the PC
			printf("RET\n");
			break;
                case 0xe8:
                case 0xf8:
                case 0xd8:
                case 0xf0:
                case 0xc8:
                case 0xe0:
                case 0xc0:
                case 0xd0:
			//Rcondition
			printf("RCON %c\n",decodeCon(*instruction));
			break;
                case 0xef:
                case 0xf7:
                case 0xe7:
                case 0xdf:
                case 0xc7:
                case 0xd7:
                case 0xff:
                case 0xcf:
			//RST
			//This function takes the current PC address and puts
			//it on the stack, then takes the NNN of the opcode
			//
			//   11NNN111
			//
			//multiplies it by 8 and puts that into the PC. I 
			//had no idea this is what a soft reset did... seems
			//like its not much of a reset at all....
			printf("RST %#02x\n",((*instruction >> 3) & ~(3 << 3)));
			break;
		case 0xe9:
			printf("PCHL\n");
			break;
                case 0xe5:
                case 0xd5:
                case 0xc5:
			//PUSH rp
			printf("PUSH %c %d\n",decodeRP(*instruction,4),(*instruction >> 4) & 3);
			break;
		case 0xf5:
			//PUSH PSW
			printf("PUSH PSW\n");
			break;
                case 0xc1:
                case 0xd1:
                case 0xe1:
			//POP rp
			printf("POP %c %d\n",decodeRP(*instruction,4),(*instruction >> 4) & 3);
			break;
		case 0xf1:
			//POP PSW
			printf("POP PSW\n");
			break;
		case 0xe3:
			//XTHL Exchange stack top with H and L
			printf("XTHL\n");
			break;
		case 0xf9:
			//SPHL Stack fills H and L
			printf("SPHL\n");
			break; 
		case 0xdb:
			//IN port
			printf("READ INPUT\n");
			break;
		case 0xd3:
			//OUT port
			printf("SEND OUTPUT\n");
			break;
		case 0xfb:
			//ENABLE INTERUPTS
			printf("ENABLE INTERUPTS\n");
			break;
		case 0xf3:
			//DISABLE INTERUPTS
			printf("DISABLE INTERUPTS\n");
			break;
		case 0x76:
			//HALT
			printf("HALT");
			break;
                case 0x5b:
                case 0x5a:
                case 0x59:
                case 0x58:
                case 0x5f:
                case 0x5c:
                case 0x5d:
                case 0x53:
                case 0x52:
                case 0x51:
                case 0x50:
                case 0x57:
                case 0x54:
                case 0x55:
                case 0x4b:
                case 0x4a:
                case 0x49:
                case 0x48:
                case 0x4f:
                case 0x4c:
                case 0x4d:
                case 0x43:
                case 0x42:
                case 0x41:
                case 0x40:
                case 0x47:
                case 0x44:
                case 0x45:
                case 0x7b:
                case 0x7a:
                case 0x79:
                case 0x78:
                case 0x7f:
                case 0x7c:
                case 0x7d:
                case 0x63:
                case 0x62:
                case 0x61:
                case 0x60:
                case 0x67:
                case 0x64:
                case 0x65:
                case 0x6b:
                case 0x6a:
                case 0x69:
                case 0x68:
                case 0x6f:
                case 0x6c:
                case 0x6d:
			//MOV r1, r2
			printf("MOV %c, %c\n",decodeRegister(*instruction,2),decodeRegister(*instruction,1));
			break;
		default:
			printf("\n");
			break;
	}

	return numBytes;
	


}

/*
 * This is a helper function to decode the register pair in a 
 * opcode, makes the assembly more readable for reverse engineering.
 */
char decodeRP(unsigned char op, int offset){

	unsigned char retVal = (op >> offset) & 3;

	switch(retVal){

		case 0:
			retVal = 'B';
			break;
		case 1:
			retVal = 'D';
			break;
		case 2:
			retVal = 'H';
			break;
		case 3:
			retVal = 'S';
			break;

	} 

	return retVal;

}

/*
 * This is a function to help with the disassembly by allowing for smaller
 * case statements in the numBytes function.
 *
 * loc 1 - SSS
 * loc 2 - DDD
 *
 */
char decodeRegister(unsigned char op,int loc){

	unsigned char retVal = 0x36;
	unsigned char mask = 0x07;

	switch(loc){
	
		case 1:
			retVal =  op & mask;
			break;
		case 2:
			mask = (mask << 3);
			retVal = (op & mask) >> 3;
			break;

	}
	
	switch(retVal){
		case 7:
			retVal = 'A';
			break;
		case 0:
			retVal = 'B';
			break;
		case 1:
			retVal = 'C';
			break;
		case 2:
			retVal = 'D';
			break;
		case 3:
			retVal = 'E';
			break;
		case 4:
			retVal = 'H';
			break;
		case 5:
			retVal = 'L';
			break;
	}

	return retVal;

}

/*
 * This is a helper function to decode the conditional that a jump
 * statement is looking for.
 *
 */
char decodeCon(unsigned char op){

	unsigned char retVal = 0x08;
	unsigned char mask = 0x07 << 3;

	retVal = (op & mask) >> 3;

	switch(retVal){

		case 0x00:
		case 0x01:
			retVal = 'Z';
			break;
		case 0x02:
		case 0x03:
			retVal = 'C';
			break;
		case 0x04:
		case 0x05:
			retVal = 'P';
			break;
		case 0x06:
		case 0x07:
			retVal = 'S';
			break;
		case 0x08:
			retVal = 'E';
			break;
	}

	return retVal;
}
