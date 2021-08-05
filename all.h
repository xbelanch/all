#ifndef ALL_H
#define ALL_H


// TODO: Implement abstract data type
// https://stackoverflow.com/questions/3274472/c-double-linked-list-with-abstract-data-type
typedef struct node {
    size_t data;
    struct node *next;
} Node;

typedef struct list {
    Node *head;
    size_t n;
} List;

typedef void (*callback)(Node* data); // ok guys

List *newList();
Node *newNode(size_t data);
int push(List *list, size_t data);
int pop(List *list);
Node *add(List *list, size_t data);
int delete(List *list);
Node *insert_after(List *list, Node *prev, size_t data);
Node *insert_before(List *list, Node *next, size_t data);
Node *search(List *list, size_t data);
void traverse(List *list, callback func);
void printNode(Node *node);
void sort(Node **headRef);

#endif
