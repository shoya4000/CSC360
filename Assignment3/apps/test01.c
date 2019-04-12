#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include <Disk.h>
#include <File.h>
#include <BitOps.h>

void printWithPause(char* str) {
	printf("%s", str);
	sleep(1);
}

void testCreateDisk() {
	printWithPause("Creating disk...\n");
	createDisk();
	printf("Empty disk created\n");
}

FILE* testAccessDisk() {
	printWithPause("Accessing vdisk..\n");
	return fopen("vdisk", "rb+");
}

void testInitLLFS(FILE* disk) {
	printWithPause("Initializing LLFS..\n");
	initLLFS(disk);
	printf("LLFS initialized\n");
}

void confirmSuperBlock(int* buffer) {
	printf("Confirming SuperBlock values\n");
	if (buffer[0] != MAGIC_NUMBER) {
		printf("Magic number is incorrect\n");
		exit(1);
	}
	if (buffer[1] != NUM_BLOCKS) {
		printf("Number of blocks is incorrect\n");
		exit(1);
	}
	if (buffer[2] != INODE_COUNT) {
		printf("Inode count is incorrect\n");
		exit(1);
	}
	printf("SuperBlock values are correct\n");
}

void confirmFreeBlockVector(int* buffer) {
	printWithPause("Confirming blocks 0-9 reserved...\n");
	int i;
	for (i = 0; i < 10; i++) {
		if (TestBit(buffer, i) != 0) {
			printf("Error in block reservation\n");
			exit(1);
		}
	}
	printf("Blocks 0-9 are reserved\n");

	printWithPause("Confirming blocks 10-4095 free...\n");
	for (i = 10; i < NUM_BLOCKS; i++) {
		if (!TestBit(buffer, i) != 0) {
			printf("Error in block reservation\n");
			exit(1);
		}
	}
	printf("Blocks 10-4095 are free\n");
}


int main(int argc, char* argv[]) {
	testCreateDisk();
	FILE* disk = testAccessDisk();
	testInitLLFS(disk);

	printWithPause("Reading SuperBlock...\n");
	int* buffer = (int*)malloc(NUM_BLOCKS);
	readBlock(disk, 0, buffer);
	confirmSuperBlock(buffer);

	printWithPause("Reading Free Block Vector...\n");
	readBlock(disk, 1, buffer);
	confirmFreeBlockVector(buffer);

	free(buffer);

	createFile(disk);
	writeToFile(disk, "Hello World!", 12);
	char* buffer1 = malloc(sizeof(char) * BLOCK_SIZE);
	readFile(disk, buffer1);
	printf("%s\n", buffer1);//assume we know it's a string

	free(buffer1);


	fclose(disk);
	return 0;
}
