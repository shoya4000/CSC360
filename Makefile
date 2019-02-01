all: kapish.c
	gcc -g -o -Wall -Werrorkapish kapish.c

clean: 
	  $(RM) kapish