#include <stdio.h>
#include <stdlib.h>

#define BUFFER_LEN 128

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
		int j = 0;
		for(int i = 0; i < BUFFER_LEN && buffer[i] != '\n' && buffer[i] != '\0' && buffer[i] != EOF; i++) {
			if( (buffer[i] >= 'a' && buffer[i] <= 'z') || (buffer[i] >= 'A' && buffer[i] <= 'Z') || buffer[i] == '_' ) {
				more[j] = buffer[i];
				j++;
			} else if( buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == '\t' ) {
				more[j] = '\0';
				if(j > 0) {
					puts(more);
				}
				j=0;
			} else {
				more[j] = '\0';
				if(j > 0) {
					puts(more);
				}
				j=0;
				putchar(buffer[i]);
				putchar('\n');
			}
		}
//		more[j] = '\0';
//		puts(more);
	}

	return 0;
}
