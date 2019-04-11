#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Disk.h>

const int BLOCK_SIZE = 512;
const int NUM_BLOCKS = 4096;

const char* VDISK = "vdisk";

FILE* accessDisk() {
	return fopen(VDISK, "rb+");
}

void createDisk() {
	FILE* disk = fopen(VDISK, "wb");
	char* init = calloc(BLOCK_SIZE * NUM_BLOCKS, 1);
	fwrite(init, BLOCK_SIZE * NUM_BLOCKS, 1, disk);
	fclose(disk);
}

void writeBlock(int blockNum, char* data, int size) {
	FILE* disk = accessDisk();
	fseek(disk, blockNum * BLOCK_SIZE, SEEK_SET);
	fwrite(data, size, 1, disk);
	fclose(disk);
}

void readBlock(int blockNum, char* buffer) {
	FILE* disk = accessDisk();
	fseek(disk, blockNum * BLOCK_SIZE, SEEK_SET);
	fread(buffer, BLOCK_SIZE, 1, disk);
	fclose(disk);
}