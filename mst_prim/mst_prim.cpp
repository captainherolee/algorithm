#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
#define MAX_N 10001
const int INF = 0x3F;

struct Data {
    int id, weight;
    Data(int a, int b) {
        id = a;
        weight = b;
    }
    bool operator<(const Data &d) const {
        return weight < d.weight;
    }
};

priority_queue <Data> pQ;
vector<Data> Graph[MAX_N];
int N, E, Res;

int prim() {
    bool visited[MAX_N] = {false};
    pQ.push(Data(0,0));

    while (!pQ.empty()) {
       Data temp = pQ.top();
       pQ.pop();
       int id = temp.id;
       int val = temp.weight;
       if (visited[id] == 0) {
          visited[id] = 1;
          Res += val;
          for (int i = 0; i < Graph[id].size(); i++) {
            pQ.push({Graph[id][i].id, Graph[id][i].weight});
          }
       }
    }
    return Res;
} 

int main(void) {
    freopen("graph_search_input.txt", "r", stdin);
    cin >> N >> E;

    for (int i = 0; i < E; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        Graph[a].push_back(Data(b, c));
        Graph[b].push_back(Data(a, c));
    }
    Res = 0;
    printf("total min sum : %d\n", prim());

    return 0;
}