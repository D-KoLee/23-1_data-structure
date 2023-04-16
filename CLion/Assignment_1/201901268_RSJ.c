//
// Created by SeungJun Ryu on 2023/04/15.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 스택을 구현하는 구조체
typedef int element;
typedef struct StackNode {
    element data;
    struct StackNode *link;
} StackNode;

// 링크드리스트로 스택을 구현하기 위한 구조체
typedef struct {
    StackNode *top;
} LinkedStackType;

// 초기화 함수
void init(LinkedStackType *s) {
    s->top = NULL;
}

//공백 상태 검출 함수
int is_empty(LinkedStackType *s) {
    return (s->top == NULL);
}

//포화 상태 검출 함수
int is_full(LinkedStackType *s) {
    return 0;
}

// 삽입 함수
void push(LinkedStackType *s, element item) {
    StackNode *temp = (StackNode *) malloc(sizeof(StackNode));
    temp->data = item;
    temp->link = s->top;
    s->top = temp;
}

void print_stack(LinkedStackType *s) {
    for (StackNode *p = s->top; p != NULL; p = p->link)
        printf("%d->", p->data);
    printf("NULL \n");
}

// 삭제 함수
element pop(LinkedStackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택이 비어있음\n");
        exit(1);
    } else {
        StackNode *temp = s->top;
        int data = temp->data;
        s->top = s->top->link;
        free(temp);
        return data;
    }
}

// 주 함수
int main(void) {
    LinkedStackType s;
    init(&s);
    push(&s, 1);
    print_stack(&s);
    push(&s, 2);
    print_stack(&s);
    push(&s, 3);
    print_stack(&s);
    pop(&s);
    print_stack(&s);
    pop(&s);
    print_stack(&s);
    pop(&s);
    print_stack(&s);
    return 0;
}

