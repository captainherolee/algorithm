#include <stdio.h>
#include <queue>
#include <cstring>
#include <vector>
#include <string>

using namespace std;
#define MAXN 1000
#define MAX_WEIGHT 30001

struct Node {
    int dest;
    int weight;
};

vector<Node> Adj[MAXN+1];
int TotalN;
int Visited[MAXN];


void init(int N, int K, int sCity[], int eCity[], int mLimit[]) {
    TotalN = N;
    for (int i = 0; i < TotalN; i++) {
        Adj[i].clear();
        Visited[i] = 0;
    }

    for (int i = 0; i < K; ++i) {
        Adj[sCity[i]].push_back({eCity[i], mLimit[i]});
    }

    return;
}

void add(int sCity, int eCity, int mLimit) {
    Adj[sCity].push_back({eCity, mLimit});
	return;
}

struct compare {
    bool operator()(const Node &p1, Node &p2) {
        return p1.weight < p2.weight;
    }
};
void bfs(int sCity, int eCity, int& maxWeight) {
    priority_queue<Node, vector<Node>, compare> pq;

    pq.push({sCity, MAX_WEIGHT});
    Visited[sCity] = 1;
    Node curr;
    while (pq.size()) {
        curr = pq.top();

        if (curr.dest == eCity) {
            maxWeight = curr.weight;
            return;
        }
        pq.pop();
        Visited[curr.dest] = 1;
        for (auto &p : Adj[curr.dest]) {
            if (Visited[p.dest] != 1) {
                pq.push({p.dest, p.weight < curr.weight ? p.weight : curr.weight});
            }
        }
    }
}

int calculate(int sCity, int eCity) {
    int maxWeight;
    int ans = 0;
    memset(Visited, 0, sizeof(Visited));
    bfs(sCity, eCity, maxWeight);
    if (maxWeight != 0) {
        return maxWeight;
    }

    return -1;
}