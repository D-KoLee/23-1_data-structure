//
// Created by SeungJun Ryu on 2023/05/15.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    struct element *left;
    struct element *right;
} element;

typedef struct {
    element *heap;
    int heap_size;
} HeapType;

HeapType *create_heap();    // 생성 함수
void init_heap(HeapType *h); // 초기화 함수
int is_empty(HeapType *h); // 비어있는지 확인하는 함수
void insert_min_heap(HeapType *h, int item); // 삽입 함수
int delete_min_heap(HeapType *h); // 삭제 함수
int find(HeapType *h); // 최솟값 찾기
element *find_node(element *node, int index); // 노드의 위치를 찾는 함수
void find_pre_node(element *root, int index, element *new_node); // 부모 노드를 찾는 함수
element *new_element(HeapType *h, int key, int index); // 새로운 노드 만들기


HeapType *create_heap() {
    return (HeapType *) malloc(sizeof(HeapType));
}

void init_heap(HeapType *h) {
    h->heap_size = 0;
}

int is_empty(HeapType *h) {
    return (h->heap_size == 0);
}

void insert_min_heap(HeapType *h, int item) {
    int i = ++(h->heap_size);
    new_element(h, item, h->heap_size); // 새로운 노드 생성

    while (i != 1 && item < find_node(h->heap, i / 2)->key) {
        find_node(h->heap, i)->key = find_node(h->heap, i / 2)->key;
        i /= 2;
    }
    find_node(h->heap, i)->key = item; // 새로운 노드 삽입
}

int delete_min_heap(HeapType *h) {
    int parent, child;
    int item, temp;
    item = find(h);
    temp = find_node(h->heap, h->heap_size--)->key;
    parent = 1;
    child = 2;
    while (child <= h->heap_size) {

        if (child < h->heap_size && find_node(h->heap, child)->key > find_node(h->heap, child + 1)->key)
            child++;
        if (temp <= find_node(h->heap, child)->key)
            break;

        find_node(h->heap, parent)->key = find_node(h->heap, child)->key;
        parent = child;
        child *= 2;
    }
    find_node(h->heap, parent)->key = temp;
    return item;
}


int find(HeapType *h) {
    return h->heap->key;
}

element *find_node(element *node, int index) {
    int temp[8] = {0};
    int cnt = 0;
    element *root = node;

    while (index > 1) {
        temp[cnt++] = index % 2;
        index /= 2;
    }
    //0이면 left, 1이면 right
    cnt--;
    while (cnt >= 0) {
        if (temp[cnt] == 0)
            root = root->left;
        else if (temp[cnt] == 1)
            root = root->right;
        cnt--;
    }
    return root;
}

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

element *new_element(HeapType *h, int key, int index) {
    element *new_node = (element *) malloc(sizeof(element));
    if (new_node == NULL) {
        printf("Allocation Error");
        exit(1);
    }
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;

    if (h->heap == NULL) {
        h->heap = new_node;
    } else {
        find_pre_node(h->heap, index, new_node);
    }
    return new_node;
}

int main(void) {
    int e[5] = {30, 50, 10, 20, 5};
    int e_del[5];
    HeapType *heap = create_heap(); // 히프 생성
    init_heap(heap);            // 초기화
    // 삽입
    //main() 함수에서 insert_min_heap() 으로 key 값 30, 50, 10, 20, 5을 가지는 element를 차례로 추가한다.
    for (int i = 0; i < 5; i++) {
        insert_min_heap(heap, e[i]);
    }

    // 삭제
    //delete_min_heap() 함수를 5회 호출하면서 element 값을 출력한다.
    for (int i = 0; i < 5; i++) {
        e_del[i] = delete_min_heap(heap);
    }

    for (int i = 0; i < 5; i++) {
        printf("<%d>\n", e_del[i]);
    }
    free(heap);
    return 0;
}