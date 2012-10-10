#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int find_depth(char *node) {
     if (*node == '(' && *(node + 1) == '0' && *(node + 2) == '0' && *(node + 3) == ')') return 0;
     int leftDepth, open = 0;
     if (*(node + 1) == '0') {
     	leftDepth = 0;
     } else {
     	leftDepth = find_depth(node + 1);
     	open = 1;
     }
     node+=2;
     while(open > 0) {
     	if (*node == '(') {
     		open++;
     	} else if (*node == ')') {
     		open--;
     	}
     	node++;
     }
     int rightDepth = *node == '0' ? 0 : find_depth(node);
     return leftDepth > rightDepth ? 1 + leftDepth : 1 + rightDepth;
}

int main(int argc, char const *argv[])
{
	/* code */
 	assert(find_depth("(00)") == 0);
    assert(find_depth("((00)0)") == 1);
    assert(find_depth("((00)(00))") == 1);
    assert(find_depth("((00)(0(00)))") == 2);
    assert(find_depth("((00)(0(0(00))))") == 3);
	return 0;
}