#include <iostream>
#include <stdio.h>
using namespace std;

int N, Digit;
int Memo[1000000][20];

int swap(int num, int a, int b)
{
    int numArr[10];
    int tmp = num;

    for (int i = 0; i < Digit; ++i) {
        numArr[i] = tmp % 10;
        tmp /= 10;
    }

    if (numArr[a] == numArr[b]) {
        return num;
    }

    tmp = numArr[a];
    numArr[a] = numArr[b];
    numArr[b] = tmp;

    num = 0;
    for (int i = Digit - 1; i >= 0; --i) {
        num = num * 10 + numArr[i];
    }

    return num;
}

int solve(int num, int cnt)
{
    //memo
    int& ret = Memo[num][cnt];
    if (ret != -1) return ret;

    if (cnt == 0) return ret = num;

    ret = 0;
    for (int i = 0; i < Digit - 1; ++i) {
        for (int j = i + 1; j < Digit; ++j) {
            int tmp = solve(swap(num, i, j), cnt - 1);
            if (tmp > ret) ret = tmp;
        }
    }
    
    return ret;
}

int main(void)
{
    int tcCnt;

    setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

    cin >> tcCnt;

    for (int t = 1; t <= tcCnt; ++t) {
        int num, cnt;
        cin >> num >> cnt;
          
        Digit = 0;
        int tmp = num;
        while (tmp) {
            tmp /= 10;
            ++Digit;
        }
        ////// memo
        for (int i = 0; i < 1000000; ++i) {
            for (int j = 0; j <= cnt; ++j) {
                Memo[i][j] = -1;
            }
        }

        cout << "#" << t << ' ' << solve(num, cnt) << endl;
    }

    return 0;

}