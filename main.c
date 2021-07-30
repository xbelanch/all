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
        if (node->next != NULL)  {
            fprintf(stdout, "\tnext data: %lu\n", node->next->data);
        } else {
            fprintf(stdout, "\tnext data is NULL\n");
        }
    }
}

Node *find_at_index(List *list, size_t index) {
    if (index > list->n)
        return NULL;

    size_t n = 0;
    Node *cursor = list->head;
    while (cursor != NULL) {
        if (n == index) {
            return cursor;
        }
        cursor = cursor->next;
        n++;
    }

    return NULL;
}

// Merge sort algorithm
List *merge_sort(List *list) {
    if (list->n <= 1)
        return list;
    printf("+++++++++++++++++++++\n");
    printf("LEFT ----\n");
    // left half list
    Node *start = list->head;
    Node *pointer = start;
    Node *end= find_at_index(list, (list->n / 2));
    List *leftList = newList();
    while (pointer != end) {
        add(leftList, pointer->data);
        pointer = pointer->next;
    }
    // add(leftList, end->data);
    traverse(leftList, printNode);
    printf("RIGHT ----\n");

    // right halft list
    start = end;
    pointer = start;
    List *rightList = newList();
    while (pointer != NULL) {
        add(rightList, pointer->data);
        pointer = pointer->next;
    }
    traverse(rightList, printNode);

    merge_sort(leftList);
    merge_sort(rightList);

    return NULL;
}


// Sort a linked list using insertion sort
// Robbed at the moment from https://www.learnc.net/c-data-structures/c-linked-list/
// TODO: Fix list tail point to the right node
Node* sort(List *list)
{
    Node *x, *y, *e;

    x = list->head;
    list->head = NULL;

    while(x != NULL) {
        e = x;
        x = x->next;
        if (list->head != NULL) {
            if(e->data > list->head->data) {
                y = list->head;
                while ((y->next != NULL) && (e->data > y->next->data)) {
                    y = y->next;
                }
                e->next = y->next;
                y->next = e;
            }
            else {
                e->next = list->head;
                list->head = e;
            }
        }
        else {
            e->next = NULL;
            list->head = e;
        }
    }

    return list->head;
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv[0];

    List *list = newList();

    for (size_t i = 0; i < 5; ++i)
        add(list, i);

    pop(list);
    push(list, 12);
    add(list, 1000);
    insert_after(list, list->head, 330);
    insert_after(list, list->tail, 22);
    insert_before(list, list->head, 101);
    insert_before(list, search(list, 330), 33);

    // sort(list);
    traverse(list, printNode);
    fprintf(stdout, "Head value: %lu\n", list->head->data);
    fprintf(stdout, "Tail value: %lu\n", list->tail->data);
    fprintf(stdout, "Length of list: %lu\n", list->n);
    fprintf(stdout, "Node value at half of list: %lu\n", find_at_index(list, list->n / 2)->data);


    //
    printf("+++ MERGE SORTING +++\n");
    merge_sort(list);
    free(list);
    return 0;
}
