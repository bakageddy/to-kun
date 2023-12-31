#ifndef __LEXER_H
#define __LEXER_H

#include <stddef.h>

typedef struct {
	const char* buf;
	size_t file_size;
	size_t cursor;
	char current;
} Lexer;

Lexer* init_lexer(const char* buffer, size_t file_size);
char peek(const Lexer* lex);
void consume(Lexer* lex);
int iswhitespace(char c);
void consume_white_space(Lexer* lex);

#endif //__LEXER_H
