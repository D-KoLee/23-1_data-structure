//
// Created by SeungJun Ryu on 2023/04/17.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef double element;

typedef struct {
    element data;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
} StackType;

// 스택 초기화 함수
void init_stack(StackType *s) {
    s->top = NULL;
}

// 포화 상태 검출 함수
int isFull(StackType *s) {
    return 0;
}

// 공백 상태 검출 함수
int isEmpty(StackType *s) {
    return (s->top == NULL);
}

// 삽입함수
void push(StackType *s, element item) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    new_node->data = item;
    new_node->next = s->top;
    s->top = new_node;
}

// 삭제함수
element pop(StackType *s) {
    if (isEmpty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    } else {
        Node *temp = s->top;
        element data = temp->data;
        s->top = s->top->next;
        free(temp);
        return data;
    }
}

// 읽기함수
element peek(StackType *s) {
    if (isEmpty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    } else
        return s->top->data;
}

// 연산자의 우선순위를 반환한다.
int prec(char op) {
    switch (op) {
        case '(':
        case ')':
            return 0;
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
    }
    return -1;
}

// 식에 문자열이 들어가 있거나 괄호의 갯수가 맞는지 검사하는 함수
int checking(char s[]) {
    int s_len = strlen(s);
    int cnt_left = 0;
    int cnt_right = 0;

    //처음에 +,-가 있을 경우 부호이므로 예외처리
    if (s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/') {
        fprintf(stderr, "식에 부호가 포함되어 있거나 연산자가 올바르지 않게 입력되었습니다.");
        return 1;
    }
    //마지막에 +,-가 있을 경우 식이 잘못된 것이므로 예외처리
    if (s[s_len - 1] == '+' || s[s_len - 1] == '-' || s[s_len - 1] == '*' || s[s_len - 1] == '/') {
        fprintf(stderr, "식에 부호가 포함되어 있거나 연산자가 올바르지 않게 입력되었습니다.");
        return 1;
    }

    for (int i = 0; i < s_len; i++) {
        if (isalpha(s[i]) != 0) { //isalpha를 통해 s[i]의 문자가 알파벳인지 확인
            fprintf(stderr, "식에 문자열이 들어가 있습니다.");
            return 1;
        }
        if (s[i] == '(')// 왼쪽 괄호를 만날때 cnt_left 1증가
            cnt_left += 1;
        if (s[i] == ')')// 오른쪽 괄호를 만날때 cnt_right 1증가
            cnt_right += 1;
        //s[i]가 연산자일 경우 다음에 오는 +,-는 부호이거나 식이 잘못된 것이므로 예외처리
        if (i + 1 < s_len && (s[i] == '+' || s[i] == '-' || s[i] == '/' || s[i] == '*') &&
            (s[i + 1] == '+' || s[i + 1] == '-' || s[i + 1] == '/' || s[i + 1] == '*')) {
            fprintf(stderr, "식에 부호가 포함되어 있거나 연산자가 올바르지 않게 입력되었습니다.");
            return 1;
        }

    }
    if (cnt_left != cnt_right) { // cnt_left != cnt_right이 참이면 괄호의 짝이 맞지 않는다.
        fprintf(stderr, "괄호가 맞지 않습니다.");
        return 1;
    }


    return 0;
}

// 중위 표기 수식 -> 후위 표기 수식 그리고 후위식을 postfix의 주소를 받아 postfix에 저장한다.
void infix_to_postfix(char exp[], char postfix[]) {
    int i = 0;
    int j = 0;
    char ch;
    int len = strlen(exp);

    StackType s;
    init_stack(&s); // 스택 초기화

    for (i = 0; i < len; i++) {
        ch = exp[i];

        switch (ch) {
            case '+':
            case '-':
            case '*':
            case '/': // 연산자
                // 스택에 있는 연산자의 우선순위가 더 크거나 같으면 출력
                while (!isEmpty(&s) && (prec(ch) <= prec(peek(&s)))) {
                    postfix[j++] = pop(&s);
                    postfix[j++] = ' ';
                }
                push(&s, ch);
                break;
            case '(': // 왼쪽 괄호
                push(&s, ch);
                break;
            case ')': // 오른쪽 괄호
                while (peek(&s) != '(') {
                    postfix[j++] = pop(&s);
                    postfix[j++] = ' ';
                }
                pop(&s); // '(' pop함수로 빼기
                break;
            case '.': // 소수점 처리
                postfix[j++] = ch;
                break;
            default: // 피연산자, 현재 위치는 i이므로 i번째 다음 기호가 '.'이면 공백을 출력하지 않는다.
                postfix[j++] = ch;
                if (i + 1 < len && ((exp[i + 1] >= '0' && exp[i + 1] <= '9') || exp[i + 1] == '.')) {
                    break;
                }
                postfix[j++] = (' ');
                break;
        }
    }
    while (!isEmpty(&s)) {// 스택에 저장된 연산자들 출력
        postfix[j++] = pop(&s);
        postfix[j++] = ' ';
    }
}

