#include <stdio.h>
#include <stdlib.h>

#include <Disk.h>

const int BLOCK_SIZE = 512;
const int NUM_BLOCKS = 4096;

void createDisk() {
	FILE* disk = fopen("vdisk", "wb");
	char* init = calloc(BLOCK_SIZE * NUM_BLOCKS, 1);
	fwrite(init, BLOCK_SIZE * NUM_BLOCKS, 1, disk);
	fclose(disk);
}

void writeBlock(FILE* disk, int blockNum, void* data, int size) {
	fseek(disk, blockNum * BLOCK_SIZE, SEEK_SET);
	fwrite(data, size, 1, disk);
}

void readBlock(FILE* disk, int blockNum, char* buffer) {
	fseek(disk, blockNum * BLOCK_SIZE, SEEK_SET);
	fread(buffer, BLOCK_SIZE, 1, disk);
}