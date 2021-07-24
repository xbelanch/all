#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    size_t data;
    struct node *next;
} Node;

typedef struct list {
    Node *firstNode;
} List;

Node *newNode(size_t data) {
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

List *list;

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv[0];

    list = malloc(sizeof(List));
    list->firstNode = newNode(0);
    Node *node = list->firstNode;

    while (NULL != node) {
        fprintf(stdout, "data: %lu\n", node->data);
        node = node->next;
    }

    return 0;
}
