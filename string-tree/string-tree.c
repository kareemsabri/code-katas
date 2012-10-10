#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int validate(char *node) {
	int offset = 0;
	char *stack = (char *)malloc(strlen(node)*sizeof(char));
	int num = 0;
	while(*(node + offset) != '\0') {
		switch(*(node + offset)) {
			case '(':
				stack[num++] = '(';
				break;
			case '0':
				stack[num++] = '0';
				break;
			case ')':
				if (stack[num - 1] == '0' && stack[num - 2] == '0' && stack[num - 3] == '(') {
					num -= 3;
					if (num == 0) {
						break;
					}
					//we've validated a full node, chop it off by replacing it with a 0 on the stack.
					stack[num++] = '0';
				} else {
					return 0;
				}
				break;
			default:
				return 0;
		}
		offset++;
	}
	return num == 0;
}

int recursive_find_depth(char *node) {
     if (*node == '(' && *(node + 1) == '0' && *(node + 2) == '0' && *(node + 3) == ')') return 0;
     int leftDepth, open = 0;
     if (*(node + 1) == '0') {
     	leftDepth = 0;
     } else {
     	leftDepth = recursive_find_depth(node + 1);
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
     int rightDepth = *node == '0' ? 0 : recursive_find_depth(node);
     return leftDepth > rightDepth ? 1 + leftDepth : 1 + rightDepth;
}

int find_depth(char *node) {
	if (validate(node)) {
		return recursive_find_depth(node);
	} else {
		return -1;
	}
}

int main(int argc, char const *argv[])
{
	/* code */
 	assert(find_depth("(00)") == 0);
    assert(find_depth("((00)0)") == 1);
    assert(find_depth("((00)(00))") == 1);
    assert(find_depth("((00)(0(00)))") == 2);
    assert(find_depth("((00)(0(0(00))))") == 3);
    assert(find_depth("x") == -1);
    assert(find_depth("0") == -1);
    assert(find_depth("()") == -1);
    assert(find_depth("(0)") == -1);
    assert(find_depth("(00)x") == -1);
    assert(find_depth("(0p)") == -1);
    assert(find_depth("((0(0)(00))") == -1);
	return 0;
}