//macros below from https://stackoverflow.com/a/30590727
#define SetBit(A,k)     ( A[(k/32)] |= (1 << (k%32)) )
#define ClearBit(A,k)   ( A[(k/32)] &= ~(1 << (k%32)) )
#define TestBit(A,k)    ( A[(k/32)] & (1 << (k%32)) )

const int INODE_SIZE;

void initLLFS(FILE*);
char* createEmptyInode();