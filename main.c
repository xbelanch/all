#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node {
    size_t data;
    struct node *next;
} Node;

typedef struct list {
    Node *head;
    Node *tail;
    size_t n;
} List;

typedef void (*callback)(Node* data); // ok guys

List *newList() {
    List *list = malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
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
    if (list->n == 0)
        list->tail = node;
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
    list->tail = node;
    list->tail->next = NULL;
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

        } else {
            list->tail->next = node;
            list->tail = node;
            list->tail->next = NULL;
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

void traverse(List *list, callback func)
{
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

void midList(Node *head, Node **frontNode, Node **backNode) {
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

Node *sortMerge(Node *frontNode, Node *backNode) {

    Node *result = NULL;

    if (frontNode == NULL)
        return (backNode);
    else if (backNode == NULL)
        return (frontNode);

    if (frontNode->data <= backNode->data) {
        result = frontNode;
        result->next = sortMerge(frontNode->next, backNode);
        // if (result->next->next == NULL)
        //     printNode(result->next);
    } else {
        result = backNode;
        result->next = sortMerge(frontNode, backNode->next);
    }


    return (result);
}

// Merge sort algorithm
void merge_sort(Node **headRef) {

    Node *head = *headRef;
    Node *frontNode;
    Node *backNode;

    // Base case -- length 0 or 1;
    if (head == NULL || head->next == NULL)
        return;

    midList(head, &frontNode, &backNode);

    merge_sort(&frontNode);
    merge_sort(&backNode);

    // merge the sorted lists together
    *headRef = sortMerge(frontNode, backNode);
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv[0];

    List *list = newList();

    for (int i = 0; i <= 10; ++i)
        add(list, i);

    pop(list);
    push(list, 12);
    add(list, 1000);
    insert_after(list, list->head, 330);
    insert_after(list, list->tail, 22);
    insert_before(list, list->head, 101);
    insert_before(list, search(list, 330), 33);
    merge_sort(&list->head);
    traverse(list, printNode);
    fprintf(stdout, "Head value: %lu\n", list->head->data);
    assert(1000  == list->tail->data);
    fprintf(stdout, "Tail value: %lu\n", list->tail->data);
    free(list);
    return 0;
}
