/*
Sho Ya Voorthuyzen
V00730770
CSC 360
Assignment #1, Part #1: Doubly linked list - Takes in a number and generates a doubly linked list of each number up to the number given. Can print current list, can insert or delete.
January 16th 2019
*/
#include <stdio.h> //standard input and output library
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
	bool exit = false;
	printf("? ");
	while (exit == false) {
		char input[512];
		fgets(input, 512, stdin);
		char *parsed;
		parsed = strtok(input, " ");
		while (parsed != NULL) {
			strtok(parsed, "\n");
			int result = strncmp(parsed, "exit", 512);
			if (strncmp(parsed, "setenv", 512) == 0 ) {
				var = strtok(NULL, " ");
				value = strtok(NULL, " ");
				setenv(var, value, 1);
				printf("setenv");
			}
			else if (strncmp(parsed, "unsetenv", 512) == 0 ) {
				var = strtok(NULL, " ");
				unsetenv(var);
				break;
			}
			else if (strncmp(parsed, "cd", 512) == 0 ) {
				printf("cd");
			}
			else if (strncmp(parsed, "exit", 512) == 0 ) {
				exit = true;
				break;
			}

			parsed = strtok(NULL, " ");

		}
		if (exit != true) {
			printf("\n? ");
		}
	}

	return 0;
}