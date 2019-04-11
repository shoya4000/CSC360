#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <Disk.h>
#include <File.h>

#define TestBit(A,k)    ( A[(k/32)] & (1 << (k%32)) )

void removeNewLine(char* string) {
	if (string[strlen(string) - 1] == '\n') {
		string[strlen(string) - 1] = '\0';
	}
}

int main(int argc, char* argv[]) {
	printf("Initializing LLFS\n");
	createDisk();
	printf("Accessing vdisk\n");
	FILE* disk = fopen("vdisk", "rb+");
	printf("Initializing LLFS\n");
	initLLFS(disk);
	printf("Reading block 0\n");
	char* buffer = (char*)malloc(BLOCK_SIZE);
	readBlock(disk, 0, buffer);
	printf("%s\n", buffer);
	free(buffer);
	int* buffer2 = (char*)malloc(NUM_BLOCKS);
	readBlock(disk, 1, buffer2);
	printf("Confirming blocks 0-9 reserved\n");
	int i;
	for (i = 0; i < 10; i++) {
		if (TestBit(buffer2, i) != 0) {
			printf("Error in block reservation\n");
			exit(0);
		}
		printf("printing bit %d: %d\n", i, TestBit(buffer2, i) != 0);
	}
	free(buffer);
	fclose(disk);
	return 0;
}
