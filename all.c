#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "all.h"

List *newList() {
    List *list = malloc(sizeof(List));
    list->head = NULL;
    list->n = 0;
    return list;
}

Node *newNode(size_t data) {
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

int push(List *list, size_t data) {
    Node *node = newNode(data);
    node->next = list->head;
    list->head = node;
    list->n++;
    return 0;
}

int pop(List *list) {
    if (list->n == 0)
        return 0;

    Node *remove = list->head;
    list->head = list->head->next;
    list->n--;
    free(remove);

    return 1;
}

Node *add(List *list, size_t data) {
    Node *node, *p;
    node = newNode(data);
    if (list->head == NULL) {
        list->head = node;
    } else {
        p = list->head;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = node;
    }
    list->n++;
    return node;
}

int delete(List *list) {
    return pop(list);
}

Node *insert_after(List *list, Node *prev, size_t data) {
    Node *cursor = list->head;
    while (cursor != prev) {
        cursor = cursor->next;
    }

    if (cursor != NULL) {
        Node *node = newNode(data);
        if (cursor->next != NULL) {
            node->next = prev->next;
            prev->next = node;
        }
        list->n++;
        return node;
    } else {
        return NULL;
    }
}

Node *insert_before(List *list, Node *next, size_t data) {
    Node *cursor = list->head;
    Node *prev = NULL;
    while (cursor != next) {
        prev = cursor;
        cursor = cursor->next;
    }

    if (cursor != NULL) {
        Node *node = newNode(data);
        list->n++;
        if (prev == NULL) {
            // next equals to head list
            node->next = cursor;
            list->head = node;
            return list->head;
        } else {
            node->next = cursor;
            prev->next = node;
            return node;
        }
    } else {
        return NULL;
    }
}

Node *search(List *list, size_t data) {
    Node *cursor = list->head;
    while (cursor != NULL) {
        if (cursor->data == data) {
            return cursor;
        }
        cursor = cursor->next;
    }

    return NULL;
}

void traverse(List *list, callback func) {
    Node* cursor = list->head;
    while(cursor != NULL) {
        func(cursor);
        cursor = cursor->next;
    }
}

void printNode(Node *node) {
    if (node == NULL) {
        fprintf(stderr, "Node with this data not found!\n");
    } else {
        fprintf(stdout, "data: %lu\n", node->data);
    }
}

static void split_list(Node *head, Node **frontNode, Node **backNode) {
    Node *slow = head;
    Node *fast = head->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    // slow is at the midpoint in the list
    *frontNode = head;
    *backNode = slow->next;
    slow->next = NULL;
}

static Node *sort_two_nodes(Node *frontNode, Node *backNode) {
    Node *result = NULL;

    if (frontNode == NULL)
        return (backNode);
    else if (backNode == NULL)
        return (frontNode);

    if (frontNode->data <= backNode->data) {
        result = frontNode;
        result->next = sort_two_nodes(frontNode->next, backNode);
    } else {
        result = backNode;
        result->next = sort_two_nodes(frontNode, backNode->next);
    }

    return (result);
}

// At this moment the code has been stolen from:
// https://www.geeksforgeeks.org/merge-sort-for-linked-list/
// TODO: Understand how merge sort algorithm is working
// Maybe you can found a nice explanation at Wikipedia:
// https://en.wikipedia.org/wiki/Merge_sort#Natural_merge_sort
void sort(Node **headRef) {
    Node *head = *headRef;
    Node *frontNode;
    Node *backNode;

    if (head == NULL || head->next == NULL)
        return;

    split_list(head, &frontNode, &backNode);
    sort(&frontNode);
    sort(&backNode);

    *headRef = sort_two_nodes(frontNode, backNode);
}
