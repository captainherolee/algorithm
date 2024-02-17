#include<vector>
#include<cstring>
#include<algorithm>
 
using namespace std;
 
#define MAX_N 40000 //39990
#define MAX_L 10
#define MAX_NL 4000 //3999
 
struct Player {
    int id;
    int ability;
};
 
bool compare (const Player& A, const Player& B) {
    if (A.ability == B.ability) return A.id < B.id;
    else return A.ability > B.ability;
}
 
vector <Player> playerVector[MAX_L + 1];
Player lowOfLeague[MAX_L + 1];
Player highOfLeague[MAX_L + 1];
 
int N, L, LofN, totalIdValue;
 
void init(int N, int L, int mAbility[]) {
    ::N = N;
    ::L = L;
    LofN = N/L;
 
    for (int i = 0; i < MAX_L + 1; ++i) {
        playerVector[i].clear();
    }
 
    int count = 0;
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < LofN; ++j) {
            playerVector[i].push_back({ count, mAbility[(LofN)*i + j] });
            count++;
        }
    }
 
    for (int i = 0; i < L; ++i) {
        sort(playerVector[i].begin(), playerVector[i].end(), compare);
    }
}
 
int move() {
    totalIdValue = 0;
 
    for (int i = 0; i < L - 1; ++i) {
        lowOfLeague[i] = { 0,0 };
        highOfLeague[i] = { 0,0 };
    }
 
    for (int i = 0; i < L - 1; ++i) {
        lowOfLeague[i] = *playerVector[i].rbegin();
        highOfLeague[i] = *playerVector[i + 1].begin();
    }
 
    for (int i = 0; i < L - 1; ++i) {
        playerVector[i].pop_back();
        totalIdValue += lowOfLeague[i].id;
 
        playerVector[i + 1].erase(playerVector[i + 1].begin());
        totalIdValue += highOfLeague[i].id;
    }
 
    for (int i = 0; i < L - 1; ++i) {
        auto it = upper_bound(playerVector[i].begin(), playerVector[i].end(), highOfLeague[i], compare);
        playerVector[i].insert(it, highOfLeague[i]);
 
        it = upper_bound(playerVector[i + 1].begin(), playerVector[i + 1].end(), lowOfLeague[i], compare);
        playerVector[i + 1].insert(it, lowOfLeague[i]);
    }
    return totalIdValue;
}
 
int trade() {
    totalIdValue = 0;
 
    for (int i = 0; i < L - 1; ++i) {
        lowOfLeague[i] = { 0,0 };
        highOfLeague[i] = { 0,0 };
    }
 
    for (int i = 0; i < L - 1; ++i) {
        lowOfLeague[i] = playerVector[i][LofN / 2];
        highOfLeague[i] = *playerVector[i + 1].begin();
    }
 
    for (int i = 0; i < L - 1; ++i) {
        playerVector[i].erase(playerVector[i].begin() + LofN / 2);
        totalIdValue += lowOfLeague[i].id;
    }
 
    for (int i = 0; i < L - 1; ++i) {
        playerVector[i + 1].erase(playerVector[i + 1].begin());
        totalIdValue += highOfLeague[i].id;
    }
 
    for (int i = 0; i < L - 1; ++i) {
        auto it = upper_bound(playerVector[i].begin(), playerVector[i].end(), highOfLeague[i], compare);
        playerVector[i].insert(it, highOfLeague[i]);
 
        it = upper_bound(playerVector[i + 1].begin(), playerVector[i + 1].end(), lowOfLeague[i], compare);
        playerVector[i + 1].insert(it, lowOfLeague[i]);
    }
    return totalIdValue;
}