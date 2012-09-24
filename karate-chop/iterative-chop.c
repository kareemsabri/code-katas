#include <stdio.h>
#include <assert.h>

int chop(int key, int array[], int length) {
	int lower = 0;
	int upper = length - 1;
	int middle;
	while(upper >= lower) {
		middle = lower + (upper - lower) / 2;
		if (array[middle] == key) {
			return middle;
		}
		if (array[middle] < key) {
			lower = middle + 1;
			continue;
		}
		if (array[middle] > key) {
			upper = middle - 1;
			continue;
		}
	}
	return -1;
}

int main(int argc, char *argv[]) {
	int array1[0] = {};
    int array2[1] = {1};
    int array3[3] = {1,3,5};
    int array4[4] = {1,3,5,7};

    assert(-1 == chop(3, array1, 0));
	printf("%d\n", chop(3, array1, 0));

    assert(-1 == chop(3, array2, 1));
	printf("%d\n", chop(3, array2, 1));

    assert(0 == chop(1, array2, 1));
    printf("%d\n", chop(1, array2, 1));

    assert(0 == chop(1, array3, 3));
	printf("%d\n", chop(1, array3, 3));

	assert(1 == chop(3, array3, 3));
    printf("%d\n", chop(3, array3, 3));
	
	assert(2 == chop(5, array3, 3));
    printf("%d\n", chop(5, array3, 3));

	assert(-1 == chop(0, array3, 3));
    printf("%d\n", chop(0, array3, 3));

	assert(-1 == chop(2, array3, 3));
    printf("%d\n", chop(2, array3, 3));

	assert(-1 == chop(4, array3, 3));
    printf("%d\n", chop(4, array3, 3));

	assert(-1 == chop(6, array3, 3));
    printf("%d\n", chop(6, array3, 3));
    
    assert(0 == chop(1, array4, 4));
	printf("%d\n", chop(1, array4, 4));
    
    assert(1 == chop(3, array4, 4));
    printf("%d\n", chop(3, array4, 4));
    
    assert(2 == chop(5, array4, 4));
    printf("%d\n", chop(5, array4, 4));
    
    assert(3 == chop(7, array4, 4));
    printf("%d\n", chop(7, array4, 4));
    
    assert(-1 == chop(0, array4, 4));
    printf("%d\n", chop(0, array4, 4));
    
    assert(-1 == chop(2, array4, 4));
    printf("%d\n", chop(2, array4, 4));
    
    assert(-1 == chop(4, array4, 4));
    printf("%d\n", chop(4, array4, 4));
    
    assert(-1 == chop(6, array4, 4));
    printf("%d\n", chop(6, array4, 4));
    
    assert(-1 == chop(8, array4, 4));
    printf("%d\n", chop(8, array4, 4));
}