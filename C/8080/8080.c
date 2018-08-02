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



struct CPUINFO
{

  //Registers
  unsigned int A:8;		//AKA the accumulator
  unsigned int B:8;
  unsigned int C:8;
  unsigned int D:8;
  unsigned int E:8;
  unsigned int H:8;		//H and L are used in special opcodes for 
  unsigned int L:8;		//memory references and stack stuff
  unsigned int PC:16;
  unsigned int SP:16;		//Kind of cheating with these last two...
  //They should be two 8 bit registers...

  //Processor Status Word (PSW)
  unsigned char Z:1;
  unsigned char S:1;
  unsigned char P:1;
  unsigned char CY:1;
  unsigned char AC:1;
} CPUINFO;

typedef struct op_def
{
  unsigned char op;
  unsigned char byte1;
  unsigned char byte2;
} op;

void loadProgram (char *filename, char *memSpace);
op *fetch (unsigned int PC);

char *memory;

int
main (int argc, char **arggv)
{

  //Allocate maximum memory possible for 8080 Processor due to its
  //16 bit addressing.
  memory = malloc (sizeof (char) * MAX_MEM_LOC);

  if (argc > !1)
    {
      printf ("No file specified!");
      exit (1);
    }

  loadProgram (arggv[1], memory);

  while (1)
    {

      decode_execute (fetch (CPUINFO.PC));

    }

  return 0;
}


/*
 * This is a helper function built to load a file into the memory space
 * for the processor to start using.
 */
void
loadProgram (char *filename, char *memSpace)
{

  FILE *f = fopen (filename, "rb");

  if (f == NULL)
    {
      printf ("File load failure!");
      exit (1);
    }

  fseek (f, 0L, SEEK_END);

  int size = ftell (f);

  fread (memSpace, size, 1, f);

  fclose (f);

}

unsigned char
MEM(unsigned int loc){
	return memory[loc];
}

op *
fetch (unsigned int PC)
{

  op *newOP = malloc (sizeof (op));

  newOP->op = memory[PC];
  newOP->byte1 = memory[PC + 1];
  newOP->byte2 = memory[PC + 2];

  return newOP;
}

void
loadRegister(unsigned char reg, unsigned char val){

	switch(reg){

		case 0x07:
			CPUINFO.A = val;
		case 0x00:
			CPUINFO.B = val;
		case 0x01:
			CPUINFO.C = val;
		case 0x02:
			CPUINFO.D = val;
		case 0x03:
			CPUINFO.E = val;
		case 0x04:
			CPUINFO.H = val;
		case 0x05:
			CPUINFO.L = val;
	}
}

void
loadMemory(unsigned char reg, unsigned int loc){

	switch(reg){

		case 0x07:
			memory[loc] = CPUINFO.A;
		case 0x00:
			memory[loc] = CPUINFO.B;
		case 0x01:
			memory[loc] = CPUINFO.C;
		case 0x02:
			memory[loc] = CPUINFO.D;
		case 0x03:
			memory[loc] = CPUINFO.E;
		case 0x04:
			memory[loc] = CPUINFO.H;
		case 0x05:
			memory[loc] = CPUINFO.L;
	}
}

unsigned char 
regVal(unsigned char reg){

	switch(reg){

		case 0x07:
			return CPUINFO.A;
		case 0x00:
			return CPUINFO.B;
		case 0x01:
			return CPUINFO.C;
		case 0x02:
			return CPUINFO.D;
		case 0x03:
			return CPUINFO.E;
		case 0x04:
			return CPUINFO.H;
		case 0x05:
			return CPUINFO.L;
	}


}

void
regToReg(unsigned char r1, unsigned char r2){

	switch(r1){

		case 0x07:
			CPUINFO.A = regVal(r2);
		case 0x00:
			CPUINFO.B = regVal(r2);
		case 0x01:
			CPUINFO.C = regVal(r2);
		case 0x02:
			CPUINFO.C = regVal(r2);
		case 0x03:
			CPUINFO.E = regVal(r2);
		case 0x04:
			CPUINFO.H = regVal(r2);
		case 0x05:
			CPUINFO.L = regVal(r2);
	}

}

int
MOV(op* operation){

	unsigned char mask = 0x07;
	unsigned char op = operation->op;
	unsigned char SSS = op & mask;
	unsigned char DDD = ((op & ~mask) >> 3) & mask;
	
	if(op & mask == 6){
		op = (op & (mask << 3)) >> 3;
		loadRegister(op,MEM((CPUINFO.H << 4) | CPUINFO.L));
	}else if(op & ~(mask) == 112){
		op = (op & mask);
		loadMemory(op, (CPUINFO.H << 4) | CPUINFO.L);
	}else{
		regToReg(DDD,SSS);
	}

}


