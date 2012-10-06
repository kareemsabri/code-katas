#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct node {
	unsigned long long int key;
	char *word;
	struct node *next;
} node;

void insert(unsigned long long int key, char *word, node *array, int size) {
	int index = key % size;
	//check for collision
	while(array[index].key != 0 && array[index].key != key) {
		//probe linearly
		index = (index + 1) % size;
	}
	//first entry
	if (array[index].key == 0) {
		array[index].key = key;	
		array[index].word = word;
		array[index].next = NULL;
		return;		
	}
	//chaining with anagram
	node *tmp = &array[index];
	while(tmp->next != NULL) {
		tmp = tmp->next;
	}
	tmp->next = (node *)malloc(sizeof(node));
	tmp->next->key = key;
	tmp->next->word = word;
	tmp->next->next = NULL;
}

void print(node *array, int size) {
	int i;
	int anagramSetCount = 0;
	for(i = 0; i < size; i++) {
		if (array[i].key != 0 && array[i].next != NULL) {
			anagramSetCount++;
			node *tmp = array + i;
			while(tmp != NULL) {
				printf("%s ", tmp->word);
				tmp = tmp->next;
			}
			printf("\n");
		}
	}
	printf("found %d sets of anagrams\n", anagramSetCount);
}

int main(int argc, char const *argv[]) {
	clock_t start = clock();
	const int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};
	FILE *file = fopen("/usr/share/dict/words", "r");
	char *word = (char *)malloc(100*sizeof(char));
	int wordCount = 0;
	int letterCount = 0;
	
	while((word = fgets(word, 100, file)) != NULL) {
		wordCount++;
		letterCount += strlen(word);
	}

	rewind(file);

	char **wordArray = (char **)malloc(wordCount*(sizeof(char *)));
	*wordArray = (char *)malloc(letterCount*sizeof(char));

	char *current = *wordArray;
	node *head = (node *)calloc(wordCount, sizeof(node));
	int i;
	int size = wordCount;
	for(i=0; i<wordCount; i++) {
		*(wordArray + i) = current;
		fgets(*(wordArray + i), 100, file);
		unsigned long long int product = 1;
		char *j = *(wordArray + i);
		int k;
		do {
			product *= primes['z' - tolower(*j)];
		} while(*++j != '\n');
		*j = '\0';
		insert(product, current, head, size);
		current += strlen(*(wordArray + i)) + 1;
	}

	print(head, size);
	printf ("time: %f seconds\n", ( (double)clock() - start ) / CLOCKS_PER_SEC );
	return 0;
}