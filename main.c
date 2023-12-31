#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

size_t get_file_size(const char* path) {
	struct stat st;
	if (stat(path, &st) == -1) {
		return 0;
	}
	return st.st_size;
}

int main(void) {
	char name[1024];
	printf("Enter file name to lex: ");
	scanf("%s", name);
	FILE* f = fopen(name, "r");
	if (!f) {
		printf("ERROR: failed to open file: %s!\n", name);
		exit(-1);
	}
	size_t n = get_file_size(name);
	char *buf = malloc(sizeof(char) * (n + 1));
	if (!buf) {
		printf("ERROR: failed to allocate buffer!\n");
		exit(-1);
	}
	read(fileno(f), buf, n);
	buf[n] = 0;

	Lexer* l = init_lexer(buf, n + 1);
	if (!l) {
		exit(-1);
	}

	while (peek(l) != 0) {
		if (iswhitespace(l -> current)) {
			consume_white_space(l);
		}
		// This statement tells me to add the char to the token
		printf("%c", l -> current);

		// These indicate when i should return the token
		if (peek(l) == ' ') {
			printf("\n");
		}
		if (peek(l) == ',') {
			printf("\n");
		}
		consume(l);
	}
	printf("\n");

	fclose(f);
	free(l);
	return 0;
}
