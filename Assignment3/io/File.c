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
	FILE* disk = fopen("../disk/vdisk", "wb"); // Open the file to be written to in binary mode
	char* init = calloc(BLOCK_SIZE * NUM_BLOCKS, 1);
	fwrite(init, BLOCK_SIZE * NUM_BLOCKS, 1, disk);

	fclose(disk);
}

int main(int argc, char* argv[]) {
	while (true) {
		printf("0_o ");
		char input[512];
		if (fgets(input, 512, stdin) == NULL) {
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		removeNewLine(input);
		char *parsed;
		parsed = strtok(input, " ");
		while (parsed != NULL) {
			if (strncmp(parsed, "InitLLFS", 512) == 0 ) {
				createDisk();
				break;
			}
			else if (strncmp(parsed, "exit", 512) == 0 ) {
				exit(EXIT_SUCCESS);
			}
			parsed = strtok(NULL, " ");
		}
	}
	return 0;
}