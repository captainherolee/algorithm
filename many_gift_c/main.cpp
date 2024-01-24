#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// friends_len은 배열 friends의 길이입니다.
// gifts_len은 배열 gifts의 길이입니다.
// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
int solution(const char* friends[], size_t friends_len, const char* gifts[], size_t gifts_len) {
    int gift_given[50] = {0,};
    int gift_received[50] = {0,};
    int gift_index[50][50] = {0,};
    int next_month[50] = {0,};
    int max_gift = 0;

    for(int i = 0; i < gifts_len; i++) {
        char giver[11];
        char receiver[11];
        sscanf(gifts[i], "%s %s", giver, receiver);
        int giver_index = -1;
        int receiver_index = -1;

        for(int j = 0; j < friends_len; j++) {
            if(strcmp(friends[j], giver) == 0) {
                giver_index = j;
            }
            if(strcmp(friends[j], receiver) == 0) {
                receiver_index = j;
            }
        }

        gift_given[giver_index]++;
        gift_received[receiver_index]++;
        gift_index[giver_index][receiver_index]++;
    }

    for(int i = 0; i < friends_len; i++) {
        for(int j = 0; j < friends_len; j++) {
            if(i != j) {
                if(gift_index[i][j] > gift_index[j][i]) {
                    next_month[i]++;
                } else if(gift_index[i][j] == gift_index[j][i] && gift_given[i] - gift_received[i] > gift_given[j] - gift_received[j]) {
                    next_month[i]++;
                }
            }
        }
    }

    for(int i = 0; i < friends_len; i++) {
        if(next_month[i] > max_gift) {
            max_gift = next_month[i];
        }
    }

    return max_gift;
}

int main(void)
{
    const char* friends[] = {"muzi", "ryan", "frodo", "neo"};
    const char* gifts[] = {"muzi frodo", "muzi frodo", "ryan muzi", "ryan muzi", "ryan muzi", "frodo muzi", "frodo ryan", "neo muzi"};

    printf("%d\n", solution(friends, 4, gifts, 9));
}