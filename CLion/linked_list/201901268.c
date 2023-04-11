//
// Created by SeungJun Ryu on 2023/04/08.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[100];
} element;

typedef struct ListNode {
    element data;
    struct ListNode *link;
} ListNode;

void error(char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

ListNode *insert_first(ListNode *head, element value) {
    ListNode *p = (ListNode *) malloc(sizeof(ListNode));
    p->data = value;
    p->link = head;
    head = p;
    return head;
}

ListNode *insert(ListNode *head, ListNode *pre, element value) {
    ListNode *p = (ListNode *) malloc(sizeof(ListNode));
    p->data = value;
    p->link = pre->link;
    pre->link = p;
    return head;
}

ListNode *delete_first(ListNode *head) {
    ListNode *removed;
    if (head == NULL)
        return NULL;
    removed = head;
    head = removed->link;
    free(removed);
    return head;
}

ListNode *delete(ListNode *head, ListNode *p) {
    ListNode *pre, *removed = NULL;

    if (head == NULL) {
        return NULL;
    }

    if (head == p) {
        removed = head;
        head = removed->link;
        free(removed);
        return head;
    }

    pre = head;
    while (pre->link != NULL && pre->link != p) {
        pre = pre->link;
    }

    if (pre->link == NULL) {
        error("Not found");
    }

    removed = pre->link;
    pre->link = removed->link;
    free(removed);
    return head;
}


void print_list(ListNode *head) {
    for (ListNode *p = head; p != NULL; p = p->link)
        printf("%s -> ", p->data.name);
    printf("NULL \n");
}

ListNode *search(ListNode *head, element item) {
    ListNode *p = head;

    while (p != NULL) {
        if (strcmp(p->data.name, item.name) == 0) {
            return p;
        }
        p = p->link;
    }
    error("Not found");
    return NULL;
}

ListNode *split_list(ListNode *head, ListNode *split_node) {
    ListNode *p = head;
    if(head == NULL)
        return NULL;
    while (p->link != split_node)
        p = p->link;
    p->link = NULL;
    return head;
}

int main(void) {
    ListNode *head = NULL;
    ListNode *head2 = NULL;
    ListNode *p = NULL;
    element data;

    strcpy(data.name, "PEACH");
    head = insert_first(head, data);
    strcpy(data.name, "MELON");
    head = insert_first(head, data);
    strcpy(data.name, "MANGO");
    head = insert_first(head, data);
    strcpy(data.name, "LEMON");
    head = insert_first(head, data);
    strcpy(data.name, "BANANA");
    head = insert_first(head, data);
    strcpy(data.name, "KIWI");
    head = insert_first(head, data);
    strcpy(data.name, "APPLE");
    head = insert_first(head, data);
    printf("head -> ");
    print_list(head);

    printf("삭제할 단어: ");
    scanf("%s", data.name);

    if ((p = search(head, data)) != NULL) {
        head2 = p->link;
    }

    if (p == head) {
        head2 = delete_first(head);
        head = NULL;
    } else {
        head = delete(head, p);
        head = split_list(head, head2);
    }

    printf("head1 -> ");
    if (head == NULL)
        printf("NULL\n");
    else
        print_list(head);
    printf("head2 -> ");
    print_list(head2);

    return 0;
}
