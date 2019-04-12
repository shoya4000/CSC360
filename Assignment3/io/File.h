const int INODE_SIZE;

struct Super {
	int mag, blocks, inodes, head;
};

void initLLFS(FILE*);
char* createEmptyInode();