#include <stdio.h>

#define MAX 10 

int factorial(int num) {
    if (num == 0) {
        return 1;
    } else {
        return num * factorial(num - 1);
    }
}
int main(void) 
{
    int N = MAX;

    printf("ans=%lld\n", factorial(N));
}