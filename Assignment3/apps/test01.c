#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <Disk.h>
#include <File.h>
#include <BitOps.h>

int main(int argc, char* argv[]) {
	printf("Initializing LLFS...\n");

	printf("Creating disk...\n");
	createDisk();
	printf("Empty disk created\n");

	printf("Accessing vdisk..\n");
	FILE* disk = fopen("vdisk", "rb+");

	printf("Initializing LLFS..\n");
	initLLFS(disk);
	printf("LLFS initialized\n");

	printf("Reading SuperBlock...\n");
	char* buffer1 = (char*)malloc(BLOCK_SIZE);
	readBlock(disk, 0, buffer1);
	printf("%s\n", buffer1);
	free(buffer1);

	printf("Reading Free Block Vector...\n");
	int* buffer2 = (int*)malloc(NUM_BLOCKS);
	readBlock(disk, 1, buffer2);

	printf("Confirming blocks 0-9 reserved...\n");
	int i;
	for (i = 0; i < 10; i++) {
		if (TestBit(buffer2, i) != 0) {
			printf("Error in block reservation\n");
			exit(0);
		}
	}

	printf("Blocks 0-9 are reserved\n");
	printf("Confirming blocks 10-4095 free...\n");
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
