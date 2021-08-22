#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "all.h"

typedef struct data{
    char *name;
    char *surname;
} Data;

char *randomWords[] = {
    "González",
    "Fernández",
    "Belanche",
    "Coll",
    "Hegel",
    "Zizek"
};

void print(struct node *node) {
    struct data *data = ((struct data*)(node->data));
    fprintf(stdout, "data: %s %s\n", data->name, data->surname);
}

void strcatRandomWord(struct node *node){
    struct data *data = ((struct data*)(node->data));
    size_t len = strlen(data->surname);
    char *new = malloc(sizeof(char) * len + 1 + 64);
    memcpy(new, data->surname, len);
    strcat(new, " ");
    size_t lenRandomWords = sizeof(randomWords) / sizeof(randomWords[0]);
    strcat(new, randomWords[rand() % lenRandomWords]);
    data->surname = new;
}

// Callback needed: Compare surname between nodes
int compare(const void *a, const void *b) {
    const struct data *da = a;
    const struct data *db = b;
    return strcmp(da->surname, db->surname);
}

// Callback needed: traverse entire linked list
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

    srand(time(NULL));

    // Create a new list
    List *list = newList(traverse, compare);

    // Push some data onto this brand new list
    push(list, &(Data){.name="Rotter", .surname="Olanots"});
    push(list, &(Data){.name="Lyud", .surname="Pavlichenko"});
    push(list, &(Data){.name="Pucka", .surname="Coll"});
    push(list, &(Data){.name="Bizcocha", .surname="Singluten"});
    push(list, &(Data){.name="Pompa", .surname="Sircumstanchia"});
    push(list, &(Data){.name="Floki", .surname="Rangarok"});

    // Get the peek node
    Node *node = peek(list);
    add_after(list, node, &(Data){.name="Max", .surname="Karpone"});

    // Get a node that match with a given surname
    node = get(list, &(struct data){.name ="Pucka", .surname = "Coll"});
    if (node != NULL) {
        fprintf(stdout, "found: %s %s\n",
                ((struct data*)node->data)->name,
                ((struct data*)node->data)->surname
                );
    } else {
        panic("Given node data not found on list!");
    }

    // Add new node before the matched one
    add_before(list, node, &(Data){.name="Tomachito", .surname="Pomodoro"});

    // Sort linked list nodes by compare its surname values
    sort(list, &list->head);

    //  Callbacks! callbacks everywhere
    list->traverse(list, strcatRandomWord);

    // Traverse and print the data values of every node
    list->traverse(list, print);

    // Free up list
    free(list);
    return 0;
}
