#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "all.h"

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
    insert_before(list, list->head, 101);
    insert_before(list, search(list, 330), 33);
    fprintf(stdout, "Head value before merge sort: %lu\n", list->head->data);
    sort(&list->head);
    traverse(list, printNode);
    fprintf(stdout, "Head value after merge sort: %lu\n", list->head->data);
    free(list);
    return 0;
}
