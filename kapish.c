/*
Sho Ya Voorthuyzen
V00730770
CSC 360
Assignment #1, Part #1: Doubly linked list - Takes in a number and generates a doubly linked list of each number up to the number given. Can print current list, can insert or delete.
January 16th 2019
*/
#include <stdio.h> //standard input and output library
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <limits.h>

void removeNewLine(char* string) {
	if (string[strlen(string) - 1] == '\n') {
		string[strlen(string) - 1] = '\0';
	}
}

int main(int argc, char *argv[]) {
	while (true) {
		printf("? ");
		char input[512];
		if (fgets(input, 512, stdin) == NULL) {
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		removeNewLine(input);
		char *parsed;
		parsed = strtok(input, " ");
		while (parsed != NULL) {
			if (strncmp(parsed, "setenv", 512) == 0 ) {
				char *var = strtok(NULL, " ");
				char *value = strtok(NULL, " ");
				setenv(var, value, 1);
				break;
			}
			else if (strncmp(parsed, "unsetenv", 512) == 0 ) {
				char *var = strtok(NULL, " ");
				unsetenv(var);
				break;
			}
			else if (strncmp(parsed, "cd", 512) == 0 ) {
				char *dir = strtok(NULL, " ");
				printf("debug: %s", dir);
				if (dir != NULL) {
					chdir(dir);
				}
				else {
					chdir("~");
				}
				char cwd[PATH_MAX];
				getcwd(cwd, sizeof(cwd))
				printf("cwd: %s", cwd);
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