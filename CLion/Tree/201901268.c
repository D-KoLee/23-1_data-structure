// 이진 탐색 트리를 사용한 연락처 프로그램
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX_WORD_SIZE 100
#define MAX_PHONE_SIZE 200

typedef struct {
    char name[MAX_WORD_SIZE];        // 이름
    char phone_number[MAX_PHONE_SIZE]; // 전화번호
} element;

typedef struct TreeNode {
    element key;
    struct TreeNode *left, *right;
} TreeNode;

int compare(element e1, element e2) {
    return strcmp(e1.name, e2.name);
}

int node_count(TreeNode *node) {
    int count = 0;
    if (node != NULL)
        count = 1 + node_count(node->left) + node_count(node->right);
    return count;
}

void display(TreeNode *p) {
    if (p != NULL) {
        display(p->left);
        printf("count: %d, '%s'의 전화번호:%s \n", node_count(p), p->key.name, p->key.phone_number);
        display(p->right);
    }
}

TreeNode *search(TreeNode *root, element key) {
    TreeNode *p = root;
    if (p == NULL)
        return NULL;

    if (compare(key, p->key) == 0)
        return p;
    else if (compare(key, p->key) < 0)
        p = search(p->left, key);
    else if (compare(key, p->key) > 0)
        p = search(p->right, key);

    return p;
}

TreeNode *new_node(element item) {
    TreeNode *temp = (TreeNode *) malloc(sizeof(TreeNode));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

TreeNode *insert_node(TreeNode *node, element key) {
    if (node == NULL)
        return new_node(key);\
    if (compare(key, node->key) < 0)
        node->left = insert_node(node->left, key);
    else if (compare(key, node->key) > 0)
        node->right = insert_node(node->right, key);
    else if (compare(key, node->key) == 0)
        node->key = key;
    return node;
}

TreeNode *max_value_node(TreeNode *node) {
    TreeNode *current = node;
    while (current->right != NULL)
        current = current->right;
    return current;
}

void quit() {
    exit(1);
}

TreeNode *delete_node(TreeNode *root, element key) {
    if (root == NULL)
        return root;

    else if (compare(key, root->key) < 0)
        root->left = delete_node(root->left, key);
    else if (compare(key, root->key) > 0)
        root->right = delete_node(root->right, key);
    else {
        if (root->left == NULL) {
            TreeNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode *temp = root->left;
            free(root);
            return temp;
        }
        TreeNode *temp = max_value_node(root->right);

        root->key = temp->key;
        root->right = delete_node(root->right, temp->key);
    }
    return root;
}

int main(void) {
    char command;
    element e;
    TreeNode *root = NULL;
    TreeNode *tmp;

    do {
        printf("\n삽입(i), 탐색(s), 출력(p), 삭제(d), 종료(q): ");
        command = getchar();
        getchar();
        switch (command) {
            case 'i':
                printf("이름: ");
                fgets(e.name, sizeof e.name, stdin);
                e.name[strlen(e.name) - 1] = '\0';
                printf("전화번호: ");
                fgets(e.phone_number, sizeof e.phone_number, stdin);
                e.phone_number[strlen(e.phone_number) - 1] = '\0';
                root = insert_node(root, e);
                break;
            case 'd':
                printf("이름: ");
                fgets(e.name, sizeof e.name, stdin);
                e.name[strlen(e.name) - 1] = '\0';
                root = delete_node(root, e);
                break;
            case 'p':
                display(root);
                printf("\n");
                break;
            case 's':
                printf("이름: ");
                fgets(e.name, sizeof e.name, stdin);
                e.name[strlen(e.name) - 1] = '\0';
                tmp = search(root, e);
                if (tmp != NULL)
                    printf("'%s'의 전화번호:%s\n", tmp->key.name, tmp->key.phone_number);
                break;
            case 'q':
                quit();
        }

    } while (command != 'q');

    return 0;
}