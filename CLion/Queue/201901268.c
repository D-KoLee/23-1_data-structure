//
// Created by SeungJun Ryu on 2023/04/24.
//
#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct { // 큐 타입
    element *data;
    int front, rear, count, size;
} QueueType;

// 오류 함수
void error(char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 초기화 함수
void init(QueueType *q) {
    q->front = q->rear = 0;
    q->count = 0;
    q->size = 5;
    q->data = (element *) malloc(sizeof(element) * q->size);
}

// 공백 상태 검출 함수
int is_empty(QueueType *q) {
    return (q->count == 0);
}

// 포화 상태 검출 함수
int is_full(QueueType *q) {
    return (q->count == q->size-1);
}

// 크기 변환
void resize(QueueType *q) {
    printf("Resize: %d -> %d\n", q->size, q->size * 2);
    q->size = q->size * 2;
    q->data = (element *) realloc(q->data, sizeof(element) * q->size);
}

// 출력 함수
void queue_print(QueueType *q) {
    printf("QUEUE(front=%d rear=%d count=%d) = ", q->front, q->rear, q->count);
    if (!is_empty(q)) {
        int i = q->front;
        do {
            i = (i + 1) % (q->size);
            printf("%d | ", q->data[i]);
            if (i == q->rear)
                break;
        } while (i != q->front);
    }
    printf("\n");
}

// 삽입 함수
void enqueue(QueueType *q, element data) {
    if (is_full(q))
        resize(q);
    q->rear = (q->rear + 1) % q->size;
    q->data[q->rear] = data;
    q->count++;
}

// 삭제 함수
element dequeue(QueueType *q) {
    if (is_empty(q)) {
        error("큐가 비어있음");
    }
    q->front = (q->front + 1) % q->size;
    q->count--;
    return q->data[q->front];
}

// 피크 함수
element peek(QueueType *q) {
    if (is_empty(q)) {
        error("큐가 비어있음");
    }
    return q->data[(q->front + 1) % q->size];
}

int main(void) {
    QueueType q;
    init(&q);

    printf("==Add 100 elements==\n");
    for (int i = 0; i < 100; i++) {
        enqueue(&q, i + 1);
        queue_print(&q);
    }
    printf("==Remove 100 elements==\n");
    while (!is_empty(&q)) {
        dequeue(&q);
        queue_print(&q);
    }
    printf("Queue is empty\n");
    return 0;
}