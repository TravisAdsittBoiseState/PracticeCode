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

#define MAX_MEM_LOC 0xffff



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

enum REG
{ B, C, D, E, H, L, A = 7 };

void loadProgram (char *filename, char **memSpace);
op *fetch (unsigned int PC);
unsigned char addReg (unsigned char reg, int val);
unsigned char subReg (unsigned char reg, int val);
unsigned char regVal (unsigned char reg);
void loadRegister (unsigned char reg, unsigned char val);
unsigned char subReg (unsigned char reg, int val);
void printCPUStatus ();
unsigned char *memory;

int
main (int argc, char **arggv)
{

  //Allocate maximum memory possible for 8080 Processor due to its
  //16 bit addressing.
  memory = malloc (sizeof (unsigned char) * MAX_MEM_LOC);

  if (argc < 1)
    {
      printf ("No file specified!");
      exit (1);
    }

  //loadProgram (arggv[1], &memory);
  /*FILE *f = fopen(arggv[1], "rb");

     if(f == NULL){
     printf("Couldn't open the file specified!\n");
     exit(1);
     }

     fseek(f,0L,SEEK_END);

     int size = ftell(f);

     fseek(f,0,SEEK_SET);

     fread(memory,size,1,f);

     fclose(f);




     while (1)
     {
     op* operation = fetch (CPUINFO.PC);
     decode_execute (operation);

     }
   */

  //Testing functions

  int in = 1;
  printf ("Setting register A to 0\n");
  loadRegister (A, 0);

  printCPUStatus ();

  while (in > 0)
    {

      printf ("Enter an int to add to register A...\n");
      scanf ("%d", &in);
      CPUINFO.A = addReg (A, in);
      printCPUStatus ();



    }
  in = 1;
  while (in > 0)
    {

      printf ("Enter an int to sub to register A...\n");
      scanf ("%d", &in);
      CPUINFO.A = subReg (A, in);
      printCPUStatus ();



    }

  return 0;
}

void
printCPUStatus ()
{

  int i = 0;

  printf ("Registers A-L values:\n");
  for (i = 0; i < 8; i++)
    {

      if (i != 6)
	{
	  printf ("%d\n", regVal (i));
	}

    }

  printf ("Flag Z : %d\n", CPUINFO.Z);
  printf ("Flag S : %d\n", CPUINFO.S);
  printf ("Flag P : %d\n", CPUINFO.P);
  printf ("Flag CY : %d\n", CPUINFO.CY);
  printf ("Flag AC : %d\n", CPUINFO.AC);



}

void
setParity (unsigned char val)
{

  unsigned char valI = val;
  unsigned int count;

  while (valI > 0)
    {

      if ((valI & 1) > 0)
	count++;
      valI = valI >> 1;

    }

  CPUINFO.P = count % 2;
}

/*
 * This is a helper function built to load a file into the memory space
 * for the processor to start using.
 */
void
loadProgram (char *filename, char **memSpace)
{

  FILE *f = fopen (filename, "rb");

  if (f == NULL)
    {
      printf ("File load failure!");
      exit (1);
    }

  fseek (f, 0L, SEEK_END);

  int size = ftell (f);

  rewind (f);


  fread (*memSpace, size, 1, f);

  fclose (f);

}

