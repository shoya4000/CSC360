const int BLOCK_SIZE;
const int NUM_BLOCKS;

void createDisk();
void writeBlock(FILE*, int, void*, int);
void readBlock(FILE*, int, void*);