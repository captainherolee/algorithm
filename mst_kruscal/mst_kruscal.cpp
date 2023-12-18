#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
#define MAX_N 100
const int INF = 0x3F;

int N, E, Graph[MAX_N][MAX_N];
int Parent[MAX_N], Weight[MAX_N];

int prim() {
    priority_queue < pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;

    //priority_queue <int, vector<int>, greater <int>> pq_min;
    //priority_queue <int, vector<int>, less <int>> pq_mx;
    
    bool visited[MAX_N] = {false};
    visited[0] = true;

    for (int next = 0; next < N; ++next) {
        pq.push(make_pair(Graph[0][next], next));
    }
    int sumCost = 0;
    while (!pq.empty()) {
        int curr = pq.top().second;
        int weight = pq.top().first;
        pq.pop();
        if (visited[curr]) continue;
        visited[curr] = true;
        sumCost += weight;

        for (int next = 0; next < N; ++next) {
            pq.push(make_pair(Graph[curr][next], next));
        }
    }
    return sumCost;
} 

int main(void) {
    freopen("graph_search_input.txt", "r", stdin);
    cin >> N >> E;

    for (int i = 0; i < N; ++i) {
        for( int j = 0; j < N; ++j) {
            Graph[i][j] = 0;
        }
    }
    for (int i = 0; i < E; ++i) {
        int a, b, weight;
        cin >> a >> b >> weight;
        Graph[a][b] = Graph[b][a] = 1;
        
    } 
    printf("hello world\n");
    return 0;
}