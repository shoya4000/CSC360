#include <stdio.h> //standard input and output library
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>

void check_mem_fail(const void *a) {
//check memory allocation succeeded
	if (!a) {
		fprintf(stderr, ("Memory allocation failed\n"));
		exit(1);
	}
}

typedef struct node {
	char* the_command;
	struct node *prev;
	struct node *next;
} node;

int historyLength = 0;
struct node *START = NULL;
struct node *END = NULL;

void addHistory(char* command) {
	struct node *newNode = malloc(sizeof * newNode);
	check_mem_fail(newNode);
	newNode->the_command = malloc(sizeof * command);
	check_mem_fail(newNode->the_command);
	strcpy(newNode->the_command, command);
	newNode->prev = NULL;
	newNode->next = START;
	START = newNode;
	if (historyLength == 0) {
		END = newNode;
	}
	historyLength++;
}

void printHistory() {
	struct node *item = START;
	int i;
	for (i = 0; i < historyLength; i++) {
		printf("%s\n", item->the_command);
		item = item->next;
	}
}

void freeHistory() {
	struct node *item = START;
	int i;
	for (i = 0; i < historyLength; i++) {
		item = item->next;
		free(item->prev->the_command);
		free(item->prev);
	}
	free(item);
	historyLength--;
}

char* reexecute(char* prefix) {
	int i;
	for (i = 0; i < strlen(prefix) - 1; i++) {
		prefix[i] = prefix[i + 1];
	}
	struct node *item = START;
	for (i = 0; i < historyLength; i++) {
		if (strncmp(prefix, item->the_command, strlen(prefix)) == 0) {
			return item->the_command;
		}
		item = item->next;
	}
	return "NoPrefix";
}

void removeNewLine(char* string) {
	if (string[strlen(string) - 1] == '\n') {
		string[strlen(string) - 1] = '\0';
	}
}

int main(int argc, char *argv[]) {
	while (true) {
		signal(SIGINT, SIG_DFL);
		printf("? ");
		char input[512];
		if (fgets(input, 512, stdin) == NULL) {
			printf("\n");
			freeHistory();
			exit(EXIT_SUCCESS);
		}
		removeNewLine(input);
		if (input[0] != '!') {
			addHistory(input);
		} else {
			strcpy(input, reexecute(input));
		}
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
				if (dir != NULL) {
					chdir(dir);
				}
				else {
					chdir(getenv("HOME"));
				}
				break;
			}
			else if (strncmp(parsed, "exit", 512) == 0 ) {
				freeHistory();
				exit(EXIT_SUCCESS);
			}
			else if (strncmp(parsed, "history", 512) == 0 ) {
				printHistory();
			}
			else if (strncmp(parsed, "NoPrefix", 512) == 0 ) {
				printf("No matching prefix");
			}
			else {
				argv[0] = parsed;
				int i = 1;
				while (parsed != NULL) {
					argv[i] = strtok(NULL, " ");
					parsed = argv[i];
					i++;
				}
				signal(SIGINT, SIG_IGN);
				pid_t childID = fork();
				if (childID == 0) {
					signal(SIGINT, SIG_DFL);
					execvp(argv[0], argv);
					perror("Error");
				} else {
					wait(NULL);
				}
			}
			parsed = strtok(NULL, " ");
		}
	}
	freeHistory();
	return 0;
}