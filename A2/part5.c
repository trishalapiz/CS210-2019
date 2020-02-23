// PART 5

#include <stdio.h>

#define size 2 // 6 words, so 12 bytes
#define regElements 8
#define instructions 100
int main(int argc, char *argv[]){
        FILE *file;
        unsigned char readByte[size]; 
        // storing the data being read from p2.obj
        unsigned short registers[regElements] = {0x0000}; // all elements set to 0x0000?
        // holds values of 8 general purpose registers
        unsigned short PC, IR, index, numBytes, x, offset, address, temp, subAddress, regIndex, mode, srOne, srTwo;
        // where 'x' holds the value of the starting address
        char CC;
        // assign condition code here
        unsigned short memory[instructions]; // STORE MACHINE CODE IN HERE use to simulate the memory  
        
    	int j, k, l, m, n, o;
    	
        // opening the file to be read into
        file = fopen(argv[1], "rb");
        
        // all initially set to ZERO
       	CC = 'Z';
        IR = 0x0000;
        regIndex = 0x0E00;
        
        // PC set to starting address
        fread(&x, 1, size, file); // reads first 2 bytes of the file
		PC = x << 8;
        
        //read through file and store instructions in array
        k = 0;
       	do {
       		numBytes = fread(readByte, 1, size, file); // points to 3rd byte
       		memory[k] = readByte[0] << 8 | readByte[1];
       		k += 1;
       	} while (numBytes == size);
        fclose(file);
        
        // iterating through instructions
        m = 0;
        while ((memory[m] & 0xF000) != 0xF000) { // while opcode is not halt
        	if ((memory[m] & 0xF000) == 0x5000) { // if opcode is AND
        		IR = memory[m]; // 5601 or 5660
        		PC = PC + 0x0001;
        		mode = IR & 0x0020;
        		if (mode == 0x0000) { // register mode, IR = 5601
        			regIndex = (memory[m] & 0x0E00) >> 9; // store AND here
        			srOne = (memory[m] & 0x01C0) >> 6; // SR1 = 0
        			srTwo = (memory[m] & 0x0007); // SR2 = 1
        			registers[regIndex] = registers[srOne] & registers[srTwo];
        			if (registers[regIndex] > 0) {
        				CC = 'P';
        			} else if (registers[regIndex] < 0){
        				CC = 'N';
        			}
        			printf("after executing instruction\t0x%x\n", IR);
        			for (n=0; n<regElements; n++) { 
        				printf("R%d\t0x%04x\n", n, registers[n]);
        			}
        			printf("PC\t0x%x\n", PC);
        			printf("IR\t0x%x\n", IR);
        			printf("CC\t%c\n", CC);
         			for (j=0; j<18; j++) // print the lines
						if (j == 17) {
							printf("=\n");
						} else {
							printf("=");
						}
        		} else if (mode == 0x0020) { // immediate mode, IR = 5660
        			srOne = (memory[m] & 0x01C0) >> 6; // SR = 1
        			srTwo = (memory[m] & 0x001F); // returns #0
        			regIndex = (memory[m] & 0x0E00) >> 9; // store AND here
        			registers[regIndex] = registers[srOne] & srTwo;
        			if (registers[regIndex] > 0) {
        				CC = 'P';
        			} else if (registers[regIndex] < 0){
        				CC = 'N';
        			}
        		}
        	} else if ((memory[m] & 0xF000) == 0xA000) { // if opcode LDI
        		IR = memory[m]; // a403
        		PC = PC + 0x0001; // increment PC, PC = 4503
        		offset = IR & 0x01FF; // offset of 3, address should be 4506 // OUTER ADDRESS
        		address = PC + offset; // 4506
        		subAddress = address & 0x00FF; // 6, index to access memory 2nd time
        		temp = memory[subAddress]; // 4501
        		index = temp & 0x00FF; // returns 1
        		regIndex = (memory[m] & 0x0E00) >> 9; // R2
        		registers[regIndex] = memory[index]; // R2 = 0xe203
        		if (registers[regIndex] > 0) {
        			CC = 'P';
        		} else if (registers[regIndex] < 0){
        			CC = 'N';
        		} else {
        			CC = 'Z';
        		}
        	} else if ((memory[m] & 0xF000) == 0x2000) { // if opcode is LD
        		IR = memory[m]; // 2005
        		PC = PC + 0x0001; // increment PC so PC = 4501
        		offset = IR & 0x01FF; 
        		address = PC + offset; // address is 4502
        		index = address & 0x00FF; // number used to get what is saved in memory, 2
        		regIndex = memory[m] & 0x0E00; // regIndex = 0 , number used to save into register
        		registers[regIndex] = memory[index];
        		if (registers[regIndex] > 0) {
        			CC = 'P';
        		} else if (registers[regIndex] < 0){
        			CC = 'N';
        		}
        	} else if ((memory[m] & 0xF000) == 0xE000) { // if opcode is LEA
        		IR = memory[m]; // e205
        		PC = PC + 0x0001; // increment PC so PC = 4502
        		offset = IR & 0x01FF; // returns 0
        		address = PC + offset; // address = 4502
        		index = address & 0x00FF; // returns 2, 0x00FF used to calculate actual address
        		regIndex = (memory[m] & 0x0E00) >> 9; // needs to return 1
        		registers[regIndex] = address | index; // R1 = 4504
        		if (registers[regIndex] > 0) {
        			CC = 'P';
        		} else if (registers[regIndex] < 0){
        			CC = 'N';
        		}
        	}
        	m += 1;
        } // end of while loop
        
        printf("after executing instruction\t0x%x\n", IR);
        	for (n=0; n<regElements; n++) { 
        		printf("R%d\t0x%04x\n", n, registers[n]);
        	}
        	printf("PC\t0x%x\n", PC);
        	printf("IR\t0x%x\n", IR);
        	printf("CC\t%c\n", CC);
         	for (j=0; j<18; j++) // print the lines
				if (j == 17) {
					printf("=\n");
				} else {
					printf("=");
				}
}
