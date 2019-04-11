#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <File.h>
#include <Disk.h>

//macros below from https://stackoverflow.com/questions/2525310/how-to-define-and-work-with-an-array-of-bits-in-c
#define SetBit(A,k)     ( A[(k/32)] |= (1 << (k%32)) )
#define ClearBit(A,k)   ( A[(k/32)] &= ~(1 << (k%32)) )
#define TestBit(A,k)    ( A[(k/32)] & (1 << (k%32)) )

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
	char* freeBlocks = calloc(BLOCK_SIZE, 1);
	for (int i = 10; i < BLOCK_SIZE; i++) {
		SetBit(freeBlocks, i);
	}
	//memset(freeBlocks + 1 , 0x3f, 1);
	//memset(freeBlocks + 2, 0xff, BLOCK_SIZE - 2);
	writeBlock(disk, 1, freeBlocks, BLOCK_SIZE);
}

char* createEmptyInode() {
	char* inode = (char*)malloc(INODE_SIZE);
	short dataBlock1 = 3;
	memcpy(inode + 8, &dataBlock1, 2); //First direct block value pointing to block number 3
	return inode;
}