#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <cstring>
#include <stdio.h>
 
#define MAXL    (11)
#define MAX_N 50000
 
using namespace std;
 
unordered_map<string, int> um;
vector<int> child[MAX_N];
int parent[MAX_N];
int depth[MAX_N];
int vis[MAX_N];
int idx;
int step;
 
void init(char mRootSpecies[MAXL])
{   
    um.clear();
    step = 0;
    memset(parent,0,sizeof(parent));
    memset(depth,0,sizeof(depth));
    memset(vis,0,sizeof(vis));
    for(int i=0; i<MAX_N; ++i) child[i].clear();
 
    idx = 0;
    depth[idx] = 0;
    um.insert({mRootSpecies, idx});
    idx++;
}
 
void add(char mSpecies[MAXL], char mParentSpecies[MAXL])
{
    int pidx = um.find(mParentSpecies)->second;
    int cidx = idx++;
 
    parent[cidx] = pidx;
    depth[cidx] = depth[pidx]+1;
 
    child[pidx].push_back(cidx);
 
    um.insert({mSpecies, cidx});
}
 
int getDistance(char mSpecies1[MAXL], char mSpecies2[MAXL])
{
    int idx1 = um.find(mSpecies1)->second;
    int idx2 = um.find(mSpecies2)->second;
    if(depth[idx1] < depth[idx2]) {
        int tmp = idx1;
        idx1 = idx2;
        idx2 = tmp;
    }
 
    int ans = 0;
    while(depth[idx1] > depth[idx2]) {
        idx1 = parent[idx1];
        ans++;
    }
 
    if(idx1 == idx2) {
        return ans;
    } else {
        while(idx1 != idx2) {
            idx1 = parent[idx1];
            idx2 = parent[idx2];
            ans += 2;
        }
    }
 
    return ans;
}
 
int getCount(char mSpecies[MAXL], int mDistance)
{   
    int sidx = um.find(mSpecies)->second;
    queue<int> q;
    q.push(sidx);
    vis[sidx] = ++step;
 
    int ans = 0;
    int dist = 0;
    while(!q.empty() && dist < mDistance) {
        dist++;
        int sz = (int)q.size();
 
        for(int i=0; i<sz; ++i) {
            int nidx = q.front(); q.pop();
 
            if(vis[parent[nidx]] != step) {
                vis[parent[nidx]] = step;
                q.push(parent[nidx]);
                if(dist == mDistance) ans++;
            }
 
            for(int j=0; j<(int)child[nidx].size(); ++j) {
                if(vis[child[nidx][j]] != step) {
                    vis[child[nidx][j]] = step;
                    q.push(child[nidx][j]);
                    if(dist == mDistance) ans++;
                }
            }
        }
    }
 
    return ans;
}