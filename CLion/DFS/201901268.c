//
// Created by SeungJun Ryu on 2023/05/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

struct Vertex {
    int n;
    bool visited;
};

//stack
int stack[MAX];
int top;

// 배열 arr 설정
struct Vertex *arr[MAX];

// 배열 adj matrix`
int adj_mat[MAX][MAX];

// count
int count = 0;

// 초기화 함수
void init() {
    top = -1;
}

// 삽입 함수
void push(int item) {
    stack[++top] = item;
}

// 삭제 함수
int pop() {
    return stack[top--];
}

// peek함수 -> 읽기함수
int peek() {
    return stack[top];
}


int is_empty() {
    return (top == -1);
}

void insert_vertex(char item) {
    struct Vertex *v = (struct Vertex *) malloc(sizeof(struct Vertex));
    v->n = item;
    v->visited = false;
    arr[count++] = v;
}

void insert_edge(int i, int j) {
    adj_mat[i][j] = 1;
    adj_mat[j][i] = 1;
}

int get_vertex(int i) {
    for (int v = 0; v < count; v++) {
        if (adj_mat[i][v] == 1 && arr[v]->visited == false) {
            return v;
        }
    }
    return -1;
}

void dfs_iterate() {
    arr[0]->visited = 1;

    printf("정점 %c -> ", arr[0]->n);
    push(0);

    while (!is_empty()) {
        int isVisited = get_vertex(peek());

        if (isVisited == -1) {
            pop();
        } else {
            arr[isVisited]->visited = true;
            printf("정점 %c -> ", arr[isVisited]->n);
            push(isVisited);
        }
    }
}

int main() {
    int i, j;
    init();

    for (i = 0; i < 4; i++) {
        for (j = 0; j < MAX; j++)
            adj_mat[i][j] = 0;
    }

    insert_vertex('0');
    insert_vertex('1');
    insert_vertex('2');
    insert_vertex('3');
    insert_vertex('4');

    insert_edge(0, 1);
    insert_edge(0, 2);
    insert_edge(0, 3);
    insert_edge(1, 2);
    insert_edge(2, 3);

    printf("명시적 스택을 이용한 깊이 우선 탐색\n");
    dfs_iterate();
}