int
decode_execute (op * operation)
{


  switch (operation->op)
    {

    case 0x00:
      //NOP
      CPUINFO.PC++;
      break;
    case 0x1e:
    case 0x3e:
    case 0x26:
    case 0x0e:
    case 0x2e:
    case 0x06:
    case 0x16:
      //MVI r, data
      break;
    case 0x31:
    case 0x21:
    case 0x01:
    case 0x11:
      //LXI rp, data
      break;
    case 0x3a:
      //LDA addr
      break;
    case 0x32:
      //STA addr
      break;
    case 0x2a:
      //LHLD addr
      break;
    case 0x22:
      //SHLD addr
      break;
    case 0x1a:
    case 0x0a:
      //LDAX rp
      break;
    case 0x12:
    case 0x02:
      //STAX rp
      break;
    case 0xeb:
      //XCHG HL and DE
      break;
    case 0x82:
    case 0x87:
    case 0x81:
    case 0x83:
    case 0x85:
    case 0x84:
    case 0x80:
      //ADD r
      break;
    case 0x86:
      //ADD M
      //The content of the memory at the HL address is added to the
      //accumulator (register A).
      break;
    case 0xc6:
      //ADI data
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
      break;
    case 0x8e:
      //ADC M
      //register A + M(HL) + Carry Bit
      break;
    case 0xce:
      //ACI data
      //register A + (byte 2) + CY flag
      break;
    case 0x92:
    case 0x90:
    case 0x94:
    case 0x93:
    case 0x97:
    case 0x91:
    case 0x95:
      //SUB r
      break;
    case 0x96:
      //SUB M
      break;
    case 0xd6:
      //SUI data
      break;
    case 0x9f:
    case 0x9c:
    case 0x9d:
    case 0x9a:
    case 0x9b:
    case 0x99:
    case 0x98:
      //SBB r
      break;
    case 0x9e:
      //SBB M
      break;
    case 0xde:
      //SBI data
      break;
    case 0x1c:
    case 0x14:
    case 0x04:
    case 0x3c:
    case 0x0c:
    case 0x24:
    case 0x2c:
      //INR r
      break;
    case 0x34:
      //INR M
      break;
    case 0x05:
    case 0x25:
    case 0x2d:
    case 0x0d:
    case 0x3d:
    case 0x1d:
    case 0x15:
      //DCR r
      break;
    case 0x35:
      //DCR M
      break;
    case 0x03:
    case 0x23:
    case 0x13:
    case 0x33:
      //INX rp
      //Increment the register pairs lower by one
      break;
    case 0x1b:
    case 0x0b:
    case 0x3b:
    case 0x2b:
      //DCX rp
      break;
    case 0x09:
    case 0x39:
    case 0x29:
    case 0x19:
      //DAD rp
      //Adds the register pair to the H and L registers
      break;
    case 0x27:
      //DAA
      //Forms two four bit Binary Coded Decimal digits from the
      //Accumulator (Register A)
      break;
    case 0xa7:
    case 0xa5:
    case 0xa0:
    case 0xa1:
    case 0xa4:
    case 0xa3:
    case 0xa2:
      //ANA r
      break;
    case 0xa6:
      //ANA M
      break;
    case 0xe6:
      //ANI data
      break;
    case 0xac:
    case 0xad:
    case 0xaa:
    case 0xaf:
    case 0xa8:
    case 0xab:
    case 0xa9:
      //XRA r
      break;
    case 0xae:
      //XRA M
      break;
    case 0xee:
      //XRI data
      break;
    case 0xb1:
    case 0xb0:
    case 0xb3:
    case 0xb7:
    case 0xb4:
    case 0xb2:
    case 0xb5:
      //ORA r
      break;
    case 0xf6:
      //ORI data
      break;
    case 0xbc:
    case 0xbb:
    case 0xb8:
    case 0xbd:
    case 0xb9:
    case 0xbf:
    case 0xba:
      //CMP r
      break;
    case 0xbe:
      //CMP M
      break;
    case 0xfe:
      //CPI data
      break;
    case 0x07:
      //RLC
      break;
    case 0x0f:
      //RRC
      break;
    case 0x17:
      //RAL
      break;
    case 0x1f:
      //RAR
      break;
    case 0x2f:
      //CMA
      break;
    case 0x3f:
      //CMC
      break;
    case 0x37:
      //STC
      break;
    case 0x36:
      //MVI ADDR (H and L), r 
      break;
    case 0xc3:
      //JMP
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
      break;
    case 0xcd:
      //CALL addr
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
      break;
    case 0xc9:
      //RET
      //Pulls an address off the stack and puts it in the PC
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
      break;
    case 0xe9:
      break;
    case 0xe5:
    case 0xd5:
    case 0xc5:
      //PUSH rp
      break;
    case 0xf5:
      //PUSH PSW
      break;
    case 0xc1:
    case 0xd1:
    case 0xe1:
      //POP rp
      break;
    case 0xf1:
      //POP PSW
      break;
    case 0xe3:
      //XTHL Exchange stack top with H and L
      break;
    case 0xf9:
      //SPHL Stack fills H and L
      break;
    case 0xdb:
      //IN port
      break;
    case 0xd3:
      //OUT port
      break;
    case 0xfb:
      //ENABLE INTERUPTS
      break;
    case 0xf3:
      //DISABLE INTERUPTS
      break;
    case 0x76:
      //HALT
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
    case 0x73:
    case 0x75:
    case 0x70:
    case 0x72:
    case 0x74:
    case 0x71:
    case 0x77:
    case 0x66:
    case 0x7e:
    case 0x4e:
    case 0x6e:
    case 0x56:
    case 0x46:
    case 0x5e:
      MOV(operation);
      break;
    }

  free (operation);

  return 0;

}
