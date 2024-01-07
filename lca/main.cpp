#include <iostream>
#include <stdio.h>
using namespace std;
#define MAXK 14
int V, E, Tree[10001][2], Parent[10001][MAXK+1], Depth[10001], Size[10001];

int lca(int n1, int n2)
{
    int u = Depth[n1] > Depth[n2] ? n1 : n2;
    int v = Depth[n1] > Depth[n2] ? n2 : n1;

    int diff = Depth[u] - Depth[v];
    for (int k = 0; diff; ++k) {
        if (diff % 2) u = Parent[u][k];
        diff /= 2;
    }

    if (u != v) {
        for (int k = MAXK; k >= 0; --k) {
            if (Parent[u][k] != -1 && Parent[u][k] != Parent[v][k]) {
                u = Parent[u][k];
                v = Parent[v][k];
            }
        }  
        u = Parent[u][0];
    }
    

    return u;
}

int traversal(int node, int depth) {
    int cnt = 0;
    if (node != 0) {
        cnt++;
        cnt += traversal(Tree[node][0], depth + 1);
        cnt += traversal(Tree[node][1], depth + 1);
    }
    Depth[node] = depth;
    Size[node] = cnt;
    
    return cnt;
}
int main(void)
{
    int tcCnt, n1, n2;

    setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

    cin >> tcCnt;

    for (int t = 1; t <= tcCnt; ++t) {
        cin >> V >> E >> n1 >> n2;
          
        for (int i = 1; i <= V; ++i) {
            Tree[i][0] = Tree[i][1] = 0;
            for (int k = 0; k <= MAXK; ++k) {
                Parent[i][k] = -1;
            }
        }

        for (int i = 0; i < E; ++i) {
            int p, c;
            cin >> p >> c;
            if (Tree[p][0] == 0) {
                Tree[p][0] = c;
            } else {
                Tree[p][1] = c;
            }
            Parent[c][0] = p;
        }
        for (int k = 0; k < MAXK; ++k) {
            for (int i = 1; i <= V; ++i) {
                if (Parent[i][k] != -1) {
                    Parent[i][k + 1] = Parent[Parent[i][k]][k];
                }
            }
        }
        traversal(1, 0);
        int anc = lca(n1, n2);

        cout << "#" << t << ' ' << Size[anc] << endl;
    }

    return 0;

}