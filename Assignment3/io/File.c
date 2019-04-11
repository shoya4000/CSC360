#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <File.h>
#include <Disk.h>

const int MAGIC_NUMBER = 0x6b6f6d61;
const int INODE_SIZE = 32;
const int INODE_COUNT = 2048;

struct Super {
	int mag, blocks, inodes, head;
};
struct FreeBlockVector {
	unsigned int superBlock : 1, freeBlocks : 1, reservedBlocks : 8, rest : 8;
};

void initLLFS(FILE* disk) {
	struct Super superInit = {
		MAGIC_NUMBER, NUM_BLOCKS, INODE_COUNT, 0
	};
	writeBlock(disk, 0, &superInit, sizeof(superInit));
	struct FreeBlockVector freeBlocks = {
		0, 0, 0, 0xf
	};
	writeBlock(disk, 1, &freeBlocks, sizeof(freeBlocks));
}

char* createEmptyInode() {
	char* inode = (char*)malloc(INODE_SIZE);
	short dataBlock1 = 3;
	memcpy(inode + 8, &dataBlock1, 2); //First direct block value pointing to block number 3
	return inode;
}