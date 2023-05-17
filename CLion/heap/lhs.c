#include <stdio.h>
#include <stdlib.h>

typedef struct element {
    int key;
    struct element* left;
    struct element* right;
} element;

typedef struct HeapType {
    element* heap;
    int heap_size;
} HeapType;

HeapType* create_heap() {
    return (HeapType*)malloc(sizeof(HeapType));
}

void init_heap(HeapType* h) {
    h->heap_size = 0;
}

element* new_element(int data) {
    element* e = (element*)malloc(sizeof(element));
    if (e == NULL) {
        fprintf(stderr,"오류!\n");
        exit(1);
    }
    e->key = data;
    e->left = e->right = NULL;
    return e;
}

int is_empty(HeapType* h) {
    return (h->heap_size == 0);
}

void change_binary(int* arr, int num){ //이진수 저장 될때 3은 011이지만 배열에서는 110으로 저장됨
    int c = 0, mok, nmg, i;

    do{
        mok = num / 2;
        nmg = num % 2;
        arr[c++] = nmg;
        num = mok;
    } while (mok != 0);
}

int find_one(int* temp) {
    int flag, j;
    for (flag = 0, j = 2; flag != 1; j--) { // 이진수 저장하는 배열에서 마지막에서 첫번째로 1이 나오면 0에서 1로 변함
        if (temp[j] == 1)
            flag = 1;
    }
    return j;
}

element* linked_list_index(int* temp, element* root) { //링크드 리스트 index 찾기
    element* tmp = root;
    int k = find_one(temp);
    for (; k >= 0; k--) {
        if (temp[k] == 1)
            tmp = tmp->right;
        else if (temp[k] == 0)
            tmp = tmp->left;
    }
    return tmp;
}

void swap(int* key1, int* key2) { //키 값 교환
    int tmp = *key1;
    *key1 = *key2;
    *key2 = tmp;
}


void insert_min_heap(HeapType* h, int key) {
    if (is_empty(h)) {
        h->heap = new_element(key);
        h->heap_size++;
        return;
    }

    int i = ++(h->heap_size);
    int temp[3] = { 0 };
    change_binary(temp, i / 2);

    element* tmp = linked_list_index(temp, h->heap);
    if (i % 2 == 1) // i가 홀수 일때
        tmp->right = new_element(key);
    else // i가 짝수 일때
        tmp->left = new_element(key);

    while (i != 0) {
        int temp1[3] = { 0 };
        int temp2[3] = { 0 };
        change_binary(temp1, i); //자식 이진수
        change_binary(temp2, i / 2); //부모 이진수

        element* child = linked_list_index(temp1, h->heap);
        element* parent = linked_list_index(temp2, h->heap);

        if (child->key < parent->key)
            swap(&(child->key), &(parent->key));

        i /= 2;
    }
}

int delete_min_heap(HeapType* h) {

    if (is_empty(h)) {
        exit(1);
    }

    int key = h->heap->key; //말단 키 값

    int temp1[3] = { 0 };
    change_binary(temp1, h->heap_size);
    element* last = linked_list_index(temp1, h->heap);
    h->heap->key = last->key;

    int temp2[3] = { 0 };
    change_binary(temp2, h->heap_size / 2);
    element* last_parent = linked_list_index(temp2, h->heap);

    if (h->heap_size % 2 == 1) //말단 노드 부모의 left, right 중에 말단 노드가 있었던 위치에 NULL을 넣어준다.
        last_parent->right = NULL;
    else
        last_parent->left = NULL;

    h->heap_size--;
    free(last);

    int index = 1;
    while (index < h->heap_size) {
        int temp[3] = { 0 };
        change_binary(temp, index);
        element* parent = linked_list_index(temp, h->heap);

        if (parent->left == NULL) // 자식이 없는 경우
            break;

        else if (parent->right == NULL) { // 자식이 왼쪽에만 있는 경우
            if (parent->left->key < parent->key) {
                swap(&(parent->left->key), &(parent->key));
                index *= 2; //왼쪽
            }
            else
                break;
        }
        else if (parent->left->key < parent->right->key) { //자식이 왼쪽 오른쪽 둘다 있는 경우. 왼쪽 오른쪽 중 작은 쪽을 찾아주어야한다.
            if (parent->left->key < parent->key) { // 왼쪽 키가 오른쪽 키보다 작은 경우. 왼쪽 키와 부모키를 비교
                swap(&(parent->left->key), &(parent->key));
                index *= 2;
            }
            else
                break;
        }
        else {
            if (parent->right->key < parent->key) { // 오른쪽 키가 왼쪽 키보다 작은 경우. 오른쪽 키와 부모 키를 비교
                swap(&(parent->right->key), &(parent->key));
                index = index * 2 + 1; // 오른쪽
            }
            else
                break;
        }
    }
    return key;
}

int find(HeapType* h) {
    return h->heap->key;
}

int main(void) {

    HeapType* heap;
    heap = create_heap();
    init_heap(heap);

    insert_min_heap(heap, 30);
    insert_min_heap(heap, 50);
    insert_min_heap(heap, 10);
    insert_min_heap(heap, 20);
    insert_min_heap(heap, 5);
    /*
    printf("%d\n", heap->heap->key);
    printf("%d\n", heap->heap->left->key);
    printf("%d\n", heap->heap->right->key);
    printf("%d\n", heap->heap->left->left->key);
    printf("%d\n\n", heap->heap->left->right->key);
    */
    printf("%d\n", delete_min_heap(heap));
    printf("%d\n", delete_min_heap(heap));
    printf("%d\n", delete_min_heap(heap));
    printf("%d\n", delete_min_heap(heap));
    printf("%d\n", delete_min_heap(heap));


    return 0;
}