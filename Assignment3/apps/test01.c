#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <Disk.h>
#include <File.h>

const int BLOCK_SIZE = 512;

void removeNewLine(char* string) {
	if (string[strlen(string) - 1] == '\n') {
		string[strlen(string) - 1] = '\0';
	}
}

int main(int argc, char* argv[]) {
	printf("Initializing LLFS\n");
	createDisk();
	printf("Accessing vdisk\n");
	FILE* disk = fopen("vdisk", "rb+");
	printf("Reading block 0\n");
	char* buffer = (char*)malloc(BLOCK_SIZE);
	readBlock(disk, 0, buffer);
	int i;
	for (i = 0; i < BLOCK_SIZE; i++) {
		printf("%2x ", buffer[i]);
	}
	printf("\n");
	free(buffer);
	fclose(disk);
	printf("Calling helloworld from File.c");
	helloWorld();
	return 0;
}
