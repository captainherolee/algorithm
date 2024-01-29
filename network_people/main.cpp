#include <stdio.h>
#include <cstring>
#define MAX 1000
int E[MAX][MAX];
int vis[MAX];
int size[MAX];
int n, t;
struct queue {
    int data[MAX];
    int f, r;
    void init() { f = r = 0;}
    void push(int a) { data[r++] = a; }
    int pop() { return data[f++]; }
    bool isEmpty() { return !(f < r);}
} q;

int calCC(int from) {
    memset(vis, -1, sizeof(vis));
    q.init(), q.push(from), vis[from] = 0;
    int here, there, ret = 0;
    while (!q.isEmpty()) {
        here = q.pop();
        for (int i = 0; i < size[here]; i++) {
            there = E[here][i];
            if (vis[there] != -1) continue;
            vis[there] = vis[here] + 1;
            q.push(there);
        }
    }
    for (int i = 0; i < n; i++) ret += vis[i];

    return ret;
}

int main(void) {
    int minCC = 2e9;
    scanf("%d", &n);
    memset(E, 0, sizeof(E));
    memset(size, 0, sizeof(size));

    int a, maxDc = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a);
            if (a) E[i][size[i]++] = j;
        }
    }

    for (int i = 0; i < n; i++) {
        int cc = calCC(i);
        if (minCC > cc) minCC = cc;
    }

    printf("%d %d\n", t, minCC);
}
