#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>


int main(int argc, char** argv)
{
	puts("Jun's Lisp Version 0.0.1\n");
	puts("Press Ctrl-C to exit...\n");

	while(1) {
		char* input = readline("jisp> ");
		add_history(input);

		printf("No you're a %s\n",input);
		free(input);
	}

	return 0;
}
