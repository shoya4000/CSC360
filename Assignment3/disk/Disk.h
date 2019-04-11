const int BLOCK_SIZE;
const int NUM_BLOCKS;

void createDisk();
void writeBlock(FILE*, int, char*, int);
void readBlock(FILE*, int, char*);