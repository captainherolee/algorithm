#include <vector>
#include <queue>
#include <cstring>

using namespace std;

#define MAXN 1000
#define MAXK 4000
#define MAX_WEIGHT 30000
#define TRUE 1
#define FALSE 0
struct Node {
    int dest;
    int weight;
};

vector<Node> Adj[MAXK];
int Visited[MAXN];
int TotalN;

void init(int N, int K, int sCity[], int eCity[], int mLimit[]) {
    TotalN = N;

    for (int i = 0; i < N; ++i) {
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
    bool operator()(Node &p1, Node &p2){
        return (p1.weight < p2.weight);
    }
};

int bfs(int sCity, int eCity) {
    priority_queue<Node, vector<Node>, compare> pq;
    int maxWeight = MAX_WEIGHT;
    pq.push({sCity, MAX_WEIGHT});
    Node curr;
    while (!pq.empty()) {
        curr = pq.top();
        if (curr.dest == eCity) {
            return curr.weight;
        }
        pq.pop();
        Visited[curr.dest] = TRUE;
    
        for (auto &p : Adj[curr.dest]) {
            if (Visited[p.dest] != TRUE) {
                pq.push({p.dest, p.weight < curr.weight ? p.weight : curr.weight});
            }            
        }
    }

    return -1;
}
int calculate(int sCity, int eCity) {
    int ret = 0;
    memset(Visited, 0, sizeof(Visited));
    ret = bfs(sCity, eCity);

    
    return ret;
}