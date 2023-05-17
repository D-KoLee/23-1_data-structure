//
// Created by SeungJun Ryu on 2023/05/17.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct element {
    int key;
    struct element *left;
    struct element *right;
} element;

typedef struct HeapType {
    element *heap;
    int heap_size;
} HeapType;

// 생성 함수
HeapType *create_heap() {
    return (HeapType *) malloc(sizeof(HeapType));
}

// 초기화 함수
void init_heap(HeapType *h) {
    h->heap = NULL;
    h->heap_size = 0;
}

// 부모 노드를 찾는 함수
void find_pre_node(element *root, int index, element *new_node) {
    int temp[10] = {0};
    int cnt = 0;
    element *node = root;
    for (int k = 0; index > 1; k++) {
        temp[cnt++] = index % 2;
        index /= 2;
    }

    cnt -= 1;
    while (cnt >= 1) {
        if (temp[cnt] == 0)
            node = node->left;
        else if (temp[cnt] == 1)
            node = node->right;
        cnt--;
    }
    if (temp[cnt] == 0)
        node->left = new_node;
    else if (temp[cnt] == 1)
        node->right = new_node;
}

// 노드의 위치를 찾는 함수
element *find_node(element *root, int index) {
    int temp[10] = {0}; // 2진수를 저장할 크기 10인 배열
    int cnt = 0;
    element *node = root;
    // index를 2진수로 배열에 저장
    for (int k = 0; index > 1; k++) {
        temp[cnt++] = index % 2;
        index /= 2;
    }
    //2진수를 읽으면서 0이면 left 1이면 right로 이동 cnt < 0 이면 node 반환
    cnt -= 1;
    while (cnt >= 0) {
        if (temp[cnt] == 0)
            node = node->left;
        else if (temp[cnt] == 1)
            node = node->right;
        cnt--;
    }
    return node;
}


element *new_element(HeapType *h, int key, int index) {
    element *temp_node = (element *) malloc(sizeof(element));
    temp_node->key = key;
    temp_node->left = temp_node->right = NULL;

    if (h->heap == NULL) {
        h->heap = temp_node;
        return h->heap;
    }

    find_pre_node(h->heap, index, temp_node);
    return temp_node;
}

int is_empty(HeapType *h) {
    return (h->heap_size == 0);
}

// 현재 요소의 개수가 heap_size인 히프 h에 item을 삽입한다.
// 삽입 함수
void insert_min_heap(HeapType *h, int item) {
    int i;
    i = ++(h->heap_size);
    new_element(h, item, h->heap_size); //새로운 노드 만들기

    // 트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
    while ((i != 1) && (item < find_node(h->heap, i / 2)->key)) {
        find_node(h->heap, i)->key = find_node(h->heap, i / 2)->key;
        i /= 2;
    }
    find_node(h->heap, i)->key = item;  // 새로운 노드를 삽입
}

int find(HeapType *h) {
    return h->heap->key;
}

// 삭제 함수
int delete_min_heap(HeapType *h) {
    int parent, child;
    int item, temp;
    item = find(h);
    temp = find_node(h->heap, (h->heap_size--))->key;
    parent = 1;
    child = 2;
    while (child <= h->heap_size) {
        // 현재 노드의 자식노드 중 더 작은 자식노드를 찾는다.
        if ((child < h->heap_size) &&
            (find_node(h->heap, child)->key) > find_node(h->heap, child + 1)->key)
            child++;
        if (temp <= find_node(h->heap, child)->key)
            break;
        // 한 단계 아래로 이동
        find_node(h->heap, parent)->key = find_node(h->heap, child)->key;
        parent = child;
        child *= 2;
    }
    find_node(h->heap, parent)->key = temp;
    return item;
}


int main(void) {
    int e1 = 30, e2 = 50, e3 = 10, e4 = 20, e5 = 5;
    int e6, e7, e8, e9, e10;
    HeapType *heap;
    heap = create_heap(); // 히프 생성
    init_heap(heap);      // 초기화

    // 삽입
    insert_min_heap(heap, e1);
    insert_min_heap(heap, e2);
    insert_min_heap(heap, e3);
    insert_min_heap(heap, e4);
    insert_min_heap(heap, e5);

    for (int i = 1; i < 6; i++) {
        printf("%d\n", find_node(heap->heap, i)->key);
    }
    //삭제
    e6 = delete_min_heap(heap);
    printf("<%d>\n", e6);
    e7 = delete_min_heap(heap);
    printf("<%d>\n", e7);
    e8 = delete_min_heap(heap);
    printf("<%d>\n", e8);
    e9 = delete_min_heap(heap);
    printf("<%d>\n", e9);
    e10 = delete_min_heap(heap);
    printf("<%d>\n", e10);
    free(heap);
    return 0;
}