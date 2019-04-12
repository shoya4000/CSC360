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

struct Inode {
	uint32_t size, flags;
	uint16_t direct[10], indirectBlock, doubleIndirectBlock;
};

struct DentryNode {
	uint16_t inode;
	char fileName[30];
};

struct Dentry {
	struct DentryNode dentryNodeList[16];
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
	for (i = 132; i < NUM_BLOCKS; i++) {
		SetBit(freeBlocks, i);
	}
	writeBlock(disk, 1, freeBlocks, NUM_BLOCKS);
	free(freeBlocks);

	int* freeInodes = calloc(NUM_BLOCKS / 2, 1);
	for (i = 0; i < NUM_BLOCKS / 2; i++) {
		SetBit(freeInodes, i);
	}
	writeBlock(disk, 2, freeInodes, NUM_BLOCKS / 2);
	free(freeInodes);
}

int findFirstFreeInode(FILE* disk) {
	int* freeInodes = calloc(NUM_BLOCKS / 2, 1);
	readBlock(disk, 2, freeInodes);
	int i;
	for (i = 0; i < NUM_BLOCKS / 2; i++) {
		if (TestBit(freeInodes, i) != 0) {
			ClearBit(freeInodes, i);
			writeBlock(disk, 2, freeInodes, i);
			free(freeInodes);
			return i;
		}
	}
	printf("No free Inodes remaining\n");
	exit(1);
}


void createFile(FILE* disk) {
	struct Inode inode = {
		.direct[0] = 132 //132 and other values will need to be free blocks that are found
	};
	int offset = findFirstFreeInode(disk);

	char* inodesBuffer = (char*)malloc(BLOCK_SIZE);
	readBlock(disk, 3, inodesBuffer);
	int i;
	for (i = 0; i < 50; i++) {
		printf("%2x ", inodesBuffer[i]);
	}
	printf("done\n");
	memcpy(inodesBuffer + (offset * INODE_SIZE), &inode, INODE_SIZE);

	writeBlock(disk, 3, inodesBuffer, INODE_SIZE * (offset + 1));
	free(inodesBuffer);
}

void writeToFile(FILE* disk, void* data, int size) {
	char* inodeBuffer = (char*)malloc(BLOCK_SIZE);
	check_mem_fail(inodeBuffer);
	//3 below is just reading first inode, need to make dynamic
	readBlock(disk, 3, inodeBuffer);
	uint16_t fileBlockNumber;
	memcpy(&fileBlockNumber, inodeBuffer + 8, 2);
	writeBlock(disk, fileBlockNumber, data, size);

	free(inodeBuffer);
}

void readFile(FILE* disk, void* buffer) {
	char* inodeBuffer = (char*)malloc(BLOCK_SIZE);
	check_mem_fail(inodeBuffer);
	//3 below is just reading first inode, need to make dynamic
	readBlock(disk, 3, inodeBuffer);
	uint16_t fileBlockNumber;
	memcpy(&fileBlockNumber, inodeBuffer + 8, 2);
	readBlock(disk, fileBlockNumber, buffer);

	free(inodeBuffer);
}

//3-131 inodes
//132-4095 data blocks