unsigned char
MEM (unsigned int loc)
{
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
loadRegister (unsigned char reg, unsigned char val)
{

  switch (reg)
    {

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
loadMemory (unsigned char reg, unsigned int loc)
{

  switch (reg)
    {

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
regVal (unsigned char reg)
{

  switch (reg)
    {

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

unsigned int
regPairVal (unsigned char rp)
{

  unsigned int retVal;

  switch (rp)
    {
    case 0x00:
      retVal = CPUINFO.B << 8 | CPUINFO.C;
      break;
    case 0x01:
      retVal = CPUINFO.D << 8 | CPUINFO.E;
      break;
    case 0x02:
      retVal = CPUINFO.H << 8 | CPUINFO.L;
      break;
    case 0x03:
      retVal = CPUINFO.SP;
      break;
    }

  return retVal;
}

void
loadRegPair (unsigned char rp, unsigned int val)
{

  unsigned char high = val >> 8;
  unsigned char low = val & 0xff;

  switch (rp)
    {
    case 0x00:
      CPUINFO.B = high;
      CPUINFO.C = low;
      break;
    case 0x01:
      CPUINFO.D = high;
      CPUINFO.E = low;
      break;
    case 0x02:
      CPUINFO.H = high;
      CPUINFO.L = low;
      break;
    case 0x03:
      CPUINFO.SP = val;
      break;
    }


}

void
regToReg (unsigned char r1, unsigned char r2)
{

  switch (r1)
    {

    case 0x07:
      CPUINFO.A = regVal (r2);
    case 0x00:
      CPUINFO.B = regVal (r2);
    case 0x01:
      CPUINFO.C = regVal (r2);
    case 0x02:
      CPUINFO.C = regVal (r2);
    case 0x03:
      CPUINFO.E = regVal (r2);
    case 0x04:
      CPUINFO.H = regVal (r2);
    case 0x05:
      CPUINFO.L = regVal (r2);
    }

}

int
MOV (op * operation)
{

  unsigned char mask = 0x07;
  unsigned char op = operation->op;
  unsigned char SSS = op & mask;
  unsigned char DDD = ((op & ~mask) >> 3) & mask;

  if (op & mask == 6)
    {
      op = (op & (mask << 3)) >> 3;
      loadRegister (op, MEM ((CPUINFO.H << 8) | CPUINFO.L));
    }
  else if (op & ~(mask) == 112)
    {
      op = (op & mask);
      loadMemory (op, (CPUINFO.H << 8) | CPUINFO.L);
    }
  else
    {
      regToReg (DDD, SSS);
    }

}

void
LXI (op * operation)
{

  unsigned char rp = (operation->op >> 4) & 3;

  switch (rp)
    {

    case 0x00:
      CPUINFO.B = operation->byte2;
      CPUINFO.C = operation->byte1;
    case 0x01:
      CPUINFO.D = operation->byte2;
      CPUINFO.E = operation->byte1;
    case 0x02:
      CPUINFO.H = operation->byte2;
      CPUINFO.L = operation->byte1;
    case 0x03:
      CPUINFO.SP = (operation->byte2 << 8) | operation->byte1;
    }

}

void
AX (op * operation)
{

  unsigned char op = operation->op & 0x0f;
  unsigned char rp = (operation->op >> 4) & 3;
  unsigned int loc;

  switch (rp)
    {
    case 0x00:
      loc = CPUINFO.B << 8 | CPUINFO.C;
      break;
    case 0x01:
      loc = CPUINFO.D << 8 | CPUINFO.E;
      break;
    }

  switch (op)
    {
    case 0x0a:
      //LDAX
      loadRegister (A, MEM (loc));
      break;
    case 0x02:
      //STAX
      loadMemory (A, loc);
      break;
    }

}

unsigned char
subReg (unsigned char reg, int val)
{

  unsigned char retVal;

  retVal = regVal (reg) - val;

  if (regVal (reg) < val)
    {
      CPUINFO.CY = 1;		//Not sure if I should correct the bit
      //or not...
    }
  else
    {
      CPUINFO.CY = 0;
    }
  //Making an assumption here that the auxiliary carry bit 
  //behaves the same way as the carry bit just on the lower
  //four bits.
  if ((regVal (reg) & 0x0f) < val & 0x0f)
    {

      CPUINFO.AC = 1;

    }
  else
    {
      CPUINFO.AC = 0;
    }

  CPUINFO.S = retVal >> 7;

  if (retVal == 0)
    {
      CPUINFO.Z = 1;
    }
  else
    {
      CPUINFO.Z = 0;
    }

  setParity (retVal);

  return retVal;

}

unsigned char
addReg (unsigned char reg, int val)
{

  //We look at the 6th bit to see if it was carried into the 7th bit
  //after addition.
  int carry = (regVal (reg) >> 6) & 0x01;
  int carryA;

  int auxC = (regVal (reg) >> 2) & 0x01;
  int auxCA;


  unsigned char retVal;

  retVal = regVal (reg) + val;

  carryA = (retVal >> 6) & 0x01;
  auxCA = (retVal >> 2) & 0x01;

  if (carry > carryA)
    {
      CPUINFO.CY = 1;		//Not sure if I should correct the bit
      //or not...
    }
  else
    {
      CPUINFO.CY = 0;
    }
  if (auxC > auxCA)
    {

      CPUINFO.AC = 1;

    }
  else
    {
      CPUINFO.AC = 0;
    }
  if (retVal >> 7 == 1)
    {
      CPUINFO.S = 1;

    }
  else
    {
      CPUINFO.S = 0;
    }
  if (retVal == 0)
    {
      CPUINFO.Z = 1;
    }
  else
    {
      CPUINFO.Z = 0;
    }

  setParity (retVal);

  return retVal;

}

int
checkCondition(unsigned char cond){

switch(cond){

	case 0:
		return CPUINFO.Z == 0;
		break;
	case 1:
		return CPUINFO.Z == 1;
		break;
	case 2:
		return CPUINFO.CY == 0;
		break;
	case 3:
		return CPUINFO.CY == 1;
		break;
	case 4:
		return CPUINFO.P == 0;
		break;
	case 5:
		return CPUINFO.P == 1;
		break;
	case 6:
		return CPUINFO.S == 0;
		break;
	case 7:
		return CPUINFO.S == 1;
		break;
	}

}



void setFlags(unsigned char from, unsigned char to){

  if (to > from)
    {

      CPUINFO.AC = 1;

    }
  else
    {
      CPUINFO.AC = 0;
    }
  if (to >> 7 == 1)
    {
      CPUINFO.S = 1;

    }
  else
    {
      CPUINFO.S = 0;
    }
  if (to == 0)
    {
      CPUINFO.Z = 1;
    }
  else
    {
      CPUINFO.Z = 0;
    }

  setParity(to);

}

int
decode_execute (op * operation)
{
  unsigned int loc;

  switch (operation->op)
    {

    case 0x00:
      //NOP
      CPUINFO.PC++;
      break;
    case 0x26:
      //This is a special case for move immediate operation.....
      memory[CPUINFO.H << 4 | CPUINFO.L] = operation->byte1;
    case 0x1e:
    case 0x3e:
    case 0x0e:
    case 0x2e:
    case 0x06:
    case 0x16:
      //MVI r, data
      loadRegister ((operation->op >> 3) & 7, operation->byte1);
      CPUINFO.PC += 2;
      break;
    case 0x31:
    case 0x21:
    case 0x01:
    case 0x11:
      //LXI rp, data
      LXI (operation);
      CPUINFO.PC += 3;
      break;
    case 0x3a:
      //LDA addr
      loc = operation->byte2 << 4 | operation->byte1;
      loadRegister (0x03, MEM (loc));
      CPUINFO.PC += 3;
      break;
    case 0x32:
      //STA addr
      loc = operation->byte2 << 4 | operation->byte1;
      loadMemory (0x03, loc);
      CPUINFO.PC += 3;
      break;
    case 0x2a:
      //LHLD addr
      loc = operation->byte2 << 4 | operation->byte1;
      CPUINFO.H = MEM (loc + 1);
      CPUINFO.L = MEM (loc);
      CPUINFO.PC += 3;
      break;
    case 0x22:
      //SHLD addr
      loc = operation->byte2 << 4 | operation->byte1;
      loadMemory (H, loc);
      CPUINFO.PC += 3;
      break;
    case 0x1a:
    case 0x0a:
    case 0x12:
    case 0x02:
      //AX rp
      AX (operation);
      CPUINFO.PC++;
      break;
    case 0xeb:
      //XCHG HL and DE
      //Abusing loc as a temp variable here.
      loc = CPUINFO.H;
      CPUINFO.H = CPUINFO.D;
      CPUINFO.D = loc;

      loc = CPUINFO.L;
      CPUINFO.L = CPUINFO.E;
      CPUINFO.E = loc;
      CPUINFO.PC++;
      break;
    case 0x82:
    case 0x87:
    case 0x81:
    case 0x83:
    case 0x85:
    case 0x84:
    case 0x80:
      //ADD r
      CPUINFO.A = addReg (A, regVal (operation->op & 7));
      CPUINFO.PC++;
      break;
    case 0x86:
      //ADD M
      loc = (CPUINFO.H << 4) | CPUINFO.L;
      CPUINFO.A = addReg (A, MEM (loc));
      CPUINFO.PC++;
      //The content of the memory at the HL address is added to the
      //accumulator (register A).
      break;
    case 0xc6:
      //ADI data
      CPUINFO.A = addReg(A,operation->byte1);
      CPUINFO.PC += 2;
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
      CPUINFO.A = addReg(A,regVal (operation->op & 7) + CPUINFO.CY);
      CPUINFO.PC++;
      break;
    case 0x8e:
      //ADC M
      //register A + M(HL) + Carry Bit
      loc = CPUINFO.H << 4 | CPUINFO.L;
      CPUINFO.A = addReg(A,MEM (loc) + CPUINFO.CY);
      CPUINFO.PC++;
      break;
    case 0xce:
      //ACI data
      //register A + (byte 2) + CY flag
      CPUINFO.A = addReg(A,operation->byte1 + CPUINFO.CY);
      CPUINFO.PC += 2;
      break;
    case 0x92:
    case 0x90:
    case 0x94:
    case 0x93:
    case 0x97:
    case 0x91:
    case 0x95:
      //SUB r
      CPUINFO.A = subReg(A,regVal (operation->op & 7));
      CPUINFO.PC++;
      break;
    case 0x96:
      //SUB M
      loc = CPUINFO.H << 4 | CPUINFO.L;
      CPUINFO.A = subReg(A,MEM (loc));
      CPUINFO.PC++;
      break;
    case 0xd6:
      //SUI data
      CPUINFO.A = subReg(A,operation->byte1);
      CPUINFO.PC += 2;
      break;
    case 0x9f:
    case 0x9c:
    case 0x9d:
    case 0x9a:
    case 0x9b:
    case 0x99:
    case 0x98:
      //SBB r
      CPUINFO.A = subReg(A,regVal (operation->op & 7) - CPUINFO.CY);
      CPUINFO.PC++;
      break;
    case 0x9e:
      //SBB M
      loc = CPUINFO.H << 8 | CPUINFO.L;
      CPUINFO.A = subReg(A,MEM (loc) - CPUINFO.CY);
      CPUINFO.PC++;
      break;
    case 0xde:
      //SBI data
      CPUINFO.A = subReg(A,operation->byte1);
      CPUINFO.PC += 2;
      break;
    case 0x1c:
    case 0x14:
    case 0x04:
    case 0x3c:
    case 0x0c:
    case 0x24:
    case 0x2c:
      //INR r
      loc = operation->op >> 3 & 7;
      loadRegister (loc, addReg(loc,1));
      CPUINFO.PC++;
      break;
    case 0x34:
      //INR M
      loc = CPUINFO.H << 8 | CPUINFO.L;
      loc = memory[loc];
      setFlags(loc, loc + 1);
      memory[CPUINFO.H << 8 | CPUINFO.L]++;
      CPUINFO.PC++;
      break;
    case 0x05:
    case 0x25:
    case 0x2d:
    case 0x0d:
    case 0x3d:
    case 0x1d:
    case 0x15:
      //DCR r
      loc = operation->op >> 3 & 7;
      loadRegister (loc, subReg(loc,1));
      CPUINFO.PC++;
      break;
    case 0x35:
      //DCR M
      loc = CPUINFO.H << 8 | CPUINFO.L;
      loc = memory[loc];
      setFlags(loc, loc + 1);
      memory[CPUINFO.H << 8 | CPUINFO.L]++;
      CPUINFO.PC++;
      break;
    case 0x03:
    case 0x23:
    case 0x13:
    case 0x33:
      //INX rp
      //Increment the register pairs lower by one
      loc = operation->op >> 4 & 3;
      loadRegPair (loc, regPairVal (loc) + 1);
      CPUINFO.PC++;
      break;
    case 0x1b:
    case 0x0b:
    case 0x3b:
    case 0x2b:
      //DCX rp
      loc = operation->op >> 4 & 3;
      loadRegPair (loc, regPairVal (loc) - 1);
      CPUINFO.PC++;
      break;
    case 0x09:
    case 0x39:
    case 0x29:
    case 0x19:
      //DAD rp
      //Adds the register pair to the H and L registers
      loc = regPairVal (operation->op >> 4 & 3);
      loc += regPairVal (H);
      CPUINFO.CY = (regPairVal (operation->op >> 4 & 3) >> 6 & 1) > 
	(((regPairVal (operation->op >> 4 & 3) >> 6 & 1) + regPairVal(H)) >> 6 & 1); 
      loadRegPair (H, loc);
      CPUINFO.PC++;
      break;
    case 0x27:
      //DAA
      //Forms two four bit Binary Coded Decimal digits from the
      //Accumulator (Register A)
      if ((CPUINFO.A & 0x0f > 9) || CPUINFO.AC)
	{
	  CPUINFO.A = addReg(A,6);
	}
      if ((CPUINFO.A & 0xf0 >> 4 > 9) || CPUINFO.CY)
	{
	  CPUINFO.A = addReg(A,0x60);
	}
      CPUINFO.PC++;
      break;
    case 0xa7:
    case 0xa5:
    case 0xa0:
    case 0xa1:
    case 0xa4:
    case 0xa3:
    case 0xa2:
      //ANA r
      setFlags(CPUINFO.A,CPUINFO.A & regVal(operation->op & 7));
      CPUINFO.A = CPUINFO.A & regVal (operation->op & 7);
      CPUINFO.PC++;
      break;
    case 0xa6:
      //ANA M
      setFlags(CPUINFO.A,CPUINFO.A & MEM(regPairVal(H)));
      CPUINFO.A = CPUINFO.A & MEM (regPairVal (H));
      CPUINFO.PC++;
      break;
    case 0xe6:
      //ANI data
      setFlags(CPUINFO.A,CPUINFO.A & operation->byte1);
      CPUINFO.A = CPUINFO.A & operation->byte1;
      CPUINFO.PC += 2;
      break;
    case 0xac:
    case 0xad:
    case 0xaa:
    case 0xaf:
    case 0xa8:
    case 0xab:
    case 0xa9:
      //XRA r
      setFlags(CPUINFO.A,CPUINFO.A ^ regVal(operation->op & 7));
      CPUINFO.A = CPUINFO.A ^ regVal (operation->op & 7);
      CPUINFO.PC++;
      break;
    case 0xae:
      //XRA M
      setFlags(CPUINFO.A,CPUINFO.A ^ MEM(regPairVal(H)));
      CPUINFO.A = CPUINFO.A ^ MEM (regPairVal (H));
      CPUINFO.PC++;
      break;
    case 0xee:
      //XRI data
      setFlags(CPUINFO.A,CPUINFO.A ^ operation->byte1);
      CPUINFO.A = CPUINFO.A ^ operation->byte1;
      CPUINFO.PC += 2;
      break;
    case 0xb1:
    case 0xb0:
    case 0xb3:
    case 0xb7:
    case 0xb4:
    case 0xb2:
    case 0xb5:
      //ORA r
      setFlags(CPUINFO.A,CPUINFO.A | regVal(operation->op & 7));
      CPUINFO.A = CPUINFO.A | regVal (operation->op & 7);
      CPUINFO.PC++;
      break;
    case 0xb6:
      //ORA M
      setFlags(CPUINFO.A,CPUINFO.A | MEM(regPairVal(H)));
      CPUINFO.A = CPUINFO.A | MEM (regPairVal (H));
      CPUINFO.PC++;
      break;
    case 0xf6:
      //ORI data
      setFlags(CPUINFO.A,CPUINFO.A | operation->byte1);
      CPUINFO.A = CPUINFO.A | operation->byte1;
      CPUINFO.PC += 2;
      break;
    case 0xbc:
    case 0xbb:
    case 0xb8:
    case 0xbd:
    case 0xb9:
    case 0xbf:
    case 0xba:
      //CMP r
      subReg(A,regVal(operation->op & 7));
      CPUINFO.PC++;
      break;
    case 0xbe:
      //CMP M
      subReg(A,regPairVal(H));
      CPUINFO.PC++;
      break;
    case 0xfe:
      //CPI data
      subReg(A,operation->byte1);
      CPUINFO.PC+=2;
      break;
    case 0x07:
      //RLC
      loc = CPUINFO.A >> 7;
      CPUINFO.CY = loc;
      CPUINFO.A = (CPUINFO.A << 1) | loc;
      CPUINFO.PC++;
      break;
    case 0x0f:
      //RRC
      loc = CPUINFO.A & 1;
      CPUINFO.CY = loc;
      CPUINFO.A = (CPUINFO.A >> 1) | loc << 7;
      CPUINFO.PC++;
      break;
    case 0x17:
      //RAL
      loc = CPUINFO.A >> 7;
      CPUINFO.A = CPUINFO.A << 1 | CPUINFO.CY;
      CPUINFO.CY = loc;
      CPUINFO.PC++;
      break;
    case 0x1f:
      //RAR
      loc = CPUINFO.A & 1;
      CPUINFO.A = CPUINFO.A >> 1 | CPUINFO.CY << 7;
      CPUINFO.CY = loc;
      CPUINFO.PC++;
      break;
    case 0x2f:
      //CMA
      CPUINFO.A = ~(CPUINFO.A);
      CPUINFO.PC++;
      break;
    case 0x3f:
      //CMC
      CPUINFO.CY = ~CPUINFO.CY;
      CPUINFO.PC++;
      break;
    case 0x37:
      //STC
      CPUINFO.CY = 1;
      CPUINFO.PC++;
      break;
    case 0x36:
      //MVI ADDR (H and L), r
      loc = regPairVal(H);
      memory[loc] = operation->byte1;
      CPUINFO.PC+=2;
      break;
    case 0xc3:
      //JMP
      CPUINFO.PC = operation->byte2 << 8 | operation->byte1;
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
      if(checkCondition(operation->op >> 3 & 7)){
  	  CPUINFO.PC = operation->byte2 << 8 | operation->byte1;
      }else{
	  CPUINFO.PC += 3;
      }
      break;
    case 0xcd:
      //CALL addr
      memory[CPUINFO.SP - 1] = CPUINFO.PC >> 8; //Subtracting one because we are cheating
      memory[CPUINFO.SP - 2] = CPUINFO.PC & 0xff;
      CPUINFO.PC = regPairVal(H);          //with 16 bit register.
      CPUINFO.SP = CPUINFO.SP - 2;
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
      if(checkCondition(operation->op >> 3 & 7)){
	  memory[CPUINFO.SP - 1] = CPUINFO.PC >> 8;
	  memory[CPUINFO.SP - 2] = CPUINFO.PC & 0xff;
	  CPUINFO.PC = regPairVal(H);
          CPUINFO.SP = CPUINFO.SP - 2;
      }else{
	  CPUINFO.PC++;
      }
      break;
    case 0xc9:
      //RET
      //Pulls an address off the stack and puts it in the PC
      CPUINFO.PC = memory[CPUINFO.SP] << 8 | memory[CPUINFO.SP + 1];
      CPUINFO.SP = CPUINFO.SP + 2;
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
      if(checkCondition(operation->op >> 3 & 7)){
	  CPUINFO.PC = memory[CPUINFO.SP] << 8 | memory[CPUINFO.SP + 1];
          CPUINFO.SP = CPUINFO.SP + 2;
      }else{
	  CPUINFO.PC++;
      }
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
      memory[CPUINFO.SP - 1] = CPUINFO.PC >> 8; //Subtracting one because we are cheating
      memory[CPUINFO.SP - 2] = CPUINFO.PC & 0xff;
      CPUINFO.SP = CPUINFO.SP - 2;
      CPUINFO.PC = ((operation->op >> 3) & 7) * 8;
      break;
    case 0xe9:
      //PCHL
      CPUINFO.PC = regPairVal(H);
      break;
    case 0xe5:
    case 0xd5:
    case 0xc5:
      //PUSH rp
      loc = regPairVal((operation->op >> 4) & 3);
      memory[CPUINFO.SP - 1] = loc >> 8;
      memory[CPUINFO.SP - 2] = loc & 0xff;
      CPUINFO.SP -= 2;
      break;
    case 0xf5:
      //PUSH PSW
      memory[CPUINFO.SP - 1] = CPUINFO.A;
      loc = 0;
      loc = loc | CPUINFO.CY;
      loc = loc | 1 << 1;
      loc = loc | CPUINFO.P << 2;
      loc = loc | CPUINFO.AC << 4;
      loc = loc | CPUINFO.Z << 6;
      loc = loc | CPUINFO.S << 7;
      memory[CPUINFO.SP - 2] = loc;
      CPUINFO.SP -= 2;
      CPUINFO.PC++;  
      break;
    case 0xc1:
    case 0xd1:
    case 0xe1:
      //POP rp
      loc = memory[CPUINFO.SP + 1] << 8 | memory[CPUINFO.SP];
      loadRegPair((operation->op >> 4 & 3), loc);
      CPUINFO.SP += 2;
      break;
    case 0xf1:
      //POP PSW
      CPUINFO.A = memory[CPUINFO.SP + 1];
      loc = memory[CPUINFO.SP];
      CPUINFO.CY = loc & 1;
      CPUINFO.P = loc >> 2 & 1;
      CPUINFO.AC = loc >> 4 & 1;
      CPUINFO.Z = loc >> 6 & 1;
      CPUINFO.S = loc >> 7 & 1;
      CPUINFO.SP += 2;
      break;
    case 0xe3:
      //XTHL Exchange stack top with H and L
      loc = regPairVal(H);
      CPUINFO.H = memory[CPUINFO.SP + 1];
      CPUINFO.L = memory[CPUINFO.SP];
      memory[CPUINFO.SP] = loc & 0xff;
      memory[CPUINFO.SP + 1] = loc >> 8;
      break;
    case 0xf9:
      //SPHL Stack fills H and L
      CPUINFO.PC = regPairVal(H);
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
      CPUINFO.PC++;
      MOV (operation);
      break;
    }

  free (operation);

  return 0;

}
