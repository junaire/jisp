#include <stdio.h>

static char input[2048];

int main(int argc, char** argv)
{
	puts("Jun's Lisp Version 0.0.1\n");
	puts("Press Ctrl-C to exit...\n");

	while(1) {
		fputs("jisp>",stdout);
		fgets(input, 2048, stdin);
		printf("No you're a %s",input);
	}

	return 0;
}
