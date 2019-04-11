#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const int BLOCK_SIZE = 512;
const int NUM_BLOCKS = 4096;

void removeNewLine(char* string) {
	if (string[strlen(string) - 1] == '\n') {
		string[strlen(string) - 1] = '\0';
	}
}

void createDisk() {
	FILE* disk = fopen("vdisk", "wb"); // Open the file to be written to in binary mode
	char* init = calloc(BLOCK_SIZE * NUM_BLOCKS, 1);
	fwrite(init, BLOCK_SIZE * NUM_BLOCKS, 1, disk);

	fclose(disk);
}