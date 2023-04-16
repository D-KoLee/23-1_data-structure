//
// Created by SeungJun Ryu on 2023/04/16.
//
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct StackNode {
    char data;
    struct StackNode *next;
} StackNode;

typedef struct Stack {
    StackNode *top;
} Stack;

void push(Stack *stack, char data) {
    StackNode *node = (StackNode *) malloc(sizeof(StackNode));
    node->data = data;
    node->next = stack->top;
    stack->top = node;
}

char pop(Stack *stack) {
    if (stack->top == NULL) {
        return '\0';
    }
    StackNode *node = stack->top;
    stack->top = stack->top->next;
    char data = node->data;
    free(node);
    return data;
}

int isEmpty(Stack *stack) {
    return stack->top == NULL;
}

char peek(Stack *stack) {
    if (stack->top == NULL) {
        return '\0';
    }
    return stack->top->data;
}

int isOperand(char c) {
    return isdigit(c) || isalpha(c);
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int getPrecedence(char c) {
    if (c == '*' || c == '/') {
        return 2;
    } else if (c == '+' || c == '-') {
        return 1;
    } else {
        return 0;
    }
}

int isPrefix(char *expression) {
    int i = 0;
    int operandCount = 0, operatorCount = 0;

    while (expression[i] != '\0') {
        if (isOperator(expression[i])) {
            operatorCount++;
        } else if (isOperand(expression[i])) {
            operandCount++;
        }

        if (operatorCount >= 1 && operandCount >= 2) {
            return 0;
        }

        i++;
    }

    if (operatorCount == operandCount - 1) {
        return 1;
    } else {
        return 0;
    }
}

int isPostfix(char *expression) {
    int i = 0;
    int operandCount = 0, operatorCount = 0;

    while (expression[i] != '\0') {
        if (isOperator(expression[i])) {
            operatorCount++;
        } else if (isOperand(expression[i])) {
            operandCount++;
        }

        if (operandCount >= 2 && operatorCount == 0) {
            return 0;
        }

        i++;
    }

    if (operandCount == operatorCount + 1) {
        return 1;
    } else {
        return 0;
    }
}

int isInfix(char *expression) {
    int len = strlen(expression);
    int operatorCount = 0;
    int operandCount = 0;
    for (int i = 0; i < len; i++) {
        char ch = expression[i];
        if (isspace(ch)) {
            continue;
        } else if (isdigit(ch) || isalpha(ch)) {
            operandCount++;
        } else if (isOperator(ch)) {
            operatorCount++;
            if (i == 0 && (ch == ')' || ch == '*' || ch == '/')) {
                return 0;
            } else if (i == len - 1 && (ch == '(' || isOperator(expression[i - 1]))) {
                return 0;
            } else if (i > 0 && i < len - 1 && ch == '(' && isalnum(expression[i - 1])) {
                return 0;
            } else if (i > 0 && i < len - 1 && ch == ')' && isOperator(expression[i - 1])) {
                return 0;
            } else if (i > 0 && i < len - 1 && isOperator(ch) && isOperator(expression[i - 1]) && ch != '(' &&
                       ch != ')') {
                return 0;
            }
        } else {
            return 0;
        }
    }
    if (operatorCount == 0 || operandCount == 0 || operatorCount >= operandCount) {
        return 0;
    }
    return 1;
}

int main() {
    char expression[100];
    printf("수식을 입력하세요: ");
    scanf("%s", expression);

    if (isPrefix(expression))
        printf("입력된 수식은 전위 표기법입니다.");
    else if (isInfix(expression))
        printf("입력된 수식은 중위 표기법입니다.");
    else if (isPostfix(expression))
        printf("입력된 수식은 후위 표기법입니다.");
    else
        printf("잘못된 입력입니다.");

    return 0;
}
