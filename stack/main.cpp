#include <stdio.h>
#include <string>
#define MAX 100
int stack[MAX];
int top;

void stackInit(void) {
    top = 0;
}

int stackIsEmpty(void) {
    return (top == 0);
}

int stackIsFull(void) {
    return (top == MAX);
}

int stackPush(int val) {
    if (stackIsFull()) {
        printf("stack overflow");
        return 0;
    }

    stack[top++] = val;

    return 1;
}

int stackPop(int *value) {
    if (top == 0) {
        printf("stack is empty");
    }
    top--;
    *value = stack[top];

    return 1;
}


int main(void) {
    int T, N;

	scanf("%d", &T);

	for (int test_case = 1; test_case <= T; test_case++)
	{
		scanf("%d", &N);
		stackInit();
		for (int i = 0; i < N; i++) 
		{
			int value;
			scanf("%d", &value);
			stackPush(value);
		}

		printf("#%d ", test_case);

		while (!stackIsEmpty())
		{
			int value;
			if (stackPop(&value) == 1)
			{
				printf("%d ", value);
			}
		}
		printf("\n");
	}
	return 0;
}