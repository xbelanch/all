#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    size_t data;
    struct node *next;
} Node;

typedef struct list {
    Node *head;
} List;

Node *newNode() {
    Node *node = malloc(sizeof(Node));
    return node;
}

Node *addNode(List *list, size_t data) {
    Node *node, *p;
    node = newNode();
    node->data = data;
    node->next = NULL;
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


int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv[0];

    List *list = malloc(sizeof(List));
    addNode(list, 0x10);
    addNode(list, 0x100);

    Node *node = list->head;
    while (NULL != node) {
        fprintf(stdout, "data: %lu\n", node->data);
        node = node->next;
    }

    return 0;
}
