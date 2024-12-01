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

void init(intList * list) {
	list->len = 0;
	list->capacity = 1;
	list->contents = malloc(sizeof(int));
}

void clear(intList * list) {
	free(list->contents);
	init(list);
}

void append(intList * list, int item) {
	if(list->len >= list->capacity) {
		list->capacity *= 2;
		int* newList = malloc(list->capacity * sizeof(int));
		memcpy(newList, list->contents, list->len);
	}
	free(list->contents);
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

#endif