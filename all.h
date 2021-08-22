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

typedef struct node {
    struct node *next;
    void *data;
} Node;

typedef struct list {
    size_t n;
    Node *head;
    void (*traverse)(struct list *, void (*)(struct node *));
    int (*compare)(const void *, const void *value2);
    void (*callback)(Node* data); //
} List;

/*
 * Create a new linked list
 */
List *newList(void (*traverse)(struct list*, void(*)(struct node*)),
              int (*compare)(const void *a, const void *b));

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

/*
 * Insert a new node after a existing node from list.
 */
int add_after(List *list, Node *prev, void *data);

/*
 * Insert a new node before a existing node from list.
 */
int add_before(List *list, Node *next, void *data);

/*
 * Get a node from list given a data using compare function.
 */
Node *get(List *list, void *data);

/*
 * Sort list using compare function.
 */
void sort(List* list, Node **headRef);

#endif
