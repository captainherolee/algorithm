#include <vector>
#include <string>
#include <map>
using namespace std;
#define MAX 50
int N;
int graph[MAX][MAX] = {0,};
int retGift[MAX] = {0,};

vector<string> split(string s) {
    vector<string> ret;
    string tmp;

    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == ' ') {
            ret.push_back(tmp);
            tmp.clear();
        } else {
            tmp.push_back(s[i]);
        }
    }
    ret.push_back(tmp);
    return ret;
}

int solution(vector<string> friends, vector<string> gifts) {
    int answer = 0;

    N = friends.size();
    map<string, int> nameTable;

    vector<int> giftPoint(N, 0);

    for (int i = 0; i < N; ++i) {
        nameTable[friends[i]] = i;
    }

    for (int i = 0; i < gifts.size(); ++i) {
        vector<string> giftLog = split(gifts[i]);
        int sendIdx = nameTable[giftLog[0]];
        int receiveIdx = nameTable[giftLog[1]];
        graph[sendIdx][receiveIdx]++;
        giftPoint[sendIdx]++;
        giftPoint[receiveIdx]--;
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (graph[i][j] == graph[j][i]) {
                int iGiftPoint = giftPoint[i];
                int jGiftPoint = giftPoint[j];
                if (iGiftPoint == jGiftPoint) continue;
                else if (iGiftPoint > jGiftPoint) {
                    retGift[i]++;
                } else {
                    retGift[j]++;
                }
            } else {
                if (graph[i][j] > graph[j][i]) {
                    retGift[i]++;
                } else {
                    retGift[j]++;
                }
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        answer = max(answer, retGift[i]);
    }

    return answer / 2;
}


int main(void)
{
    vector<string> friends = {"muzi", "ryan", "frodo", "neo"};
    vector<string> gifts  = {"muzi frodo", "muzi frodo", "ryan muzi", "ryan muzi", "ryan muzi", "frodo muzi", "frodo ryan", "neo muzi"};
   
    printf("%d\n", solution(friends, gifts));
}