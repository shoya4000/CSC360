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
	int mag, blocks, inodes, head;
};

void initLLFS(FILE* disk) {
	struct Super superInit = {
		MAGIC_NUMBER, NUM_BLOCKS, INODE_COUNT, 0
	};
	writeBlock(disk, 0, &superInit, sizeof(superInit));
	int* freeBlocks = calloc(NUM_BLOCKS, 1);
	if (!freeBlocks) {
		printf("Memory allocation for Free Block Vector failed\n");
		exit(0);
	}
	int i;
	for (i = NUM_BLOCKS - 1; i >= 10; i--) {
		SetBit(freeBlocks, i);
	}
	writeBlock(disk, 1, freeBlocks, NUM_BLOCKS);
}

char* createEmptyInode() {
	char* inode = (char*)malloc(INODE_SIZE);
	short dataBlock1 = 3;
	memcpy(inode + 8, &dataBlock1, 2); //First direct block value pointing to block number 3
	return inode;
}