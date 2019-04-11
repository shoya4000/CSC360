int BLOCK_SIZE;
int NUM_BLOCKS;

void createDisk();
void writeBlock(FILE*, int, char*, int);
void readBlock(FILE*, int, char*);