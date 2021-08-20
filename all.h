/*
 * All: A (simple) linked list
 *
 * Use of this source code is governed by Public Domain
 * license that can be found in the LICENSE file.
 */

#ifndef ALL_H
#define ALL_H
#define panic(_msg_) { \
    fprintf(stderr, "PANIC: %s (%s:%d)\n", (_msg_), __FILE__, __LINE__); \
    exit(1); \
}

/*
 * TODO: Implement the abstract data type
 *
 * References:
 * - https://stackoverflow.com/questions/3274472/c-double-linked-list-with-abstract-data-type
 * - https://www.geeksforgeeks.org/abstract-data-types/
 */

typedef struct node {
    struct node *next;
    void *data;
} Node;

typedef struct list {
    size_t n;
    Node *head;
    void (*traverse)(struct list *self, void (*)(Node *));
    int (*compare)(void *value1, void *value2);
    void (*callback)(Node* data); // ok guys
} List;

/*
 * Create a new linked list
 */
List *newList(void (*traverse)(struct list*, void(*callback)(struct node*)));

/*
 * Insert an element at one end of the stack called top.
 */
int push(List *list, void *data);

/*
 * Return the element at the top of the stack without removing it, if the stack is not empty.
 */

Node *pop(List *list);

/*
 * Return the element at the top of the stack without removing it, if the stack is not empty.
 */
Node *peek(List *list);

int add_after(List *list, Node *prev, void *data);
// Node *add_before(List *list, Node *next, size_t data);
// Node *search(List *list, size_t data);
// void traverse(List *list, void (*callback)(Node* data));
// void printNode(Node *node);
// void sort(Node **headRef);

#endif
