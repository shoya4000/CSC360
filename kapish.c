#include <stdio.h> //standard input and output library
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

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
				if (dir != NULL) {
					chdir(dir);
				}
				else {
					chdir(getenv("HOME"));
				}
				break;
			}
			else if (strncmp(parsed, "exit", 512) == 0 ) {
				exit(EXIT_SUCCESS);
			}
			else {
				argv[0] = parsed;
				int i = 1;
				while (parsed != NULL) {
					argv[i] = strtok(NULL, " ");
					parsed = argv[i];
					i++;
				}
				pid_t childID = fork();
				if (childID == 0) {
					execvp(argv[0], argv);
					perror("Error: ");
				} else {
					wait(NULL);
				}

			}
			parsed = strtok(NULL, " ");
		}
	}

	return 0;
}