#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
