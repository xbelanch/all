/*
 * All: A (simple) linked list
 *
 * Use of this source code is governed by Public Domain
 * license that can be found in the LICENSE file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "all.h"

List *newList(void (*traverse)(List *list, void (*callback)(Node *)),
              int (*compare)(const void *, const void *b)) {
    List *list = malloc(sizeof(List));
    list->head = NULL;
    list->n = 0;
    assert(traverse && "Must declare a traverse function");
    list->traverse = traverse;
    assert(compare && "You must declare a compare function");
    list->compare = compare;
    return (list);
}

int push(List *list, void *data) {
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->next = list->head;
    list->head = node;
    list->n++;
    return (0);
}

Node *pop(List *list) {
    if (list->n == 0)
        return NULL;

    Node *remove = list->head;
    list->head = list->head->next;
    list->n--;
    return (remove);
}

Node *peek(List *list) {
    if (list->n == 0)
        return NULL;
    return list->head;
}

int add_after(List *list, Node *prev, void *data) {
    Node *cursor = list->head;
    while (cursor != prev) {
        cursor = cursor->next;
    }
    if (cursor != NULL) {
        Node *node = malloc(sizeof(Node));
        node->data = data;
        if (cursor->next != NULL) {
            node->next = prev->next;
            prev->next = node;
        }
        list->n++;
        return (0);
    } else {
        return (1);
    }
}

int add_before(List *list, Node *next, void *data) {
    Node *cursor = list->head;
    Node *prev = NULL;
    while (cursor != next) {
        prev = cursor;
        cursor = cursor->next;
    }

    if (cursor != NULL) {
        Node *node = malloc(sizeof(Node));
        node->data = data;
        list->n++;
        if (prev == NULL) {
            // next equals to head list
            node->next = cursor;
            list->head = node;
        } else {
            node->next = cursor;
            prev->next = node;
        }
        return (0);
    } else {
        return (1);
    }
}

Node *get(List *list, void *data) {
    if (data == NULL)
        panic("Cannot get any node from list because given data is NULL");
    Node *cursor = list->head;
    while (cursor != NULL) {
        if (list->compare(cursor->data, data) == 0) {
            return cursor;
        }
        cursor = cursor->next;
    }
    return NULL;
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

/*
 * At this moment the code has been stolen from:
 * https://www.geeksforgeeks.org/merge-sort-for-linked-list/
 * TODO: Understand how merge sort algorithm is working
 * Maybe you can found a nice explanation at Wikipedia:
 * https://en.wikipedia.org/wiki/Merge_sort#Natural_merge_sort
 */

static Node *sort_two_nodes(List *list, Node *frontNode, Node *backNode) {
    Node *result = NULL;

    if (frontNode == NULL)
        return (backNode);
    else if (backNode == NULL)
        return (frontNode);

    if (list->compare(frontNode->data, backNode->data) <= 0) {
        result = frontNode;
        result->next = sort_two_nodes(list, frontNode->next, backNode);
    } else {
        result = backNode;
        result->next = sort_two_nodes(list, frontNode, backNode->next);
    }

    return (result);
}

void sort(List *list, Node **headRef) {
    if (list == NULL || *headRef == NULL)
        panic("PANIC: List or headRef are NULL");

    Node *head = *headRef;
    Node *frontNode;
    Node *backNode;

    if (head == NULL || head->next == NULL)
        return;

    split_list(head, &frontNode, &backNode);
    sort(list, &frontNode);
    sort(list, &backNode);

    *headRef = sort_two_nodes(list, frontNode, backNode);
}
