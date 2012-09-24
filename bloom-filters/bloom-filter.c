#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define NUM_HASHES 5

unsigned int MurmurHash2 (const void * key, int len, unsigned int seed) {
	// 'm' and 'r' are mixing constants generated offline.
	// They're not really 'magic', they just happen to work well.

	const unsigned int m = 0x5bd1e995;
	const int r = 24;

	// Initialize the hash to a 'random' value

	unsigned int h = seed ^ len;

	// Mix 4 bytes at a time into the hash

	const unsigned char * data = (const unsigned char *)key;

	while(len >= 4)
	{
		unsigned int k = *(unsigned int *)data;

		k *= m; 
		k ^= k >> r; 
		k *= m; 
		
		h *= m; 
		h ^= k;

		data += 4;
		len -= 4;
	}
	
	// Handle the last few bytes of the input array

	switch(len)
	{
	case 3: h ^= data[2] << 16;
	case 2: h ^= data[1] << 8;
	case 1: h ^= data[0];
	        h *= m;
	};

	// Do a few final mixes of the hash to ensure the last few
	// bytes are well-incorporated.

	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;

	return h;
}

void hashes(const void *key, int len, int **result, int number, int max) {
	*result = (int*)malloc(number*sizeof(int));
	int hash1 = MurmurHash2(key, len, 13423);
	int hash2 = MurmurHash2(key, len, 345);
	int i;
	for (i=0; i<NUM_HASHES; i++) {
		*(*result + i) = abs((hash1 + i * hash2) % max);
	}
}

void insert(const void *key, int max, char * bitarray) {
	int *result, i;
	hashes(key, strlen((char *)key), &result, NUM_HASHES, max);
	for (i=0; i<NUM_HASHES; i++)  {
		int offset = *(result + i) / (8*sizeof(char));
		unsigned char * mask = (unsigned char *)malloc(sizeof(char));
		*mask = 0x01;
		*mask <<= *(result + i) % (8*sizeof(char));
		bitarray[offset] |= *mask;
	}
}

bool contains(const void *key, int max, char * bitarray) {
	int *result, i;
	hashes(key, strlen((char *)key), &result, NUM_HASHES, max);
	for (i=0; i<NUM_HASHES; i++) {
		int offset = *(result + i) / (8*sizeof(char));
		unsigned char * mask  = (unsigned char *)malloc(sizeof(char));
		*mask = 0x01;
		*mask <<= *(result + i) % (8*sizeof(char));
		*mask &= bitarray[offset];
		if (*mask == 0x00) {
			return false;
		}
	}
	return true;
}


int main(int argc, char const *argv[]) {
	FILE *input = fopen("/usr/share/dict/words", "r");
	char word[100];
	int length = 0;
	while(fgets(word, 100, input) != NULL) {
		length++;
	}
	length *= 10;
	char *bitarray = (char *)malloc((length / 8) + 1);
	rewind(input);
	while(fgets(word, 100, input) != NULL) {
		insert(word, length, bitarray);
	}
	while(fgets(word, 100, stdin)) {
		printf("%d\n", contains(word, length, bitarray));
	}
	return 0;
}