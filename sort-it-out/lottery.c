#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define NUM_BALLS 60

int bytes(int bits) {
	return (bits / 8) + (bits % 8 != 0);
}

int add(int number, void *balls) {
	if (number < 0 || number >= NUM_BALLS) {
		return -1;
	}

	int byteNum = number / 8;
	char mask = 0x01 << number % 8;
	*((char*)balls + byteNum) |= mask;
	return 1;
}

void print(void *balls) {
	int i;
	for(i=0; i<bytes(NUM_BALLS); i++) {
		char byte = *((char*)balls + i);
		int j = 0;
		while(byte > 0) {
			if (byte & 0x1) {
				printf("%d ", i*8 + j);
			}
			j++;
			byte >>= 1;
		}
	}
	printf("\n");
}

int main(int argc, char const *argv[]) {
	char *balls = (char *)calloc(bytes(NUM_BALLS), sizeof(char));
	add(20, balls);
	add(10, balls);
	add(5, balls);
	add(32, balls);
	add(60, balls);
	add(59, balls);
	add(32, balls);
	print(balls);
	return 0;
}