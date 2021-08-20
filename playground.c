/*
 * Playground.c
 * A basic sandbox for testing weird pointers and memory functions
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node {
    struct _node *next;
    char *payload[1];
} Node;

typedef struct {
    char *name;
    size_t age;
    char *first_surname;
    char *last_surname;
} Player;

typedef struct {
    char *name;
    char *first_surname;
    char *last_surname;
} Entry;

typedef struct {
    size_t data:64;
} Bucket;

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv[0];

    Node *data = malloc(sizeof(Node) + sizeof(Player));
    Player *player = &(data->payload);
    player->age = 48;
    player->name = "Xavier";
    player->first_surname = "Belanche";
    player->last_surname = "Alonso";

    for (size_t i = 0; i < 32 ; ++i) {
        putchar(*((char *)*(data->payload) + i));
    }

    putchar('\n');
    // fprintf(stdout, "age: %s\n", (*(Player *)(&(data->payload))).age);
    // fprintf(stdout, "name: %s\n", (*(Player *)(&(data->payload))).name);

    // (*(Player*)(data->payload)).age = 48;
    // (*(Player*)(data->payload)).name = "Xavier";
    // (*(Player*)(data->payload)).first_surname = "Belanche";
    // (*(Player*)(data->payload)).last_surname = "Alonso";
    // fprintf(stdout, "name:%s\n", (*(Player*)(data->payload)).age);

    // Still don't understand how to do that...
    void *bucket = &(Bucket){0};
    void *entry = &(Entry){
        .name = "Júlia",
        .first_surname = "Belanche",
        .last_surname = "Griñó",
    };

    fprintf(stdout, "entry.name: %s\n", (*(Entry*)entry).name);
    size_t len = 24; // 8 bits (char) * 3 fields
    void *dst =((char *)bucket) + len;
    memcpy(dst, entry, len);

    for (size_t i = 0; i < len; ++i) {
        if (*(char*) ((*(Bucket*)dst).data + i) != '\0') {
            putchar(*(char*) ((*(Bucket*)dst).data + i));
        } else {
            putchar('|');
        }
    }

    return (0);
}
