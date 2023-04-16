//
// Created by SeungJun Ryu on 2023/04/16.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK_SIZE 100

typedef struct StackNode {
    char data;
    struct StackNode *next;
} StackNode;

typedef struct {
    StackNode *top;
} Stack;

void push(Stack *stack, char data) {
    StackNode *new_node = (StackNode *) malloc(sizeof(StackNode));
    if (!new_node) {
        printf("메모리 할당 에러\n");
        return;
    }
    new_node->data = data;
    new_node->next = stack->top;
    stack->top = new_node;
}

char pop(Stack *stack) {
    if (stack->top == NULL) {
        printf("스택이 비어있습니다.\n");
        return '\0';
    }
    char data = stack->top->data;
    StackNode *temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    return data;
}

char peek(Stack *stack) {
    if (stack->top == NULL) {
        printf("스택이 비어있습니다.\n");
        return '\0';
    }
    return stack->top->data;
}

int is_empty(Stack *stack) {
    return stack->top == NULL;
}

int is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int precedence(char c) {
    if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return 0;
}

void postfixToInfix(char *postfix, char *infix) {
    Stack stack = { .top = NULL };
    char token, op1, op2;
    int i = 0;

    while ((token = postfix[i++]) != '\0') {
        if (isdigit(token) || isalpha(token)) {
            push(&stack, token);
        } else if (is_operator(token)) {
            op2 = pop(&stack);
            op1 = pop(&stack);
            char temp[100];
            sprintf(temp, "(%c %c %c)", op1, token, op2);
            push(&stack, temp[0]);
        } else {
            printf("잘못된 입력입니다.\n");
            return;
        }
    }

    if (!is_empty(&stack)) {
        printf("잘못된 입력입니다.\n");
        exit(1);
    }

    strcpy(infix, &op1);
}

int main() {
    char postfix[100];
    char infix[100];
    printf("후위 표기식 입력: ");
    scanf("%s", postfix);
    postfixToInfix(postfix, infix);
    printf("중위 표기식: %s\n", infix);
    return 0;
}
