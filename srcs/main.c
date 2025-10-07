#include <stdio.h>
#include <stdlib.h>

#define BUFFER_LEN 128

int main() {
	FILE *file = fopen("HelloWorld.tpap", "r");
	size_t len;
	char *buffer = (char*) malloc(BUFFER_LEN), *const more = (char*) malloc(BUFFER_LEN);

	if(!file) {
		puts("no");
		return 1;
	}

	while(getline(&buffer, &len, file) != -1) {
		int j = 0;
		for(int i = 0; i < BUFFER_LEN && buffer[i] != '\n' && buffer[i] != '\0' && buffer[i] != EOF; i++) {
			if( buffer[i] == ' ' ) {
				more[j] = '\0';
				puts(more);
				j=0;
			} else {
				more[j] = buffer[i];
				j++;
			}
		}
		more[j] = '\0';
		puts(more);
	}

	return 0;
}
