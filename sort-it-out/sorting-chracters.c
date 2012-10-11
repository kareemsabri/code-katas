#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main(int argc, char const *argv[])
{
	int *letterOccurenceCount = (int *)calloc(26,sizeof(int));
	char *buffer = (char *)malloc(256*sizeof(char));
	printf("Enter a string: ");
	gets(buffer);
	printf("\n");
	while(*buffer != '\0') {
		*buffer = tolower(*buffer);
		if (*buffer >= 'a' && *buffer <= 'z') {
			letterOccurenceCount[*buffer - 'a']++;
		}
		buffer++;
	}
	int i;
	for(i=0; i<26; i++) {
		int j;
		for(j=0; j<letterOccurenceCount[i]; j++) {
			printf("%c", 'a' + i);
		}
	}
	printf("\n");
	return 0;
}