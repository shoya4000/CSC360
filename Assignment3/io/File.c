#include <stdio.h>
#include <stdlib.h>

#include <File.h>
#include <Disk.h>

const int INODE_SIZE = 32;

void initLLFS(File* disk) {
	writeBlock(disk, 0, "amok", len("amok"));
}

char* createEmptyInode() {
	char* inode = (char*)malloc(INODE_SIZE);
	short dataBlock1 = 3;
	memcpy(inode + 8, &dataBlock1, 2); //First direct block value pointing to block number 3
	return inode;
}