// 중위 표기 수식 -> 전위 표기 수식
void infix_to_prefix(char exp[]) {
    int i, j = 0;
    char ch;
    int len = strlen(exp);
    StackType s;
    char prefix[100] = {""}; //전위 표기 수식을 저장할 문자열 선언
    init_stack(&s); // 스택 초기화


    //역순으로 검사
    for (i = len - 1; i >= 0; i--) {
        ch = exp[i];

        switch (ch) {
            case '+':
            case '-':
            case '*':
            case '/': // 연산자
                // 스택에 있는 연산자의 우선순위가 더 크거나 같으면 prefix에 저장
                while (!isEmpty(&s) && (prec(ch) < prec(peek(&s)))) {
                    prefix[j++] = pop(&s);
                    prefix[j++] = ' ';
                }
                push(&s, ch);
                break;
            case '(': // 왼쪽 괄호, 역순으로 검사하기 때문에
                while (peek(&s) != ')') {
                    prefix[j++] = pop(&s);
                    prefix[j++] = ' ';
                }
                pop(&s); // '(' pop함수로 빼기
                break;
            case ')': // 오른쪽 괄호
                push(&s, ch);
                break;
            case '.': // 소수점 처리
                prefix[j++] = ch;
                break;
            default: // 피연산자
                prefix[j++] = ch;
                if (i - 1 >= 0 && ((exp[i - 1] >= '0' && exp[i - 1] <= '9') || exp[i - 1] == '.')) {
                    break;
                }
                prefix[j++] = ' ';
                break;
        }
    }
    while (!isEmpty(&s)) { // 스택에 저장된 연산자들을 prefix에 push
        prefix[j++] = pop(&s);
        if (!isEmpty(&s))
            prefix[j++] = ' ';
    }

    // prefix 배열에 들어가있는 문자를 역순으로 출력
    for (i = j - 1; i >= 0; i--) {
        printf("%c", prefix[i]);
    }
}

//후위표기수식 계산하는 함수
double eval_postfix(char *exp) {
    int i = 0;
    char ch;
    double num;
    double op1, op2; //후위식의 피연산자 저장할 실수형 변수
    int len = strlen(exp);
    StackType s;
    init_stack(&s); // 스택 초기화

    for (i = 0; i < len; i++) {
        ch = exp[i];
        if (isdigit(ch) || ch == '.') { // 피연산자일 경우
            num = atof(&exp[i]); // atof 함수를 이용해 실수형으로 변환하여 num에 저장
            push(&s, num);
            // i를 다음 연산자 까지 이동시킨다.
            while (isdigit(exp[i]) || exp[i] == '.')
                i++;
        }
            //연산자일 경우
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') { // 연산자
            op2 = pop(&s);
            op1 = pop(&s);
            //연산자에 맞게 연산
            switch (ch) {
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
    //마지막은 항상 계산결과이므로 pop함수로 꺼내어 return
    return pop(&s);
}

int main(void) {
    char s[100] = {""};
    char postfix[100] = {""};
    printf("중위식을 입력하세요 : ");
    scanf("%s", &s);

    if (checking(s) == 1)
        exit(1);

    printf("전위식 : ");
    infix_to_prefix(s);
    printf("\n");

    printf("후위식 : ");
    infix_to_postfix(s, postfix);
    printf("%s", postfix);
    printf("\n");

    printf("계산결과 : %g", eval_postfix(&postfix));
    return 0;
}