#include <stdio.h>
#include <vector>
#include <queue>
#include <iostream>
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

void bfs(vector<vector<int>> v, int start) {
    queue<int> q;
    bool *visited;
    visited = new bool[v.size()];
    memset(visited, 0, sizeof(bool) * v.size());

    q.push(start);
    visited[start] = 1;
    int curNode;

    cout << start + 1;
    while (!q.empty()) {
        curNode = q.front();
        q.pop();

        for (int i = 0; i < v[curNode].size(); i++) {
            if (visited[v[curNode][i]] == false) {
                cout << " " << v[curNode][i] + 1;
                visited[v[curNode][i]] = true;
                q.push(v[curNode][i]);
            }
        }
    }
    cout << '\n';
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

    queue<int> sQ;

    int st, ed, q[N_MAX];
    st = ed = -1;

    sQ.push(1);
    chk[1] = 1;
    while (!sQ.empty()) {
        int here = sQ.front();
        printf("%d ", here);
        sQ.pop();
        for (i = 0; i < v[here].size(); i++) {
            if (!chk[v[here][i]]) {
                chk[v[here][i]] = 1;
                sQ.push(v[here][i]);
            }
        }
    }
    
    return 0;

}