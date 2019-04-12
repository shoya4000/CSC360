const int MAGIC_NUMBER;
const int INODE_SIZE;
const int INODE_COUNT;

struct Super {
	int mag, blocks, inodes, head;
};

void initLLFS(FILE*);
char* createEmptyInode();