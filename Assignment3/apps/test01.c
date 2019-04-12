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

int main(int argc, char* argv[]) {
	printWithPause("Initializing LLFS...\n");
	sleep(1);
	printWithPause("Creating disk...\n");
	createDisk();
	printf("Empty disk created\n");

	printWithPause("Accessing vdisk..\n");
	FILE* disk = fopen("vdisk", "rb+");

	printWithPause("Initializing LLFS..\n");
	initLLFS(disk);
	printf("LLFS initialized\n");

	printWithPause("Reading SuperBlock...\n");
	printf("Confirming SuperBlock values\n");
	int* buffer1 = (int*)malloc(NUM_BLOCKS);
	readBlock(disk, 0, buffer1);
	int i;
	for (i = 0; i < 12; 1++) {
		printf("%x\n", buffer1[i]);
	}
	//printf("%d\n", buffer1);
	free(buffer1);

	printWithPause("Reading Free Block Vector...\n");
	int* buffer2 = (int*)malloc(NUM_BLOCKS);
	readBlock(disk, 1, buffer2);

	printWithPause("Confirming blocks 0-9 reserved...\n");
	int i;
	for (i = 0; i < 10; i++) {
		if (TestBit(buffer2, i) != 0) {
			printf("Error in block reservation\n");
			exit(0);
		}
	}
	printf("Blocks 0-9 are reserved\n");

	printWithPause("Confirming blocks 10-4095 free...\n");
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
