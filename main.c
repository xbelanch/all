#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "all.h"


typedef struct _data{
    char *name;
    char *surname;
} Data;

void printHeadData(List *list) {
    Data *data = ((Data*)(list->head->data));
    fprintf(stdout, "data: %s %s\n", data->name, data->surname);
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv[0];

    List *list = newList(printHeadData);
    push(list, newNode(&(Data){.name="Rotter", .surname="de Olanots"}));
    push(list, newNode(&(Data){.name="Lyud", .surname="Pavlichenko"}));
    push(list, newNode(&(Data){.name="Pucka", .surname="Coll"}));
    list->printHeadData(list);
    pop(list);
    list->printHeadData(list);


    // push(list, 12);
    // add(list, 1000);
    // insert_after(list, list->head, 330);
    // insert_before(list, list->head, 101);
    // insert_before(list, search(list, 330), 33);
    // fprintf(stdout, "Head value before merge sort: %lu\n", list->head->data);
    // sort(&list->head);
    // traverse(list, printNode);
    // fprintf(stdout, "Head value after merge sort: %lu\n", list->head->data);
    // free(list);
    return 0;
}
