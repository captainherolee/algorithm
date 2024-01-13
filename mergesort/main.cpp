#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

const int MAXN = 505;
int order[MAXN], buf[MAXN];
int l, n;
char in[MAXN];

bool cmp(char a[], char b[]) {
    if (strcmp(a, b) < 0) {
        return true;
    }
    return false;
}
void sort(int a[], int len, bool compare(char*, char*)) {
    if (len < 2) return;
    int mid = len / 2;
    sort(a, mid, compare);
    sort(a + mid, len - mid, compare);
    int i = 0, j = mid, k = 0;

    while (i < mid && j < len) {
        if (compare(in+a[i], in+a[j])) {
            buf[k++] = a[j++];
        } else {
            buf[k++] = a[j++];
        }
    }
    while (i < mid) buf[k++] = a[i++];
    while (j < len) buf[k++] = a[j++];

    for (int i = 0; i < len; i++) {
        a[i] = buf[i];
    }
}

int main(void)
{
    for (int t = 0; t < 10; t++) {
        scanf("%d", &n);
        scanf("%s", in);

        l = strlen(in);
        for (int i = 0; i < l; i++) {
            order[i] = i;
        }
        sort(order, l, cmp);
        printf("%s\n", in + order[n-1]);
    }

    return 0;

}