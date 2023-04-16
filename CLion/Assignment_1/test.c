//
// Created by SeungJun Ryu on 2023/04/15.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EXPR_LEN 100    // 중위 표기식의 최대 길이
#define MAX_OPND_STACK_SIZE 100    // 피연산자 스택의 최대 크기

// 스택을 구현하는 구조체
typedef struct {
    int top;    // 스택의 top
    int data[MAX_OPND_STACK_SIZE];    // 스택의 data
} OpndStack;

// 스택 초기화 함수
void initStack(OpndStack *stack) {
    stack->top = -1;
}

// 스택이 비어있는지 확인하는 함수
int isStackEmpty(OpndStack *stack) {
    return stack->top == -1;
}

// 스택이 가득 찼는지 확인하는 함수
int isStackFull(OpndStack *stack) {
    return stack->top == MAX_OPND_STACK_SIZE - 1;
}

// 스택에 push하는 함수
void push(OpndStack *stack, int item) {
    if (isStackFull(stack)) {
        printf("Error: Stack is full.\n");
        exit(EXIT_FAILURE);
    }
    stack->data[++stack->top] = item;
}

// 스택에서 pop하는 함수
int pop(OpndStack *stack) {
    if (isStackEmpty(stack)) {
        printf("Error: Stack is empty.\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top--];
}

// 스택에서 top의 값을 가져오는 함수
int peek(OpndStack *stack) {
    if (isStackEmpty(stack)) {
        printf("Error: Stack is empty.\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top];
}

// 연산자 우선순위를 반환하는 함수
int getPrecedence(char op) {
    switch (op) {
        case '(': case ')': return 0;
        case '+': case '-': return 1;
        case '*': case '/': return 2;
    }
    return -1;
}

// 중위 표기식을 후위 표기식으로 변환하는 함수
void infixToPostfix(char *infix, char *postfix) {
    OpndStack stack;
    initStack(&stack);    // 스택 초기화
    int len = strlen(infix);
    int postfixIdx = 0;

    for (int i = 0; i < len; i++) {
        char ch = infix[i];
        // 숫자인 경우
        if (isdigit(ch) || ch == '.') {
            postfix[postfixIdx++] = ch;
        }
            // 연산자인 경우
        else if (strchr("+-*/", ch) != NULL) {
            while (!isStackEmpty(&stack) && getPrecedence(ch) <= getPrecedence(peek(&stack))) {
                postfix[postfixIdx++] = pop(&stack);
            }
            push(&stack, ch);
        }
            // 왼쪽 괄호인 경우
        else if (ch == '(') {
            push(&stack, ch);
        }
            // 오른쪽 괄호인 경우
        else if (ch == ')') {
            while (!isStackEmpty(&stack) && peek(&stack) != '(') {
                postfix[postfixIdx++] = pop(&stack);
            }
            if (isStackEmpty(&stack) || pop(&stack) != '(') {
                printf("Error: Invalid infix expression.\n");
                exit(EXIT_FAILURE);
            }
        }
            // 잘못된 중위 표기식인 경우
        else {
            printf("Error: Invalid infix expression.\n");
            exit(EXIT_FAILURE);
        }
    }
    // 스택에 남아있는 연산자들을 모두 pop
    while (!isStackEmpty(&stack)) {
        char op = pop(&stack);
        if (op == '(') {
            printf("Error: Invalid infix expression.\n");
            exit(EXIT_FAILURE);
        }
        postfix[postfixIdx++] = op;
    }
    postfix[postfixIdx] = '\0';    // 후위 표기식 마지막에 NULL 문자 추가
}

int main() {
    char infix[MAX_EXPR_LEN];
    char postfix[MAX_EXPR_LEN];
    printf("Enter infix expression: ");
    fgets(infix, MAX_EXPR_LEN, stdin);
    infix[strcspn(infix, "\n")] = '\0';    // fgets로 입력받은 문자열 마지막 개행 문자 제거
    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);
    return 0;
}
