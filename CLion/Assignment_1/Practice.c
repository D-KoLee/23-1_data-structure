//
// Created by SeungJun Ryu on 2023/04/15.
//
#include <stdio.h> // printf, scanf, puts
#include <stdlib.h> // malloc, free
#include <string.h> // strlen
#include <ctype.h> // isdigit, isalpha

#define MAX_LEN 100    // 중위 표기식의 최대 길이

// 스택을 구현하는 구조체
typedef double element; // 스택에 저장할 데이터의 타입

typedef struct {
    element data;
    struct StackNode *link;
} StackNode;

void is_infix_fine(char exp[]);
void is_postfix_fine(char exp[]);
void is_prefix_fine(char exp[]);
void infix_to_postfix(char exp[], char postfix[]);
void infix_to_prefix(char exp[]);
void prefix_to_infix(char exp[]);
void prefix_to_postfix(char exp[], char postfix[]);
void postfix_to_infix(char exp[]);
void postfix_to_prefix(char exp[]);
double eval_postfix(char *exp);

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
    if (temp == NULL) {
        fprintf(stderr, "메모리 할당 에러\n");
        return;
    }
    temp->data = item;
    temp->link = s->top;
    s->top = temp;
}

//void print_stack(LinkedStackType *s) {
//    for (StackNode *p = s->top; p != NULL; p = p->link)
//        printf("%d->", p->data);
//    printf("NULL \n");
//}

// 삭제 함수
element pop(LinkedStackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택이 비어있음\n");
        exit(1);
    } else {
        StackNode *temp = s->top;
        element data = temp->data;
        s->top = s->top->link;
        free(temp);
        return data;
    }
}

//스택의 top에 있는 원소를 반환하는 함수
element peek(LinkedStackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택이 비어있음\n");
        exit(1);
    } else {
        return s->top->data;
    }
}

//연산자 우선순위를 반환하는 함수
int prec(char op) {
    switch (op) {
        case '(':
        case ')':
            return 0; //괄호는 무조건 제일 낮은 우선순위로 취급
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
    }
    return -1;
}

void is_infix_fine(char exp[]) { //중위 표현식이 올바른지 검사하는 함수
    int len = strlen(exp);
    int bracket = 0;

    if (exp[0] == '+' || exp[0] == '*' || exp[0] == '/' || exp[0] == ')') {
        printf("잘못된 중위 표현식입니다.\n부호가 포함되어 있습니다.");
        exit(1);
    }//처음에 부호가 나오면 오류
    if (exp[len - 1] == '+' || exp[len - 1] == '*' || exp[len - 1] == '/' || exp[len - 1] == '(') {
        printf("잘못된 중위 표현식입니다.\n부호가 포함되어 있습니다.");
        exit(1);
    }//마지막에 부호가 나오면 오류

    for (int i = 0; i < len; i++) {
        if (exp[i] == '(' && exp[i + 1] == ')') {
            printf("잘못된 중위 표현식입니다.\n괄호가 비어있습니다.");
            exit(1);
        }//괄호가 비어있으면 오류
        if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/')
            if (exp[i + 1] == '+' || exp[i + 1] == '-' || exp[i + 1] == '*' || exp[i + 1] == '/') {
                printf("잘못된 중위 표현식입니다.\n부호가 연속으로 나옵니다.");
                exit(1);
            }//연산자가 연속으로 나오면 오류

        if (isalpha(exp[i]) != 0) {
            fprintf(stderr, "잘못된 중위 표현식입니다.\n영문자가 포함되어 있습니다.");
            exit(1);
        } //영문자가 나오면 오류

        if (exp[i] == '(')
            bracket++; //왼쪽 괄호가 나오면 bracket++
        else if (exp[i] == ')')
            bracket--; //오른쪽 괄호가 나오면 bracket--
    }
    if (bracket != 0) { //괄호 갯수가 같다면 0이어야 함
        printf("잘못된 중위 표현식입니다.\n괄호의 짝이 맞지 않습니다.");
        exit(1);
    }
}

