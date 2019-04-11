#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <File.h>
#include <Disk.h>

const int INODE_SIZE = 32;
const int MAGIC_NUMBER = 0x616d6f6b;

void initLLFS(FILE* disk) {
	char* superBlockInit = itoa(MAGIC_NUMBER) + itoa(NUM_BLOCKS);
	writeBlock(disk, 0, superBlockInit, strlen("amok") * 2);
}

char* createEmptyInode() {
	char* inode = (char*)malloc(INODE_SIZE);
	short dataBlock1 = 3;
	memcpy(inode + 8, &dataBlock1, 2); //First direct block value pointing to block number 3
	return inode;
}