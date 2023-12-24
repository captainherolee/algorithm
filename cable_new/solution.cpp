#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

#define MAX_N 10005
unordered_map<int, int>gUm; // 주어진 장치 ID와 해당 장치의 ID 번호를 매핑하는 용도로 사용
vector<pair<int, int>>gV[MAX_N]; //id , latency 
int N, MAX1, MAX2, MAX;

struct Node {
    int pID; // parent id
    int latency;
}gArrNode[MAX_N];

void init(int mDevice)
{
    gUm.clear();
    for (int i = 0; i < MAX_N; i++) {
        gV[i].clear();
    }
    N = 1;

    // save order for node 
    gUm[mDevice] = N;

    // Node Information in Array
    gArrNode[N].pID = -1;
    gArrNode[N].latency = 0;
    N++;

    return;
}

void connect(int mOldDevice, int mNewDevice, int mLatency)
{
    gUm[mNewDevice] = N;

    // identifier for each device 
    int oldID = gUm[mOldDevice];

    // Node Information in Array
    gArrNode[N].pID = oldID;
    gArrNode[N].latency = mLatency;

    // Added graph node
    gV[N].push_back({oldID, mLatency});
    gV[oldID].push_back({N, mLatency});
    N++;
    return;
}

int measure(int mDevice1, int mDevice2)
{
    int id1 = gUm[mDevice1];
    int id2 = gUm[mDevice2];
    int ans = 0;

    while (id1 != id2) {
        if (id1 < id2) {
            ans += gArrNode[id2].latency;
            id2 = gArrNode[id2].pID;
        }
        else {
            ans += gArrNode[id1].latency;
            id1 = gArrNode[id1].pID;
        }
    }
    return ans;
}

void dfs(int vertex,int par,int dist) {
    MAX = max(MAX, dist);
    for (auto it : gV[vertex]) {
        int childV = it.first;
        int d = it.second;
        if (childV == par) {
            continue;
        }
        dfs(childV, vertex, dist + d);
    }
}

int test(int mDevice)
{
    MAX1 = 0;
    MAX2 = 0;
    for (auto it : gV[gUm[mDevice]]) {
        int vertex = it.first;
        int rd = it.second;
        MAX = 0;
        dfs(vertex, gUm[mDevice], 0);
        MAX += rd;
        if (MAX > MAX1) {
            MAX2 = MAX1;
            MAX1 = MAX;
        }
        else if (MAX > MAX2) {
            MAX2 = MAX;
        }
    }
    return (MAX1+MAX2);
}

