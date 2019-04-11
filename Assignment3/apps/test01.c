#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <Disk.h>
#include <File.h>

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
	char* buffer1 = (char*)malloc(BLOCK_SIZE);
	readBlock(disk, 0, buffer1);
	printf("%s\n", buffer1);
	free(buffer1);
	int* buffer2 = (int*)malloc(NUM_BLOCKS);
	readBlock(disk, 1, buffer2);
	printf("Confirming blocks 0-9 reserved\n");
	int i;
	for (i = 0; i < 10; i++) {
		if (TestBit(buffer2, i) != 0) {
			printf("Error in block reservation\n");
			exit(0);
		}
	}
	printf("Blocks 0-9 are reserved\n");
	printf("Confirming blocks 10-4095 free\n");
	for (i = 10; i < NUM_BLOCKS; i++) {
		if (!TestBit(buffer2, i) != 0) {
			printf("Error in block reservation\n");
			exit(0);
		}
	}
	printf("Blocks 10-4095 are free\n");
	free(buffer2);
	fclose(disk);
	return 0;
}
