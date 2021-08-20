#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "all.h"


typedef struct data{
    char *name;
    char *surname;
} Data;

void print(struct node *node) {
    struct data *data = ((struct data*)(node->data));
    fprintf(stdout, "data: %s %s\n", data->name, data->surname);
}

void addstr(struct node *node){
    struct data *data = ((struct data*)(node->data));
    size_t len = strlen(data->surname);
    char *new = malloc(sizeof(char) * len + 64);
    memcpy(new, data->surname, len);
    strcat(new, " Fernández");
    data->surname = new;
}

void freeNode(struct node *node){
    struct data *data = ((struct data*)(node->data));
    data->name = 0;
    data->surname = 0;
}

void traverse(struct list *list, void (*callback)(struct node *node)) {
    struct node* cursor = list->head;
    while(cursor != NULL) {
        callback(cursor);
        cursor = cursor->next;
    }
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv[0];

    List *list = newList(traverse);
    push(list, &(Data){.name="Rotter", .surname="de Olanots"});
    push(list, &(Data){.name="Lyud", .surname="Pavlichenko"});
    push(list, &(Data){.name="Pucka", .surname="Coll"});
    Node *node = peek(list);
    add_after(list, node, &(Data){.name="Max", .surname="Carpone"});

    // Example of how to use callbacks on traverse the linked list
    list->traverse(list, addstr);
    list->traverse(list, print);
    list->traverse(list, freeNode);
    list->traverse(list, print);
    free(list);
    return 0;
}
