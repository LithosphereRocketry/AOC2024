#include <stdio.h>
#include <stdbool.h>
#include "../utils.h"

char* data;
size_t w, h;
size_t x, y;

enum direction {
    NORTH, EAST, SOUTH, WEST
};

char at(size_t x, size_t y) {
    if(x < 0 || x >= w || y < 0 || y >= h) return '+';
    return data[y*(w+1) + x];
}

void put(size_t x, size_t y, char v) {
    data[y*(w+1) + x] = v;
}

void walk(enum direction dir) {
    size_t nx, ny;
    switch(dir) {
        case NORTH: nx = x; ny = y-1; break;
        case EAST: nx = x+1; ny = y; break;
        case SOUTH: nx = x; ny = y+1; break;
        case WEST: nx = x-1; ny = y; break;
    }
    if(at(nx, ny) == '#') {
        walk((dir+1)%4);
    } else {
        bool ns = dir == NORTH || dir == SOUTH;
        if((ns ? at(x, y) == '|' : at(x, y) == '-') || at(x, y) == '+') {
            return;
        } else if(ns ? at(x, y) == '-' : at(x, y) == '|') {
            put(x, y, '+');
        } else {
            put(x, y, ns ? '|' : '-');
        }
        x = nx;
        y = ny;
        walk(dir);
    }
}

int main(int argc, char** argv) {
    FILE* f = fopen("input.txt", "r");
    data = fread_dup(f);
    w = strchr(data, '\n') - data;
    h = strlen(data) / (w + 1);

    for(size_t i = 0; i < h; i++) {
        for(size_t j = 0; j < w; j++) {
            if(at(j, i) == '^') {
                x = j; y = i;
            }
        }
    }

    walk(NORTH);

    size_t score = 0;
    for(char* p = data; *p; p++) {
        if(*p == '+' || *p == '|' || *p == '-') score++;
    }
    printf("%lu\n", score);
}