#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*typedef struct {
    int position;
    int height;
} Tower;

void dfs(int** tower, size_t tower_rows, int k, int current, int* groups, int groupCnt) {
    if (current >= tower_rows) {
        return;
    }

    groups[current] = groupCnt;

    for (int i = current + 1; i < tower_rows; i++) {
        int distance = tower[i][0] - tower[current][0];
        if (distance <= k && tower[i][1] == tower[current][1]) {
            dfs(tower, tower_rows, k, i, groups, groupCnt);
        }
    }
}

int solution(int** tower, size_t tower_rows, size_t tower_cols, int k) {
    int* groups = (int *)malloc(tower_rows * sizeof(int));
    int groupCnt = 0;

    for (size_t i = 0; i < tower_rows; i++) {
        if (groups[i] == 0) {
            groupCnt++;
            dfs(tower, tower_rows, k, i, groups, groupCnt);
        }
    }

    free(groups);
    return groupCnt;
}*/


void dfs(int** tower, size_t tower_rows, int k, int current, int* groups, int groupCnt) {
    if (groups[current] != 0) {
        return;
    }

    groups[current] = groupCnt;
    for (int i = current + 1; i < tower_rows; i++) {
        if (groups[i] != 0) {
            continue;
        }
        int distance = tower[i][0] - tower[current][0];
        if (distance <= k && tower[i][1] == tower[current][1]) {
            dfs(tower, tower_rows, k, i, groups, groupCnt);
        }
        
    }
}
int solution(int** tower, size_t tower_rows, size_t tower_cols, int k) {
    int* groups = (int *)malloc(tower_rows * sizeof(int));
    int groupCnt = 0;

    for (size_t i = 0; i < tower_rows; i++) {
        if (groups[i] == 0) {
            groupCnt++;
            dfs(tower, tower_rows, k, i, groups, groupCnt);
        }
    }

    free(groups);
    return groupCnt;
}
int main() {
    int towerData[][2] = {{0, 2}, {2, 3}, {3, 2}, {5, 3}, {6, 2}, {7, 3}, {9, 4}, {10, 2}, {11, 2}, {12, 4}, {14, 2}, {15, 3}, {16, 2}};
    size_t tower_rows = sizeof(towerData) / sizeof(towerData[0]);
    size_t tower_cols = sizeof(towerData[0]) / sizeof(towerData[0][0]);

    int k = 3;

    int** tower = (int**)malloc(tower_rows * sizeof(int*));
    for (size_t i = 0; i < tower_rows; i++) {
        tower[i] = (int*)malloc(tower_cols * sizeof(int));
        for (size_t j = 0; j < tower_cols; j++) {
            tower[i][j] = towerData[i][j];
        }
    }

    int answer = solution(tower, tower_rows, tower_cols, k);
    printf("Result: %d\n", answer);

    // 메모리 해제
    for (size_t i = 0; i < tower_rows; i++) {
        free(tower[i]);
    }
    free(tower);

    return 0;
}
