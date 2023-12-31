#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "./lexer.h"

Lexer* init_lexer(const char* buffer, uint64_t file_size) {
	Lexer* l = (Lexer*) malloc(sizeof(Lexer));
	if (!l) {
		printf("ERROR: Not enough memory for lexer!\n");
		return NULL;
	}
	l -> buf = buffer;
	l -> file_size = file_size;
	l -> cursor = 0;
	l -> current = l -> buf[l -> cursor];
	return l;
}


char peek(const Lexer* lex) {
	assert(lex -> cursor < lex -> file_size);
	return lex -> buf[lex -> cursor + 1];
}

void consume(Lexer* lex) {
	lex -> cursor += 1;
	assert(lex -> cursor < lex -> file_size);

	lex -> current = lex -> buf[lex -> cursor];
	return;
}

int iswhitespace(char c) {
	if (c == '\n' || c == '\r' || c == '\t' || c == ' ') return 1;
	else return 0;
}

void consume_white_space(Lexer* lex) {
	while (1) {
		if (iswhitespace(lex -> current)) {
			consume(lex);
		} else {
			return;
		}
	}
}
