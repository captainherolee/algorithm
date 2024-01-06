#include <stdio.h>
#include <vector>
#define N_MAX 100000
using namespace std;

bool chk[N_MAX];
int st, ed, n, m;
vector<int> v[N_MAX];

void dfs(int here)
{
    chk[here] = 1;
    printf("%d", here);
    for (int i = 0; i < v[here].size(); i++) {
        if (!chk[v[here][i]]) dfs(v[here][i]);
    }
}

int main()
{
    int i;
    scanf("%d %d", &n, &m);
    st = 1; ed = n;

    for (i = 1; i <= m; i++) {
        int le, ri;
        scanf("%d %d", &le, &ri);
        v[le].push_back(ri);
        v[ri].push_back(le);
    }

    for (i = 1; i <= n; i++) {
        if (!chk[i]) dfs(i);
    }

    return 0;

}