// PART 1

#include <stdio.h>

#define size 2

int main(int argc, char *argv[]) {
        FILE *firstFile;
        unsigned char first[size];
        int i;
        unsigned short numBytes;
        firstFile = fopen(argv[1], "rb");
        
        do {
                numBytes = fread(first, 1, size, firstFile);
                for(i=0; i<numBytes; i+=2)
                        printf("0x%02x%02x\n", first[i], first[i+1]);
        } while (numBytes == size);
        fclose(firstFile);
}