//후위표기법으로 변환하는 함수
void infix_to_postfix(char exp[], char postfix[]) {
    int i, j = 0;
    //char ch;
    int len = strlen(exp);

    LinkedStackType s;
    init(&s);

    for (i = 0; i < len; i++) {
        //ch = exp[i];
        switch (exp[i]) {
            case '+':
            case '-':
            case '*':
            case '/':
                while (!is_empty(&s) && (prec(exp[i]) <= prec(peek(&s)))) {
                    //스택에 있는 연산자의 우선순위가 더 높거나 같으면 pop
                    postfix[j++] = pop(&s);
                    postfix[j++] = ' ';
                }
                push(&s, exp[i]);
                break;
            case '(': //왼쪽 괄호는 무조건 스택에 push
                push(&s, exp[i]);
                break;
            case ')': //오른쪽 괄호는 왼쪽 괄호가 나올 때까지 pop
                while (peek(&s) != '(') {
                    postfix[j++] = pop(&s);
                    postfix[j++] = ' ';
                }
                pop(&s); //왼쪽 괄호 pop(제거
                break;
            case '.': //소숫점은 그냥 출력
                postfix[j++] = exp[i];
                break;
            default: //피연산자는 출력
                postfix[j++] = exp[i];
                if (!isdigit(exp[i + 1]) && exp[i + 1] != '.') //피연산자 뒤에 숫자가 아닌 문자가 오면 공백 추가
                    postfix[j++] = ' ';
                break;
        }
    }
    while (!is_empty(&s)) {  //스택에 남아있는 모든 연산자 pop
        postfix[j++] = pop(&s);
        postfix[j++] = ' ';
    }
    postfix[j] = '\0'; //문자열 끝에 NULL 추가
}

//후위표기법을 계산하는 함수
double eval_postfix(char *exp) {
    double op1, op2, value;
    int len = strlen(exp);

    LinkedStackType s;
    init(&s);

    for (int i = 0; i < len; i++) {
        if (isdigit(exp[i]) || exp[i] == '.') { //피연산자는 스택에 push
            value = atof(&exp[i]); //문자열을 실수로 변환
            push(&s, value); //스택에 push
            while (isdigit(exp[i]) || exp[i] == '.') //연산자가 나올 때까지 인덱스 증가
                i++;
        } else if (exp[i] == ' ') //공백은 무시
            continue;
        else { //연산자는 스택에서 pop
            op2 = pop(&s);
            op1 = pop(&s);
            switch (exp[i]) {
                case '+':
                    push(&s, op1 + op2);
                    break;
                case '-':
                    push(&s, op1 - op2);
                    break;
                case '*':
                    push(&s, op1 * op2);
                    break;
                case '/':
                    push(&s, op1 / op2);
                    break;
            }
        }
    }
    return pop(&s);
}

//전위표기법으로 변환하는 함수
void infix_to_prefix(char exp[]) {
    int i, j = 0;
    int len = strlen(exp);

    char prefix[MAX_LEN] = {""};
    LinkedStackType s;
    init(&s);

    for (i = len - 1; i >= 0; i--) {
        switch (exp[i]) {
            case '+':
            case '-':
            case '*':
            case '/':
                while (!is_empty(&s) && (prec(exp[i]) < prec(peek(&s)))) {
                    //스택에 있는 연산자의 우선순위가 더 높거나 같으면 pop
                    prefix[j++] = pop(&s);
                    prefix[j++] = ' ';
                }
                push(&s, exp[i]);
                break;
            case ')': //오른쪽 괄호는 왼쪽 괄호가 나올 때까지 pop
                push(&s, exp[i]);
                break;
            case '(': //후위와 달리 역순이기 때문에 좌우 괄호 역할이 반대
                while (peek(&s) != ')') {
                    prefix[j++] = pop(&s);
                    prefix[j++] = ' ';
                }
                pop(&s);
                break;
            case '.': //소숫점은 그냥 출력
                prefix[j++] = exp[i];
                break;
            default: //피연산자는 출력
                prefix[j++] = exp[i];
                if (!isdigit(exp[i - 1]) && exp[i - 1] == '.') //'.' 뒤에는 공백 없어야함
                    break;
                prefix[j++] = ' ';
                break;
        }
    }
    while (!is_empty(&s)) {  //스택에 남아있는 모든 연산자 pop
        prefix[j++] = pop(&s);
        prefix[j++] = ' ';
    }
    prefix[--j] = '\0';

    for (i = strlen(prefix) - 1; i >= 0; i--) //역순으로 출력
        printf("%c", prefix[i]);
}

// 주 함수
int main(void) {
    int which_one;
    printf("입력할 수식은 무엇입니까?\n1. 중위식\n2. 전위식\n3. 후위식\n");
    scanf("%d", &which_one);
    getchar();

    char infix[MAX_LEN] = {""};
    char postfix[MAX_LEN] = {""};
    char prefix[MAX_LEN] = {""};

    switch (which_one) {
        case 1:
            printf("중위식을 입력하세요 : ");
            fgets(infix, MAX_LEN, stdin);
            infix[strcspn(infix, "\n")] = '\0';    // fgets로 입력받은 문자열 마지막 개행 문자 제거
            is_infix_fine(infix);

            printf("전위식 : ");
            infix_to_prefix(infix);
            printf("\n");

            printf("후위식 : ");
            infix_to_postfix(infix, postfix);
            printf("%s", postfix);
            printf("\n");

            printf("계산결과 : %g\n", eval_postfix(&postfix));
            break;
        case 2:

    }


    return 0;
}

