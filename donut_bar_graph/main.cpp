#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// edges_rows는 2차원 배열 edges의 행 길이, edges_cols는 2차원 배열 edges의 열 길이입니다.
int* solution(int** edges, size_t edges_rows, size_t edges_cols) {
    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.

    int* answer = (int*)malloc(4*sizeof(int));
    memset(answer,0,4*sizeof(int));

    int max_id = 0;
    for(int i=0; i<edges_rows; i++){
        for(int j=0; j<edges_cols; j++){
            if(max_id < edges[i][j]){
                max_id = edges[i][j];
            }
        }
    }

    int* point = (int*)malloc(max_id*2*sizeof(int));
    memset(point,0,max_id*2*sizeof(int));

    for(int i=0; i<edges_rows; i++){
        int src_id = edges[i][0]-1;
        int dst_id = edges[i][1]-1;
        point[src_id*2 + 0]++;
        point[dst_id*2 + 1]++;
    }

    int new_id = -1;
    for(int i=0;i<max_id;i++){
        if(point[i*2+0]>1 && point[i*2+1]==0){
            new_id = i;
        }
        if(point[i*2+0]==0){
            answer[2]++;
        }
        if(point[i*2+0]>1 && point[i*2+1]>1){
            answer[3]++;
        }
    }

    answer[0] = new_id+1;
    answer[1] = point[new_id*2+0] - answer[2] - answer[3];

    free(point);

    return answer;
}