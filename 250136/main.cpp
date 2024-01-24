#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define f_max(x, y) ((x)>(y))?((x)):((y));

int drdc[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int *check;
int **visited;
int *arr;


int dfs(int r, int c, int land_rows, int land_cols, int** land){
    int res = 1;
    int nr;
    int nc;
    for (int i = 0; i < 4; i++){
        nr = r + drdc[i][0];
        nc = c + drdc[i][1];
        // 범위 안에서, 석유가 있고, 방문하지 않은 곳
        if (0 <= nr && nr < land_rows && 0 <= nc && nc < land_cols && land[nr][nc] == 1 && visited[nr][nc] == 0){
            visited[nr][nc] = 1;
            check[nc] = 1;
            res += dfs(nr, nc, land_rows, land_cols, land);
        }
    }
    return res;
};


// land_rows는 2차원 배열 land의 행 길이, land_cols는 2차원 배열 land의 열 길이입니다.
int solution(int** land, size_t land_rows, size_t land_cols) {
    int answer = 0;
    // land_rows: 세로길이
    // land_cols: 가로길이

    // check, arr, visited 생성 및 초기화
    check = (int *)malloc(sizeof(int) * land_cols);
    arr = (int *)malloc(sizeof(int) * land_cols);
    for (int i = 0; i < land_cols; i++) {
        arr[i] = 0;
        check[i] = 0;
    }
    visited = (int **)malloc(sizeof(int*) * land_rows);
    for (int i = 0; i < land_rows; i++) {
        visited[i] = (int *)malloc(sizeof(int) * land_cols);
        for (int j = 0; j < land_cols; j++) {
            visited[i][j] = 0;
        }
    }
    for (int i = 0; i < land_rows; i++) {
        for (int j = 0; j < land_cols; j++) {
            if (land[i][j] == 1 && visited[i][j] == 0) {
                visited[i][j] = 1;
                check[j] = 1;
                int num = dfs(i, j, land_rows, land_cols, land);
                for (int k = 0; k < land_cols; k++) {
                    if (check[k]) {
                        arr[k] += num;
                        check[k] = 0;
                    }
                }
            }
        }
    }

    for (int i = 0; i < land_cols; i++) {
        answer = f_max(answer, arr[i]);
        //printf("%d\n", answer);
    }
    free(check);
    free(arr);
    for (int i = 0; i < land_rows; i++) {
        free(visited[i]);
    }
    free(visited);
    return answer;
}

int main(void) {
    int land_data[5][8] = {{0, 0, 0, 1, 1, 1, 0, 0}, {0, 0, 0, 0, 1, 1, 0, 0}, {1, 1, 0, 0, 0, 1, 1, 0}, {1, 1, 1, 0, 0, 0, 0, 0}, {1, 1, 1, 0, 0, 0, 1, 1}};
    int* land[5]; // 포인터 배열을 사용하여 2D 배열을 표현

    for (int i = 0; i < 5; i++) {
        land[i] = land_data[i];
    }

    printf("%d\n", solution(land, 5, 8));
    return 0;
}