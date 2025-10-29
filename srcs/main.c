#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"
#include "keywords.h"

#define BUFFER_LEN 128
#define SIZE_MAX ~(size_t)0

size_t matchKeyword(const char *const word) {
	for(size_t i = 0; i < sizeof(KEYWORDS) / sizeof(KEYWORDS[0]); i++) {
		if(strcmp(word, KEYWORDS[i]) == 0) {
			return i;
		}
	}
	return SIZE_MAX;
}

Token matchMonograph(const char c) {
	switch (c) {
		case '(': return ROUND_BRACKET_OPEN;
		case ')': return ROUND_BRACKET_CLOSE;
		case '{': return CURLY_BRACKET_OPEN;
		case '}': return CURLY_BRACKET_CLOSE;
		case '[': return SQUARE_BRACKET_OPEN;
		case ']': return SQUARE_BRACKET_CLOSE;
		case '.': return DOT;
		case ':': return COLON;
		case ',': return COMMA;
		case '+': return PLUS;
		case '-': return MINUS;
		case '*': return STAR;
		case '/': return FORWARD_SLASH;
		case '\\': return BACKWARDS_SLASH;
		case '%': return PERCENT;
		case '=': return EQUALS;
		case '<': return SMALLER;
		case '>': return GREATER;
		case '"': return QUOTATION_MARK;
		case '!': return EXCLAIMATION_MARK;
		case '?': return QUESTION_MARK;
	}

	return NONE;
}

Token matchDiagraph(const char c) {
	switch (c) {
		case '+': return PLUS_EQUALS;
		case '-': return MINUS_EQUALS;
		case '*': return STAR_EQUALS;
		case '/': return SLASH_EQUALS;
		case '%': return PERCENT_EQUALS;
		case '=': return EQUALS_EQUALS;
		case '<': return SMALLER_EQUALS;
		case '>': return GREATER_EQUALS;
		case '!': return EXCLAIMATION_EQUALS;
	}

	return NONE;
}

int main(int argc, char **argv) {
	if(argc < 2) {
		puts("expected filename");
		return EXIT_FAILURE;
	}
	FILE *file = fopen(argv[1], "r");
	if(!file) {
		puts("Unable to open file");
		return EXIT_FAILURE;
	}

	size_t len;
	char *buffer = (char*) malloc(BUFFER_LEN), *const more = (char*) malloc(BUFFER_LEN);

	while(getline(&buffer, &len, file) != -1) {
		int i = 0, j = 0;
		while(i < BUFFER_LEN && buffer[i] != EOF) {
			if( (buffer[i] >= 'a' && buffer[i] <= 'z') || (buffer[i] >= 'A' && buffer[i] <= 'Z') || buffer[i] == '_' ) {
				do {
					more[j] = buffer[i];
					i++, j++;
				} while( (buffer[i] >= 'a' && buffer[i] <= 'z') || (buffer[i] >= 'A' && buffer[i] <= 'Z') || buffer[i] == '_' );
 				more[j] = '\0';
				size_t key = matchKeyword(more);
				if(key != SIZE_MAX) {
					printf("keyword: %lu\n", key);
				} else {
					printf("identifier: %s\n", more);
				}
			} 
			else if(buffer[i] >= '0' && buffer[i] <= '9') {
				do {
					more[j] = buffer[i];
					i++, j++;
				} while(buffer[i] >= '0' && buffer[i] <= '9');
 				more[j] = '\0';
				printf("Number literal: %s\n", more);
			} 
			else if(buffer[i] == '"') {
				i++;
				while(buffer[i] != '"') {
					if(buffer[i] == '\\') {
						i++;
					}
					more[j] = buffer[i];
					i++, j++;
				}
				i++;
				more[j] = '\0';
				printf("Word literal: %s\n", more);
			}
			else if(!( buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\n' || buffer[i] == '\r' )) {
				if(buffer[i] == '/' && buffer[i+1] == '/') {
					break;
				}
				Token t = matchMonograph(buffer[i]);
				if(t != NONE && buffer[i+1] == '=' && matchDiagraph(buffer[i]) != NONE) {
					t = matchDiagraph(buffer[i]);
				}
				if(t != NONE) {
					printf("token: %u\n", t);
				}
				i++;
			}
			else {
				i++;
			}
			j = 0;
		}
	}

	return 0;
}
