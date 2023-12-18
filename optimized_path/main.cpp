#include <iostream>
using namespace std;

#define ABS(x) (x < 0 ? -(x) : (x))
#define INF 2147483647
#define MAX_N 12

int N, ArrX[MAX_N], ArrY[MAX_N];
int Graph[MAX_N][MAX_N];
int Memo[MAX_N][1 << MAX_N];

void makeGraph() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i == j) {
                Graph[i][j] = 0;
            } else {
                Graph[i][j] = ABS(ArrX[i] - ArrX[j]) + ABS(ArrY[i] - ArrY[j]);
            }
        }
    }
}

// 완전탐색을 이용한 풀이 코드
int solve1(int pos, int visited) {
    if (visited == (1 << N) - 1 - 2) 
        return Graph[pos][1];

    int ret = INF;
    for (int next = 2; next < N; ++next) {
        if (!(visited & (1 << next)) && Graph[pos][next]) {
            int tmp = Graph[pos][next] + solve1(next, visited | (1<<next));
            if (tmp < ret) ret = tmp;
        } 
    }
    return ret;
}

// memo
int solve(int pos, int visited) {
    int& ret = Memo[pos][visited];
    if (ret != -1) return ret;

    if (visited == (1 << N) - 1 - 2) 
        return ret = Graph[pos][1];

    ret = INF;
    for (int next = 2; next < N; ++next) {
        if (!(visited & (1 << next)) && Graph[pos][next]) {
            int tmp = Graph[pos][next] + solve(next, visited | (1<<next));
            if (tmp < ret) ret = tmp;
        }
    }
    return ret;
}

int main(int argc, char** argv) {
    int tcCnt;
    freopen("sample_input.txt", "r", stdin);

    cin >> tcCnt;
    for (int t = 1; t <= tcCnt; ++t) {
        for (int i = 0; i < MAX_N; ++i) {
            for (int j = 0; j < 1 << MAX_N; ++j) {
                Memo[i][j ] = -1;
            }
        }
        
        cin >> N;
        N += 2;
        for (int i = 0; i < N; ++i) {
            cin >> ArrX[i] >> ArrY[i];
        }
        makeGraph();
        cout << "#" << t << ' ' << solve(0, 1) << endl;
    }
    return 0;
}
