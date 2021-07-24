#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    size_t data;
    struct node *next;
} Node;

typedef struct list {
    Node *head;
} List;

Node *newNode(size_t data) {
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

Node *addNode(List *list, size_t data) {
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
    return node;
}

Node *findNode(List *list, size_t data) {
    if (NULL == list)
        return NULL;
    Node *p = list->head;
    while (p->next != NULL) {
        p = p->next;
        if (p->data == data)
            return p;
    }

    return NULL;
}

void insertAfter(Node *this, Node *that) {
    that->next = this->next;
    this->next = that;
}

// void insertAtBeginning(List *list, Node *this) {

// }

void removeAfter(Node *this) {
    Node *remove = this->next;
    this->next = this->next->next;
    free(remove);
}

void listScan(List *list) {
    Node *node = list->head;
    while (NULL != node) {
        fprintf(stdout, "data: %lu\n", node->data);
        node = node->next;
    }
}

void printNode(Node *node) {
    if (NULL == node) {
        fprintf(stderr, "Node with this data not found!\n");
    } else {
        fprintf(stdout, "data: %lu\n", node->data);
    }
}

size_t listSize(List *list) {
    size_t size = 0;
    Node *node = list->head;
    while (NULL != node->next)  {
        size++;
        node = node->next;
    }
    return size;
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv[0];

    List *list = malloc(sizeof(List));
    for (size_t i = 0; i < 16; ++i) {
        addNode(list, i);
    }
    removeAfter(findNode(list, 8));
    insertAfter(findNode(list, 10), newNode(32));
    listScan(list);
    fprintf(stdout, "List size: %lu\n", listSize(list));

    return 0;
}
