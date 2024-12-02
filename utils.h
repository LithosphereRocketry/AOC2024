/* All the generic utilities and helpers I'm using
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

size_t fsize(FILE* f) {
	size_t pos = ftell(f);
	fseek(f, 0, SEEK_END);
	size_t end = ftell(f);
	fseek(f, pos, SEEK_SET);
	return end;
}

typedef struct {
	size_t len;
	size_t capacity;
	int * contents;
} intList;

void il_init(intList * list) {
	list->len = 0;
	list->capacity = 1;
	list->contents = malloc(sizeof(int));
}

void il_destroy(intList * list) {
	free(list->contents);
}

void il_clear(intList * list) {
	il_destroy(list);
	il_init(list);
}

void il_append(intList * list, int item) {
	if(list->len >= list->capacity) {
		list->capacity *= 2;
		list->contents = realloc(list->contents, list->capacity*sizeof(int));
	}
	list->contents[list->len] = item;
	list->len ++;
}

void listPrint(intList * list) {
	printf("[");
	for(int i = 0; i < list->len; i++) {
		printf("%i%s", list->contents[i], (i < list->len-1) ? ", " : "");
	}
	printf("]\n");
}

size_t memcount(char c, const char* buf, size_t len) {
	size_t count = 0;
	for(size_t i = 0; i < len; i++) {
		if(buf[i] == c) count++;
	}
	return count;
}


/**
 * Helper function for read-until-character to heap
 * Reads until the given character, or EOF if until=-1
*/
static char* fread_dup_helper(FILE* stream, int until) {
    char* str = malloc(1);
    size_t size = 0;
    size_t cap = 1;
    if(!str) return NULL;

    while(1) {
        str[size] = fgetc(stream);
        if(feof(stream)) break;

        size ++;
        if(size >= cap) {
            cap *= 2;
            char* newstr = realloc(str, cap);
            if(!newstr) {
                free(str);
                return NULL;
            }
            str = newstr;
        }
        if(str[size-1] == until) break;
    }
    str = realloc(str, size+1);
    str[size] = '\0';
    return str;
}

char* fgets_dup(FILE* stream) {
    return fread_dup_helper(stream, '\n');
}

char* fread_dup(FILE* stream) {
    return fread_dup_helper(stream, -1);
}

#endif