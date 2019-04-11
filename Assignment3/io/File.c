#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <File.h>
#include <Disk.h>

const int INODE_SIZE = 32;
const int MAGIC_NUMBER = 0x616d6f6b;

struct Superblock {
	uint32_t magic;
};

void initLLFS(FILE* disk) {
	struct Superblock super = {
		.magic = MAGIC_NUMBER
	};
	writeBlock(disk, 0, &super, sizeof(super));
}

char* createEmptyInode() {
	char* inode = (char*)malloc(INODE_SIZE);
	short dataBlock1 = 3;
	memcpy(inode + 8, &dataBlock1, 2); //First direct block value pointing to block number 3
	return inode;
}