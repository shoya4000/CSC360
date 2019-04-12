#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <File.h>
#include <Disk.h>
#include <BitOps.h>

const int MAGIC_NUMBER = 0x6b6f6d61;
const int INODE_SIZE = 32;
const int INODE_COUNT = 2048;

struct Super {
	uint32_t mag, blocks, inodes, head;
};

void check_mem_fail(const void *a) {
//check memory allocation succeeded
	if (!a) {
		fprintf(stderr, ("Memory allocation failed\n"));
		exit(1);
	}
}

void initLLFS(FILE* disk) {
	struct Super superInit = {
		MAGIC_NUMBER, NUM_BLOCKS, INODE_COUNT, 0
	};
	writeBlock(disk, 0, &superInit, sizeof(superInit));
	int* freeBlocks = calloc(NUM_BLOCKS, 1);
	check_mem_fail(freeBlocks);
	int i;
	for (i = 10; i < NUM_BLOCKS; i++) {
		SetBit(freeBlocks, i);
	}
	writeBlock(disk, 1, freeBlocks, NUM_BLOCKS);
}

char* createEmptyInode() {
	char* inode = malloc(INODE_SIZE);
	check_mem_fail(inode);
	short dataBlock1 = 3;
	memcpy(inode + 8, &dataBlock1, 2);
	return inode;
}

void createFile(FILE* disk) {
	char* inode = createEmptyInode();
	// Add more things to inode?
	writeBlock(disk, 2, inode, 32);

	free(inode);
}

void writeToFile(FILE* disk, char* data, int size) {
	char* inodeBuffer = (char*)malloc(BLOCK_SIZE);
	check_mem_fail(inodeBuffer);
	readBlock(disk, 2, inodeBuffer);
	short fileBlockNumber;
	memcpy(&fileBlockNumber, inodeBuffer + 8, 2);
	writeBlock(disk, fileBlockNumber, data, size);

	free(inodeBuffer);
}

void readFile(FILE* disk, char* buffer) {
	char* inodeBuffer = (char*)malloc(BLOCK_SIZE);
	check_mem_fail(inodeBuffer);
	readBlock(disk, 2, inodeBuffer);
	short fileBlockNumber;
	memcpy(&fileBlockNumber, inodeBuffer + 8, 2);
	readBlock(disk, fileBlockNumber, buffer);

	free(inodeBuffer);
}