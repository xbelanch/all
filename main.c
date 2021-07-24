#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    size_t data;
    struct node *next;
} Node;

typedef struct list {
    Node *head;
    Node *tail;
    size_t n;
} List;

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
    list->n++;
    return node;
}

int delete(List *list) {
    return pop(list);
}

void listScan(List *list) {
    Node *node = list->head;
    while (NULL != node) {
        fprintf(stdout, "data: %lu\n", node->data);
        node = node->next;
    }
}


// Node *findNode(List *list, size_t data) {
//     if (NULL == list)
//         return NULL;
//     Node *p = list->head;
//     while (p->next != NULL) {
//         p = p->next;
//         if (p->data == data)
//             return p;
//     }

//     return NULL;
// }

// void insertAfter(Node *this, Node *that) {
//     that->next = this->next;
//     this->next = that;
// }

// // void insertAtBeginning(List *list, Node *this) {

// // }

// void removeAfter(Node *this) {
//     Node *remove = this->next;
//     this->next = this->next->next;
//     free(remove);
// }

// void printNode(Node *node) {
//     if (NULL == node) {
//         fprintf(stderr, "Node with this data not found!\n");
//     } else {
//         fprintf(stdout, "data: %lu\n", node->data);
//     }
// }


int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv[0];

    List *list = newList();

    for (size_t i = 0; i < 5; ++i)
        add(list, i);

    fprintf(stdout, "size: %lu\n", list->n);
    pop(list);
    fprintf(stdout, "size: %lu\n", list->n);
    push(list, 12);
    fprintf(stdout, "size: %lu\n", list->n);
    add(list, 99);
    listScan(list);
    return 0;
}
