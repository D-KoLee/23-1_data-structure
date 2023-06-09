//
// Created by SeungJun Ryu on 2023/03/29.
//
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAZE_SIZE 6

typedef struct {
    short r;
    short c;
} element;

element here = {1, 0}, entry = {1, 0};

char maze[MAZE_SIZE][MAZE_SIZE] = {
        {'1', '1', '1', '1', '1', '1'},
        {'e', '0', '0', '0', '1', '1'},
        {'1', '1', '0', '1', '1', '1'},
        {'1', '1', '0', '1', '1', '1'},
        {'1', '0', '0', '0', '0', 'x'},
        {'1', '1', '1', '1', '1', '1'},
};

typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;

void init_stack(StackType *s) {
    s->top = -1;
}

int is_empty(StackType *s) {
    return (s->top == -1);
}

int is_full(StackType *s) {
    return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType *s, element item) {
    if (is_full(s)) {
        fprintf(stderr, "스택 포화 에러\n");
        return;
    } else s->data[++(s->top)] = item;
}

element pop(StackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    } else return s->data[(s->top)--];
}

void print_stack(StackType *s) {
    printf("Stack: ");
    if(s->top == -1) {
        printf("empty\n");
        return;
    }
    for (int i = s->top; i >= 0; i--) {
        printf("(%d, %d) ", s->data[i].r, s->data[i].c);
    }
    printf("\n");
}

void push_loc(StackType *s, int r, int c) {
    if (r < 0 || c < 0) return;
    if (maze[r][c] != '1' && maze[r][c] != '.') {
        element tmp;
        tmp.r = r;
        tmp.c = c;
        push(s, tmp);
    }
}

void maze_print(char maze[MAZE_SIZE][MAZE_SIZE]) {
    printf("\n");
    for (int r = 0; r < MAZE_SIZE; r++) {
        for (int c = 0; c < MAZE_SIZE; c++) {
            printf("%c", maze[r][c]);
        }
        printf("\n");
    }
}

int main(void) {
    int r, c;
    StackType s;
    init_stack(&s);
    here = entry;
    while (maze[here.r][here.c] != 'x') {
        r = here.r;
        c = here.c;
        maze[r][c] = '.';
        maze_print(maze);
        push_loc(&s, r - 1, c);
        push_loc(&s, r + 1, c);
        push_loc(&s, r, c - 1);
        push_loc(&s, r, c + 1);
        printf("이동 전 ");
        print_stack(&s);
        if (is_empty(&s)) {
            printf("실패\n");
            return 0;
        } else
            here = pop(&s);
        printf("이동 후 ");
        print_stack(&s);
    }
    printf("성공\n");
    return 0;
}