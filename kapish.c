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
	bool exit = FALSE;
	while (exit == FALSE)
		char input[512];
	printf("? ");
	fgets(input, 512, stdin);
	char *parsed;
	parsed = strtok(input, " ");
	printf("Your input was:\n");
	while (parsed != NULL) {
		if (strcmp(parsed, "exit") == 0 ) {
			exit = TRUE;
			break;
		}
		printf("%s\n", parsed);
		parsed = strtok(NULL, " ");
	}
	return 0;
}