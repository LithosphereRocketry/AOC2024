#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../utils.h"

struct entry {
    size_t len;
    int* lst;
};

size_t ents_len = 0;
struct entry* ents;

bool entry_has(struct entry* entry, int value) {
    for(size_t i = 0; i < entry->len; i++) {
        if(entry->lst[i] == value) return true;
    }
    return false;
}

void entry_push(struct entry* entry, int value) {
    if(entry_has(entry, value)) return;
    entry->lst = realloc(entry->lst, (entry->len + 1)*sizeof(int));
    entry->lst[entry->len] = value;
    entry->len++;
}

void entry_merge(struct entry* into, const struct entry* from) {
    for(size_t i = 0; i < from->len; i++) {
        entry_push(into, from->lst[i]);
    }
}

void putent(int first, int second) {
    if(second+1 >= ents_len) {
        ents = realloc(ents, (second+1)*sizeof(struct entry));
        for(size_t i = ents_len; i < second+1; i++) {
            ents[i].len = 0;
            ents[i].lst = NULL;
        }
        ents_len = second+1;
    }
    entry_push(&ents[second], first);
}

int main(int argc, char** argv) {
    FILE* f = fopen("input.txt", "r");
    int first, second;
    while(fscanf(f, "%i|%i\n", &first, &second) == 2) {
        putent(first, second);
    }

    int score = 0;
    // first now contains the first number of the sequence, because scanf things
    char* line;
    while((line = fgets_dup(f)) && strlen(line) > 0) {
        intList lnums;
        il_init(&lnums);
        char* lptr = line;
        int inc;
        if(first == -1) {
            sscanf(lptr, "%i%n", &first, &inc);
            lptr += inc;
        }
        il_append(&lnums, first);
        while(sscanf(lptr, ",%i%n", &first, &inc) == 1) {
            il_append(&lnums, first);
            lptr += inc;
        }

        bool line_safe = true;
        struct entry ent = {0, NULL};
        for(int i = 0; i < lnums.len; i++) {
            int newnum = lnums.contents[i];
            if(entry_has(&ent, newnum)) {
                line_safe = false;
                break;
            }
            if(newnum < ents_len) {
                entry_merge(&ent, &ents[newnum]);
            }
        }
        if(line_safe) {
            score += lnums.contents[lnums.len / 2];
        }

        first = -1;
        il_destroy(&lnums);
        free(line);
    }
    printf("%i\n", score);
}