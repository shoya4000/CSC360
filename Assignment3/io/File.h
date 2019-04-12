const int MAGIC_NUMBER;
const int INODE_SIZE;
const int INODE_COUNT;

void initLLFS(FILE*);
char* createEmptyInode();
void createFile(FILE*);
void writeToFile(FILE*, void*, int);
void readFile(FILE*, void*, int);