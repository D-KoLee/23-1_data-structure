//
// Created by SeungJun Ryu on 2023/05/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 50
#define FALSE 0
#define TRUE 1

struct Vertex {
    int n;
    bool visited;
};

//stack
int stack[MAX];
int top = -1;

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


// 공백함수
int is_empty() {
    return top == -1;
}

// 정점 삽입함수
void insert_vertex(char item) {
    struct Vertex *v = (struct Vertex *) malloc(sizeof(struct Vertex));
    v->n = item;
    v->visited = false;
    arr[count++] = v;
}

// 간선 삽입함수
void insert_edge(int start, int end) {
    adj_mat[start][end] = 1;
    adj_mat[end][start] = 1;
}

// 계속 출력되는 함수 설정
void display_vertex(int index) {
    printf("정점 % c ->", arr[index]->n);
}

// v가 방문되었는지 안되었는지 확인하는 함수
int get_vertex(int index) {
    int v;

    for (v = 0; v < count; v++) {
        if (adj_mat[index][v] == 1 && arr[v]->visited == false) {
            return v;
        }
    }

    return -1;
}

void dfs_iterate() {
    int i;

    // 방문했으면 TRUE
    arr[0]->visited = TRUE;

    display_vertex(0);

    // 스택에 0삽입
    push(0);

    // 만약 스택이 비어있다면...
    while (!is_empty()) {
        // vertex가 방문하지 않았다면 peek함수로 stack의 top 보기
        int unvisited_vertex = get_vertex(peek());

        if (unvisited_vertex == -1) {
            pop();
        } else {
            arr[unvisited_vertex]->visited = true;
            display_vertex(unvisited_vertex);
            push(unvisited_vertex);
        }
    }

    // 스택이 비어있고, 탐색이 끝나면 처음으로 다시 돌아가기
    for (i = 0; i < count; i++) {
        arr[i]->visited = false;
    }
}

int main() {
    int i, j;
    struct Vertex *v;

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

    printf("깊이 우선 탐색\n");
    dfs_iterate();

    return 0;
}