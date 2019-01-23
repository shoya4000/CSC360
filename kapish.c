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
	while (exit == false) {
		char input[512];
		printf("? ");
		fgets(input, 512, stdin);
		char *parsed;
		parsed = strtok(input, " ");
		printf("debug: parsed: <%s>\n", parsed);
		while (parsed != NULL) {
			int result = strcmp(parsed, "exit");
			printf("debug: result: <%d>\n", result);
			if (strncmp(parsed, "exit", 512) == 0 ) {
				printf("ding");
				exit = true;
				break;
			}
			printf("debug: parsed: <%s>\n", parsed);
			parsed = strtok(NULL, " ");
		}
	}

	return 0;
}