#include <stdio.h>
#include <stdlib.h>

int main(int c, char *argv[]) {
	if( c != 4 ) {
		printf("usage: bin2prg <binary input file> <output file name> <load address>\n");
		exit(1);
	}
	
	FILE *fp;
	FILE *fp2;
	int address;
	int program_size;
	unsigned char *buf;
	char lowByte;
	char hiByte;
	
	
	// Get file size and read into buffer
	fp = fopen(argv[1],"rb");
	if( !fp ) {
		printf("Can't open file: %s for reading.\n", argv[1]);
		exit(1);
	}
	
	fseek(fp, 0L, SEEK_END);
	program_size = ftell(fp);
	
	buf = (unsigned char*)malloc(program_size + 2);

	// Get load address
	address = atoi(argv[3]);
	
	if( address < 0 || address > 65535 ) {
		printf("Incorrect load address. Addresses must be in the range 0 to 65535.\n");
		exit(1);
	}
	
	
	lowByte = address & 0x00FF;
	hiByte = (address >> 8) & 0x00FF;
	printf("Load address: %d ($%X) Low byte: %d, High byte: %d\n", address, address, lowByte, hiByte);
	
	rewind(fp);
	
	// Set load address. 6502 addresses are stored low byte/high byte order
	buf[0] = lowByte;
	buf[1] = hiByte;
	
	// Read file into buffer and write output
	fp2 = fopen(argv[2],"wb");
	fread(&buf[2], program_size, 1, fp);
	
	fwrite(buf, sizeof(unsigned char), program_size + 2, fp2);
	fclose(fp);
	fclose(fp2);
	
}