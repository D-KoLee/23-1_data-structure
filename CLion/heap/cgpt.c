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

// 노드 생성 함수
element* new_element(int key) {
    element* new_node = (element*)malloc(sizeof(element));
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// 최소 힙 초기화 함수
void init_heap(HeapType* h) {
    h->heap = NULL;
    h->heap_size = 0;
}

// 비어있는지 확인하는 함수
int is_empty(HeapType* h) {
    return h->heap_size == 0;
}

// 트리의 루트부터 key 값에 해당하는 위치까지 내려가면서 노드 생성 및 연결
element* insert_min_heap(element* root, int key, int index, int bit) {
    if (root == NULL) {
        root = new_element(0);
    }

    if (index < bit) {
        int bit_val = (key >> (bit - 1 - index)) & 1;
        if (bit_val == 0) {
            root->left = insert_min_heap(root->left, key, index + 1, bit);
        }
        else {
            root->right = insert_min_heap(root->right, key, index + 1, bit);
        }
    }

    return root;
}

// 최소 힙에 아이템 추가
void insert(HeapType* h, int key) {
    int bit = 1;
    while ((1 << bit) <= key) {
        bit++;
    }
    h->heap = insert_min_heap(h->heap, key, 0, bit);
    h->heap_size++;
}

// 트리 순회 함수 (디버깅용)
void traverse(element* root) {
    if (root == NULL) {
        return;
    }
    traverse(root->left);
    printf("%d ", root->key);
    traverse(root->right);
}

// 최소 힙에서 아이템 제거
int delete_min_heap(element** root) {
    if (*root == NULL) {
        printf("Heap is empty.\n");
        return -1;
    }

    element* curr = *root;
    int min_key = curr->key;

    while (curr->left != NULL) {
        element* child = curr->left;

        if (curr->right != NULL && curr->right->key < child->key) {
            child = curr->right;
        }

        curr->key = child->key;
        curr = child;
    }

    free(curr);
    *root = NULL;

    return min_key;
}

int main() {
    HeapType heap;
    init_heap(&heap);

    // insert() 함수로 key 값 30, 50, 10, 20, 5 추가
    insert(&heap, 30);
    insert(&heap, 50);
    insert(&heap, 10);
    insert(&heap, 20);
    insert(&heap, 5);
    // delete_min_heap() 함수를 5회 호출하면서 element 값을 출력
    for (int i = 0; i < 5; i++) {
        int min_element = delete_min_heap(&(heap.heap));
        printf("%d ", min_element);
    }

    return 0;
}
