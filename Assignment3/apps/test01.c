#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <Disk.h>
#include <File.h>

void removeNewLine(char* string) {
	if (string[strlen(string) - 1] == '\n') {
		string[strlen(string) - 1] = '\0';
	}
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
			else if (strncmp(parsed, "read", 512) == 0 ) {
				int block = atoi(strtok(NULL, " "));
				char* buffer = (char*)malloc(512);
				readBlock(block, buffer);
				int i;
				for (i = 0; i < BLOCK_SIZE; i++) {
					printf("%2x ", buffer[i]);
				}
				printf("\n");
				free(buffer);
				printf("wut\n");
				break;
			}
			else if (strncmp(parsed, "hello", 512) == 0 ) {
				helloWorld();
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
